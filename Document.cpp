//
//  PDFDocument.cpp
//  ImagePDF
/*
 Copyright 2012 Neio Zhou

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Document.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace PDF{

	

	Document::Document(string& filename)
	{
		//file should end of ".pdf"
		
		this->_file = new ofstream(filename.c_str(),ofstream::binary | ofstream::binary);

		//init
		_pages = new vector<Page*>();
		_pages->reserve(1000);
		_address = new vector<long long>();
		_address->reserve(1000);
		_currentPage = NULL;

		//write PDF head
		ofstream& f = *(this->_file);
		//long position = f.tellp();
		f<<"%PDF-1.6"<<endl;

		_address->push_back(0);

		//set flag
		this->_opened = true;
	}

	Document::~Document(){

		if(_opened)
		{
			Close();
		}

		if(this->_file != NULL){
			this->_file->close();
			delete this->_file;
			this->_file = NULL;
		}

		if(_pages != NULL)
		{
			//delete pages
			for(vector<Page*>::iterator i = this->_pages->begin();
				i != _pages->end();
				i++){
					delete *i;
			}

			delete this->_pages;
			this->_pages = NULL;
		}

		if(_address != NULL)
		{
			delete this->_address;
			this->_address = NULL;
		}
	}

	bool Document::Close()
	{
		//check page closed
		if(this->_currentPage != NULL)
		{
			this->_currentPage->End();
			this->_currentPage = NULL;
		}

		//TODO save page catalog, xref and trailer
		ofstream& f = *(this->_file);

		//page tree
		/*
		2 0 obj
		<< /Type /Pages
		/Kids[ 4 0 R
		10 0 R
		24 0 R
		]
		/Count 3
		>>
		endobj
		4 0 obj
		<< /Type /Page
		…Additional entries describing the attributes of this page…
		>>
		endobj
		10 0 obj
		<< /Type /Page
		…Additional entries describing the attributes of this page…
		>>
		endobj
		24 0 obj
		<< /Type /Page
		…Additional entries describing the attributes of this page…
		>>
		endobj
		*/
		int pagesId = _address->size();
		long long pagesLocation = f.tellp();
		_address->push_back(pagesLocation);
		f<<pagesId<<" 0 obj"<<endl;
		f<<"<< /Type /Pages"<<endl;
		f<<"   /Kids[";
		//pages
		int pageCount = _pages->size();
		for(int i = 0; i < pageCount ; i++)
		{
			f<<(i + pagesId + 1)<<" 0 R"<<endl;
		}
		f<<"]"<<endl;
		f<<"/Count "<<pageCount<<endl;
		f<<">>"<<endl<<"endobj"<<endl;

		
		for(vector<Page*>::iterator i = this->_pages->begin();
			i != _pages->end();
			i++){
				int currentPageId = _address->size();
				long long pageLocation = f.tellp();
				_address->push_back(pageLocation);
				f<<currentPageId<<" 0 obj"<<endl<<"<< /Type /Page"<<endl;
				//page content
				/*
				3 0 obj
				<< /Type /Page
				/Parent 4 0 R
				/MediaBox [0 0 612 792]
				/Resources <<
							/ProcSet [/PDF /ImageB]
							/XObject << /Im1 22 0 R >>
				>>
				/Contents 12 0 R
				>>
				endobj
				*/
				f<<"/Parent "<<pagesId<<" 0 R"<<endl;
				f<<"/MediaBox [0 0 "<<(*i)->getWidth()<<" "<<(*i)->getHeight()<<"]"<<endl;
                f<<"/Resources <<"<<endl;
                f<<"             /ProcSet [/PDF /ImageB /ImageC]"<<endl;
                f<<"             /XObject << ";
						//write image xobjects
						vector<StreamHead*>* pageRes = (*i)->getResources();
						for(vector<StreamHead*>::iterator j = pageRes->begin();
							j != pageRes->end();
							j++)
						{
							//write xobjects
							f<<"/"<<(*j)->getName()<<" "<<((*j)->getResourceId())<<" 0 R"<<endl;
						}
					f<<">>"<<endl;
				f<<">>"<<endl;
				//write page content if there are contents
                if((*i)->getContentId() >0){
                    f<<"/Contents "<<(*i)->getContentId()<<" 0 R"<<endl;
                }
				f<<">>"<<endl<<"endobj"<<endl;

		}


		//catalog
		/*
		1 0 obj
		<< /Type /Catalog
		/Pages 2 0 R
		/PageMode /UseNone
		>>
		endobj
		*/
		int catId = _address->size();
		long long catLocation = f.tellp();
		_address->push_back(catLocation);
		f<<catId<<" 0 obj"<<endl;
		f<<"<<"<<endl;
        f<<" /Type /Catalog"<<endl;
		f<<" /Pages "<<pagesId<<" 0 R"<<endl;
		f<<">>"<<endl;
		f<<"endobj"<<endl;

		//xref
		/*
		xref
		0 6
		0000000003 65535 f
		0000000017 00000 n
		0000000081 00000 n
		0000000000 00007 f
		0000000331 00000 n
		0000000409 00000 n
		*/
		
		long long xrefLocation = f.tellp();
		long xrefSize = _address->size();
		f<<"xref"<<endl;
		f<<"0 "<<xrefSize<<endl;
		for(vector<long long>::iterator i = this->_address->begin();
			i != _address->end(); 
			i++)
		{
			//output address
			f.width(10); 
			f.fill('0');
			if( (*i)== 0)
				f<<0<<" 65535 f\r\n";
			else
				f<<*i<<" 00000 n\r\n";
		}

		//trailer

		/*
		trailer
		<< /Size 22
		/Root 2 0 R
		>>
		startxref
		18799
		%%EOF
		*/

		//long long trailerLocation = f.tellp();
		f<<"trailer"<<endl;
		f<<"<< /Size "<<xrefSize <<endl; //object sizes
		f<<"   /Root "<<catId <<" 0 R"<<endl; //catalog reference
		f<<">>"<<endl;
		f<<"startxref"<<endl;
		f<<xrefLocation<<endl;
		f<<"%%EOF"<<endl;

		//close files

		f.close();
		delete this->_file;
		this->_file = NULL;


		//clean

		this->_opened = false;

		return true;
	}



	Page* Document::NewPage(){

		if(this->_currentPage != NULL)
		{
			this->_currentPage->End();
			this->_currentPage = NULL;
		}

		Page* page = new Page(*this);
		this->_currentPage = page;
		_pages->push_back(page);
		return _currentPage;
	}

	Page* Document::getCurrentPage(){
		return _currentPage;
	}

	void Document::closePage(){
		if(_currentPage != NULL)
		{
			_currentPage = NULL;
		}
	}
}


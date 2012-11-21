//
//  PDFDocument.cpp
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

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
		
		this->_file = new ofstream(filename,ofstream::binary | ofstream::binary);

		//init
		_pages = new vector<Page*>();
		_address = new vector<long>();

		//write PDF head
		ofstream& f = *(this->_file);
		long position = f.tellp();
		f<<"%PDF 1.7"<<endl;

		//set flag
		this->_opened = true;
	}

	Document::~Document(){
		if(this->_file != NULL){
			this->_file->close();
			delete this->_file;
			this->_file = NULL;
		}

		if(_pages != NULL)
		{
			//TODO delete pages

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
		long pagesLocation = f.tellp();
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
				long pageLocation = f.tellp();
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
				f<<"/Resources <</ProcSet [/PDF /ImageB]"<<endl;
					f<<"/XObject << ";
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
				//write page content
				f<<"/Contents "<<(*i)->getContentId()<<" 0 R"<<endl;
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
		long catLocation = f.tellp();
		_address->push_back(catLocation);
		f<<catId<<" 0 obj"<<endl;
		f<<"<< /Type /Catalog"<<endl;
		f<<"/Pages "<<pagesId<<" 0 R"<<endl;
		f<<"/PageMode /UseNone"<<endl;
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
		
		long xrefLocation = f.tellp();
		long xrefSize = _address->size();
		f<<"xref"<<endl;
		f<<"0 "<<xrefSize<<endl;
		for(vector<long>::iterator i = this->_address->begin();
			i != _address->end(); 
			i++)
		{
			//output address
			f.width(10);  
			f<<*i<<" 00000 n"<<endl;
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

		long trailerLocation = f.tellp();
		f<<"trailer"<<endl;
		f<<"<< /Size "<<xrefSize <<endl; //object sizes
		f<<"<< /Root "<<catId <<" 0 R"<<endl; //catalog reference
		f<<">>"<<endl;
		f<<"startxref"<<endl;
		f<<xrefLocation<<endl;
		f<<"%%EOF"<<endl;

		//close files

		f.close();
		delete this->_file;
		this->_file = NULL;


		return true;
	}



	Page* Document::StartPage(){
		_currentPage = new Page(*this);
		_pages->push_back(_currentPage);
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


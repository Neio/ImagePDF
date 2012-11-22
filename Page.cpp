//
//  PDFPage.cpp
//  ImagePDF
//
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
#include "Page.h"
#include "Document.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace PDF;
using namespace std;

Page::Page(Document& doc){
	this->doc = &doc;
	heads = new vector<StreamHead*>();
	this->_height = 100;
	this->_width = 200;
	this->currentStream = NULL;
	this->currentStreamHead = NULL;
}

Page::~Page()
{
	for(vector<StreamHead*>::iterator j = heads->begin();
		j != heads->end();
		j++)
	{
		if(*j != NULL)
			delete *j;
	}
	delete heads;
	heads = NULL;
}
void Page::End(){
	//TODO save page content info, which describe how to print the page
	//close stream if stream is not closed
	if(currentStream != NULL)
	{
		closeStream();
	}

	/*
	23 0 obj					% Contents of page
	<< /Length 24 0 R >>
	stream
	q							% Save graphics state
	132 0 0 132 45 140 cm		% Translate to (45,140) and scale by 132
	/Im1 Do						% Paint image
	Q							% Restore graphics state
	endstream
	endobj
	24 0 obj
	33
	endobj
	*/
    
    //if(heads->size() ==0)
    //    this->_pageContentId = -1;
    //else{
    
	this->_pageContentId = doc->_address->size();

	//#define f (*(doc->_file))
	ostream& f = *(doc->_file);
	
	long long location = f.tellp();
	doc->_address->push_back(location);//add page id


	f<<this->_pageContentId<<" 0 obj"<<endl;
	f<<"<< /Length "<<(this->_pageContentId + 1)<<" 0 R >>"<<endl;
	f<<"stream"<<endl;
	long long sizecountStart = f.tellp();
	for(vector<StreamHead*>::iterator j = heads->begin();
		j != heads->end();
		j++)
	{
		(*j)->WriteContent(&f);
	}
	
	long long sizecount = (long long)f.tellp() - sizecountStart;
	f<<"endstream"<<endl<<"endobj"<<endl;

	int sizeId = doc->_address->size();
	doc->_address->push_back(f.tellp());
	f<<sizeId<<" 0 obj"<<endl<<sizecount<<endl<<"endobj"<<endl;
    //}

	doc->closePage();
}

void Page::setWidth(int Width){
	this->_width = Width;
}
void Page::setHeight(int Height){
	this->_height = Height;
}
int Page::getWidth(){
	return this->_width;
}
int Page::getHeight(){
	return this->_height;
}
int Page::getContentId(){
	return _pageContentId;
}
vector<StreamHead*>* Page::getResources(){
	return heads;
}

Stream* Page::NewStream(StreamHead* header,
	StreamEncodeProvider* Provider){

		//close previous stream if not closed
	if(currentStream != NULL)
	{
		closeStream();
	}
		
	Provider->setOstream(doc->_file);
	header->provider = Provider;
	currentStream = new Stream(this, Provider);
	currentStreamHead = header;
	int objectId = doc->_address->size();
	doc->_address->push_back(doc->_file->tellp());
	header->WriteXObjectHead(objectId, doc->_file);

    heads->push_back(header);

	return currentStream;

}

void Page::closeStream(){

	if(currentStream != NULL){
		delete currentStream;
		currentStream = NULL;
	}

	long newid = currentStreamHead->WriteXObjectTail(doc->_file);
	doc->_address->push_back(newid);
	
	currentStreamHead = NULL;
}
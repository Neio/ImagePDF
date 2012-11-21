//
//  PDFPage.cpp
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

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
}
void Page::End(){
	//TODO save page content info, which describe how to print the page
	ofstream& f = *(this->doc->_file);

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
	this->_pageContentId = doc->_address->size();
	doc->_address->push_back(f.tellp());//add page id
	f<<_pageContentId<<" 0 obj"<<endl;
	f<<"<< /Length "<<(_pageContentId + 1)<<" 0 R >>"<<endl;
	f<<"stream"<<endl;
	long sizecountStart = f.tellp();
	for(vector<StreamHead*>::iterator j = heads->begin();
		j != heads->end();
		j++)
	{
		(*j)->WriteContent(&f);
	}
	
	long sizecount = (long)f.tellp() - sizecountStart;
	f<<"endstream"<<endl<<"endobj"<<endl;

	int sizeId = doc->_address->size();
	doc->_address->push_back(f.tellp());
	f<<sizeId<<" 0 obj"<<endl<<sizecount<<endl<<"endobj"<<endl;
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

Stream* Page::StartStream(StreamHead& header,
	StreamEncodeProvider& Provider){
		
	Provider.setOstream(doc->_file);
	currentStream = new Stream(this, &Provider);
	currentStreamHead = &header;
	int objectId = doc->_address->size();
	header.WriteXObjectHead(objectId, doc->_file);
	return currentStream;

}

void Page::closeSteram(){
	currentStreamHead->WriteXObjectTail(doc->_file);
	if(currentStream != NULL){
		delete currentStream;
		currentStream = NULL;
	}
	currentStreamHead = NULL;
}
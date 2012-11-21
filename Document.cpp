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

}


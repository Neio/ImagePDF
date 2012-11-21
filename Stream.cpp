//
//  Stream.cpp
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#include "Stream.h"
#include "Page.h"
#include "StreamEncodeProvider.h"

using namespace std;
using namespace PDF;

Stream::Stream(Page* page, StreamEncodeProvider* encoder)
{
	this->page = page;
	this->encoder = encoder;

	this->encoder->Begin();
}

void Stream::End(){
	this->encoder->End();
	this->encoder = NULL;
	this->page->closeSteram();
	this->page = NULL;
}

void Stream::WriteData(char* data, int length){
	encoder->WriteData(data,length);
}

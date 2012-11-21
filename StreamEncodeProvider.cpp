//
//  StreamEncodeProvider.cpp
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#include "StreamEncodeProvider.h"
using namespace PDF;

void StreamEncodeProvider::setOstream(ostream* stream){
	this->output = stream;
}
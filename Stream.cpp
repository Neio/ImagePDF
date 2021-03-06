//
//  Stream.cpp
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

Stream::~Stream()
{
	if(this->encoder != NULL)
	{
		this->encoder->End();
		this->encoder = NULL;
	}
}


void Stream::End(){
	
	this->page->closeStream();
	//this->page = NULL; //because this class has been deleted
}

/*
Write a block of data
If you are using DCTEncoder, please input data with the length 
which is exactly the whole lines
*/
void Stream::WriteData(unsigned  char* data, unsigned long length){
	encoder->WriteData(data,length);
}

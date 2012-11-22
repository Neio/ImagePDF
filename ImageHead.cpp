//
//  ImageHead.cpp
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

#include "ImageHead.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>



using namespace PDF;
using namespace std;

StreamHead::~StreamHead(){
    delete this->provider;
	this->provider = NULL;
}

static int nameCounting = 1;
static string constName = "im";

size_t ImageHead::getResourceId(){
	return id;
}


string ImageHead::getName(){
	return *this->name;
}

ImageHead::ImageHead(int TargetX, int TargetY, int TargetWidth, int TargetHeight, 
	int ImageWidth,
	int ImageHeight,
	ColorSpace colorspace,int BitPerComponent){
	this->x = TargetX;
	this->y = TargetY;
	this->width = TargetWidth;
	this->height = TargetHeight;
	this->imageHeight = ImageHeight;
	this->imageWidth = ImageWidth;
	this->colorSpace = colorspace;
	this->bit = BitPerComponent;
	nameId = nameCounting ++;

	stringstream ss;
	ss<<constName;
	ss<<this->nameId;
	this->name = new string( ss.str());
}

ImageHead::~ImageHead()
{
	delete this->name;
	this->name = NULL;
	
}

//write page content
void ImageHead::WriteContent(ostream* file)
{
	ostream& f = *(file);
	f<<"q"<<endl; //save graphics state
	f<<this->width<<" 0 0 "<<this->height<<" "<<this->x <<" "<<this->y<<" cm"<<endl; //translate to x y
	f<<"/"<<this->getName()<<" Do"<<endl;   //paint image
	f<<"Q"<<endl; //restore graphics state

}

/*
22 0 obj% Image XObject
<< /Type /XObject
/Subtype /Image
/Width 256
/Height 256
/ColorSpace /DeviceGray
/BitsPerComponent 8
/Length 83183
/Filter /ASCII85Decode
>>
stream
9LhZI9h\GY9i+bb;,p:e;G9SP92/)X9MJ>^:f14d;,U(X8P;cO;G9e];c$=k9Mn\]
…Image data representing 65,536 samples…
8P;cO;G9e];c$=k9Mn\]~>
endstream
endobj
*/

void ImageHead::WriteXObjectHead(size_t objectId, ostream* file){
	this->id = objectId;
	ostream& f = *(file);
	f<<this->id<<" 0 obj"<<endl;
	f<<"<</Type /XObject"<<endl;
	f<<"/Subtype /Image"<<endl;
	f<<"/Width "<<this->imageWidth<<endl;
	f<<"/Height "<<this->imageHeight<<endl;
	f<<"/ColorSpace /";
	if(this->colorSpace == DeviceRGB)
		f<<"DeviceRGB"<<endl;
	else if(this->colorSpace == DeviceCMYK)
		f<<"DeviceCMYK"<<endl;
	else if(this->colorSpace == DeviceGray)
		f<<"DeviceGray"<<endl;
	else if(this->colorSpace == DeviceN)
		f<<"DeviceN"<<endl;
	else
		f<<"DeviceN"<<endl;

	f<<"/BitsPerComponent "<<this->bit<<endl;
	f<<"/Length "<<(objectId +1)<<" 0 R"<<endl;
	f<<"/Filter /"<<provider->getName()<<endl;
	f<<">>"<<endl;
	f<<"stream"<<endl;
	this->streamStart = f.tellp();
			
	//	f<<"endstream"<<endl;
	//f<<"endobj"<<endl;
}

size_t ImageHead::WriteXObjectTail(ostream* file){

	ostream& f = *(file);

	long long size = (long long)f.tellp() - (this->streamStart);
	f<<endl<<"endstream"<<endl;
	f<<"endobj"<<endl;

	size_t newid = f.tellp();

	f<<(id+1)<<" 0 obj"<<endl;
	f<<size<<endl;
	f<<"endobj"<<endl;

	return newid;
}
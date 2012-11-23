// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\imagepdf.h"


using namespace std;
using namespace PDF;

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Star test!\n";
    
    string filename = "test.pdf";
    Document doc(filename);
	Page* page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

	//sample data
	const unsigned long size = 40 * 10 * 3;
	unsigned char data[size];
    memset(data, 0x01 ,size * sizeof(char));

	//example using ASCII encoding
	Stream* s =  page->NewStream(
		new ImageHead(10,10,200,50, 40,10, PDF::DeviceRGB,8), 
		new ASCIIEncoder());
	s->WriteData(data, size);


	//start a new page
	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

	//example using Flate/zlib encoding
    s =  page->NewStream(
		new ImageHead(10,10,300,100, 40,10, PDF::DeviceRGB,8), 
		new FlateEncoder(9));
	s->WriteData(data, size/3);
	s->WriteData(data, size/3);
	s->WriteData(data, size/3);


	//example using JPEG/DCT encoding
	s =page->NewStream(
		new ImageHead(10,100,400,100, 40,10, PDF::DeviceRGB,8), 
		new DCTEncoder(40,10, 10, 3, PDF::DCT_RGB));
   
	s->WriteData(data, size/2);
	s->WriteData(data, size/2);
	
	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);


	doc.Close();
    std::cout << "Output finished!\n";
	

	return 0;
}


// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\imagepdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	 srand ( time(NULL) );
	const unsigned long size = 80 * 20 * 3;
	unsigned char data[size];
	for(unsigned long i = 0; i<size; i++)
	{
		data[i] = rand() % 255;
	}

	//example using ASCII encoding
	Stream* s =  page->NewStream(
		new ImageHead(0,0,600,800, 40,40, PDF::DeviceRGB,8), 
		new ASCIIEncoder());
	s->WriteData(data, size);


	//start a new page
	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

	//example using Flate/zlib encoding
    s =  page->NewStream(
		new ImageHead(10,10,400,100, 80,20, PDF::DeviceRGB,8), 
		new FlateEncoder(9));
	s->WriteData(data, size/3);
	s->WriteData(data + size/3, size/3);
	s->WriteData(data + size/3 + size/3, size/3);


	//example using JPEG/DCT encoding
	s =page->NewStream(
		new ImageHead(10,100,400,100, 80,20, PDF::DeviceRGB,8), 
		new DCTEncoder(80,20, 90, 3, PDF::DCT_RGB));
   
	//s->WriteData(data, size);

	s->WriteData(data, size/2);
	s->WriteData(data + size/2, size/2);


	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);


	doc.Close();
    std::cout << "Output finished!\n";
	

	return 0;
}


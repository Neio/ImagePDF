// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\ImageHead.h"
#include "..\..\Document.h"
#include "..\..\FlateEncoder.h"
#include "..\..\StreamEncodeProvider.h"
#include "..\..\StreamHead.h"
#include "..\..\ASCIIEncoder.h"
#include <iostream>
#include <string>

using namespace std;
using namespace PDF;

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Hello, World!\n";
    
    string filename = "test.pdf";
    Document doc(filename);
	Page* page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

	//sample data
	const unsigned long size = 40 * 10 * 3;
	unsigned char data[size];
    memset(data, 0x01 ,size * sizeof(char));

	Stream* s =  page->NewStream(
		new ImageHead(10,10,200,50, 40,10, PDF::DeviceRGB,8), 
		new ASCIIEncoder());
   
	s->WriteData(data, size);

	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

    s =  page->NewStream(
		new ImageHead(10,10,300,100, 40,10, PDF::DeviceRGB,8), 
		new FlateEncoder());
	s->WriteData(data, size/3);
	s->WriteData(data, size/3);
	s->WriteData(data, size/3);

	s =page->NewStream(
		new ImageHead(10,100,400,100, 40,10, PDF::DeviceRGB,8), 
		new FlateEncoder());
   
	s->WriteData(data, size);


	doc.Close();
    std::cout << "Output finished!\n";
	

	return 0;
}


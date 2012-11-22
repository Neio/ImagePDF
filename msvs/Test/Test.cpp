// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\ImageHead.h"
#include "..\..\Document.h"
#include "..\..\FlateEncoder.h"
#include "..\..\StreamEncodeProvider.h"
#include "..\..\StreamHead.h"
#include <iostream>
#include <string>

using namespace std;
using namespace PDF;

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Hello, World!\n";
    
    string filename = "test.pdf";
    Document doc(filename);
	Page* page = doc.StartPage();
    page->setHeight(800);
    page->setWidth(600);

	const int size = 40 * 10 * 3;
	char data[size];
    memset(data, 0x77 ,size * sizeof(char));

	Stream* s =  page->StartStream(
		new ImageHead(10,10,200,50, 40,10, PDF::DeviceRGB,8), 
		new FlateEncoder());
   
	s->WriteData(data, size);
	s->End();
		
	page->End();

	page = doc.StartPage();
    page->setHeight(800);
    page->setWidth(600);

	
    
    s =  page->StartStream(
		new ImageHead(10,10,400,100, 40,10, PDF::DeviceRGB,8), 
		new FlateEncoder());
   
	s->WriteData(data, size);
	s->End();
    page->End();                                  
    
	doc.Close();
    
	//delete s;
    
    std::cout << "Output finished!\n";
	

	return 0;
}


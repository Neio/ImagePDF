//
//  main.cpp
//  PDFTest
//
//  Created by 周聪辉 on 11/21/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#include <iostream>
#include "Document.h"
#include "FlateEncoder.h"
#include "ImageHead.h"
#include "Page.h"
#include <string>
#include <iostream>

using namespace std;
using namespace PDF;

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    
    string filename = "test.pdf";
    Document doc(filename);
    
    //new page
	Page* page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);
    
    //image data
    const int size = 10 * 10 * 3;
	unsigned char data[size];
    memset(data, 0x01 ,size);
	
    
    ImageHead* header = new ImageHead(
                           10,10,200,100,
                           10,10, PDF::DeviceRGB,8);
	FlateEncoder* encoder = new FlateEncoder();
	Stream* s =  page->NewStream(header, encoder);
    
	s->WriteData(data, size);
    
    
    s =  page->NewStream(new ImageHead(
                                       200,200,200,200,
                                       10,10,
                                       PDF::DeviceRGB,8)
                         ,new FlateEncoder());
    s->WriteData(data, size);


    
    page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);
    
    
    s =  page->NewStream(
                    new ImageHead(
                                10,10,200,200,
                                10,10,
                                  PDF::DeviceRGB,8)
                    , new FlateEncoder());
    
    s->WriteData(data, size);
    
    s =  page->NewStream(
                         new ImageHead(
                                       10,200,200,200,
                                       10,10,
                                       PDF::DeviceRGB,8)
                         , new FlateEncoder());
    
    s->WriteData(data, size);
    
    
    s =  page->NewStream(
                new ImageHead(
                       200,200,200,200,
                       10,10,
                       PDF::DeviceRGB,8)
             ,new FlateEncoder());
    
    s->WriteData(data, size);
    
    
	doc.Close();
    
	//delete s;    
    std::cout << "Output finished!\n";
	
    
    return 0;
}


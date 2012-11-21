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
	Page* page = doc.StartPage();
    page->setHeight(800);
    page->setWidth(600);
	
    
    ImageHead* header = new ImageHead(
                           10,10,10,10, PDF::DeviceRGB,8);
	FlateEncoder* encoder = new FlateEncoder();
	Stream* s =  page->StartStream(header, encoder);
    const int size = 10 * 10 * 3;
	char data[size];
    memset(data, 0xEE ,size);
	s->WriteData(data, size);
	s->End();
    
    
	page->End();
                                      
    
	doc.Close();
    
	//delete s;
	delete encoder;
    
    delete header;
    
    std::cout << "Output finished!\n";
	
    
    return 0;
}


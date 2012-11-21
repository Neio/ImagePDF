//
//  PDFDocument.h
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#ifndef __ImagePDF__PDFDocument__
#define __ImagePDF__PDFDocument__

#include <iostream>
#include <string>
#include <vector>
#include "Page.h"
#include "Stream.h"
using namespace std;

namespace PDF
{
    

class Document
{

public:
	Document(string& filename);
	~Document();
    
public:
    //start a new page for operation
    Page* StartPage();
    
    //get current operating page
    Page* getCurrentPage();
    
    /*Finish & close File*/
    bool Close();
    
    
private:
    
    //identify whether file opened
    bool _opened;
    
    //current page
    Page* _currentPage;
    
    //current id
    int _currentId;
    
    //file handle
    ofstream* _file;
    
    //page catalog
    vector<Page*>* _pages;
    
    //object reference
    vector<long>* _address;
    
    void closePage();

    friend class Page;
	friend class Stream;
    

    
};
    
}

#endif /* defined(__ImagePDF__PDFDocument__) */

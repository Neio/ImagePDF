//
//  PDFDocument.h
//  ImagePDF
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
    
    
    //page catalog
    vector<Page*>* _pages;
    
    //object reference
    vector<long long>* _address;
    
    void closePage();

    friend class Page;
	friend class Stream;

	
    //file handle
    ofstream* _file;
    

    
};
    
}

#endif /* defined(__ImagePDF__PDFDocument__) */

//
//  PDFPage.h
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#ifndef __ImagePDF__PDFPage__
#define __ImagePDF__PDFPage__

#include <iostream>
#include <string>
#include "Stream.h"
#include "StreamHead.h"
#include "ImageFile.h"
#include <vector>

using namespace std;

namespace PDF
{

    class Page
    {
    public:
        void End();
        
    public:
        
        
        int Write(int data);
        int Write(bool data);
        int Write(string& data);
        
        
        int Write(ImageFile& imageFile);
        
        Stream* StartStream(StreamHead& header);
        
        
    private:
        
        int _id;  //page id
        
        vector<int> _children; //children ids
        
    private:
        Stream* currentStream;
        void closeSteram();
        
        friend class Stream;
    };
}
#endif /* defined(__ImagePDF__PDFPage__) */

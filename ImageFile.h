//
//  ImageFile.h
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#ifndef __ImagePDF__ImageFile__
#define __ImagePDF__ImageFile__

#include <iostream>
#include <string>
using namespace std;

namespace PDF
{
    class ImageFile
    {
    public:
        
        //deal with JPEG image file only
        ImageFile(string& file);
        
        int Read(char* data, int readlength);
    };

}
#endif /* defined(__ImagePDF__ImageFile__) */

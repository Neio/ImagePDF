//
//  StreamEncodeProvider.h
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#ifndef __ImagePDF__StreamEncodeProvider__
#define __ImagePDF__StreamEncodeProvider__

#include <iostream>

#include <string>
using namespace std;

namespace PDF
{
    class StreamEncodeProvider
    {
    public:
        virtual string getName();
       
    };
    
}

#endif /* defined(__ImagePDF__StreamEncodeProvider__) */

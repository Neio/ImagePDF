//
//  Stream.h
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#ifndef __ImagePDF__Stream__
#define __ImagePDF__Stream__

#include <iostream>

namespace PDF
{
    class Stream{
        
    public:
        void WriteData(char* data, int length);
        
        void End();
    
    };
}

#endif /* defined(__ImagePDF__Stream__) */

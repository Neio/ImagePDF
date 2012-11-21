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
#include <fstream>
#include "StreamEncodeProvider.h"
using namespace std;

namespace PDF
{
	extern class Page;
	extern class Document;

    class Stream{
        
	private :

		Stream(Page* page, StreamEncodeProvider* encoder);
		friend class Page;
    public:


        void WriteData(char* data, int length);
        
        void End();
    
	private:
		Page* page;
		StreamEncodeProvider* encoder;
    };
}

#endif /* defined(__ImagePDF__Stream__) */

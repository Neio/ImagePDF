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
#include <fstream>
#include <string>
using namespace std;

namespace PDF
{
    class StreamEncodeProvider
    {
    public:
		void setOstream(ostream* stream);
        virtual string getName() = 0;
		virtual void Begin() = 0;
		virtual void WriteData(char* data, int length) = 0;
        virtual void End() = 0;
	protected:
		ostream* output;
    };
    
}

#endif /* defined(__ImagePDF__StreamEncodeProvider__) */

//
//  Stream.h
//  ImagePDF
//
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
#ifndef __ImagePDF__Stream__
#define __ImagePDF__Stream__

#include <iostream>
#include <fstream>
#include "StreamEncodeProvider.h"
using namespace std;

namespace PDF
{
	 class Page;
	 class Document;

    class Stream{
        
	private :

		Stream(Page* page, StreamEncodeProvider* encoder);
		~Stream();
		friend class Page;
    public:


        void WriteData(unsigned char* data, unsigned long length);
        
        void End();
    
	private:
		Page* page;
		StreamEncodeProvider* encoder;
    };
}

#endif /* defined(__ImagePDF__Stream__) */

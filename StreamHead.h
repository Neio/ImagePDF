//
//  StreamHead.h
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
#ifndef __ImagePDF__StreamHead__
#define __ImagePDF__StreamHead__

#include <iostream>
#include <string>
#include "StreamEncodeProvider.h"
using namespace std;

namespace PDF
{
    class Page;
    class Stream;

    class StreamHead
    {
	public:
		virtual size_t getResourceId()=0;
		virtual string getName()=0;

	protected:
		virtual void WriteContent(ostream* file) = 0; 
		virtual void WriteXObjectHead(size_t objectId, ostream* file) = 0;
		virtual long long WriteXObjectTail(ostream* file) = 0;
		friend class Page;
		
		StreamEncodeProvider* provider;
        
        virtual ~StreamHead();
    };
}

#endif /* defined(__ImagePDF__StreamHead__) */

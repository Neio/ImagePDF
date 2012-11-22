//
//  FlateEncoder.h
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

#ifndef __ImagePDF__FlateEncoder__
#define __ImagePDF__FlateEncoder__

#include <iostream>
#include "StreamEncodeProvider.h"
#include <string>
#include "zlib/zlib.h"
using namespace std;

namespace PDF
{
	#define CHUNK 16384

    class FlateEncoder: public StreamEncodeProvider
    {
    public:
        virtual string getName();
		virtual void Begin();
		virtual void WriteData(unsigned  char* data, unsigned long length);
        virtual void End();
	private:
		unsigned have;
		z_stream strm;
		unsigned char out[CHUNK];
    };
    
}

#endif /* defined(__ImagePDF__FlateEncoder__) */

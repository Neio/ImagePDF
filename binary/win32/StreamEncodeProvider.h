//
//  StreamEncodeProvider.h
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
		virtual void WriteData(unsigned char* data, unsigned long length) = 0;
        virtual void End() = 0;
        
        
        
        virtual ~StreamEncodeProvider();
        

	protected:
        
        ostream* output;
    };
    
}

#endif /* defined(__ImagePDF__StreamEncodeProvider__) */

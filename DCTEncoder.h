//
//  JPXEncoder.h
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

#ifndef __ImagePDF__JPXEncoder__
#define __ImagePDF__JPXEncoder__

#include <iostream>
#include "StreamEncodeProvider.h"
#include <string>
using namespace std;

namespace PDF
{
    class DCTEncoder:  public StreamEncodeProvider
    {
    public:
        virtual string getName();
		virtual void Begin();
		virtual void WriteData(char* data, int length);
        virtual void End();
        
    };
    
}

#endif /* defined(__ImagePDF__JPXEncoder__) */

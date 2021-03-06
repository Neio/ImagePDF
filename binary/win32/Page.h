//
//  PDFPage.h
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

#ifndef __ImagePDF__PDFPage__
#define __ImagePDF__PDFPage__

#include <iostream>
#include <string>
#include "Stream.h"
#include "StreamHead.h"
#include "ImageFile.h"
#include "StreamEncodeProvider.h"
#include <vector>

using namespace std;

namespace PDF
{
    class Document;

    class Page
    {
    
	private:
		Page(Document& doc);

        ~Page();

	public:
        void End(); 
        
    public:
		void setWidth(int Width);
		void setHeight(int Height);
        int getWidth();//in pixel
		int getHeight();//int pixel
        
        int Write(ImageFile& imageFile);
        
        Stream* NewStream(StreamHead* header, StreamEncodeProvider* Provider);



	protected:
		//access from Document
		size_t getContentId();
		
		vector<StreamHead*>* getResources();
        
    private:
        
		size_t _pageContentId;
        
    private:
        Stream* currentStream;
		StreamHead* currentStreamHead;
		vector<StreamHead*>* heads;

        void closeStream();
		int _height;
		int _width;
		
        friend class Document;
        friend class Stream;

		Document* doc;
    };
}
#endif /* defined(__ImagePDF__PDFPage__) */

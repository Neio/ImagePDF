//
//  PDFPage.h
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#ifndef __ImagePDF__PDFPage__
#define __ImagePDF__PDFPage__

#include <iostream>
#include <string>
#include "Stream.h"
#include "StreamHead.h"
#include "ImageFile.h"
#include <vector>

using namespace std;

namespace PDF
{
	extern class Document;

    class Page
    {
    
	protected:
		Page(Document& doc);

	public:
        void End(); 
        
    public:
		void setWidth(int Width);
		void setHeight(int Height);
        int getWidth();//in pixel
		int getHeight();//int pixel
        
        int Write(ImageFile& imageFile);
        
        Stream* StartStream(StreamHead& header);

        


	protected:
		//access from Document
		int getContentId();
		
		vector<StreamHead*>* getResources();
        
    private:
        
		int _pageContentId;
        
        vector<int> _children; //children ids
        
    private:
        Stream* currentStream;
		StreamHead* currentStreamHead;
		vector<StreamHead*>* heads;

        void closeSteram();
		int _height;
		int _width;

		
        friend class Document;
        friend class Stream;

		Document* doc;
    };
}
#endif /* defined(__ImagePDF__PDFPage__) */

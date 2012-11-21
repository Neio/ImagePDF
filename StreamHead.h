//
//  StreamHead.h
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#ifndef __ImagePDF__StreamHead__
#define __ImagePDF__StreamHead__

#include <iostream>
#include <string>
using namespace std;

namespace PDF
{
	extern class Page;
	extern class Stream;

    class StreamHead
    {
	public:
		int getResourceId();
		string getName();

	private:
		virtual void WriteContent(ofstream* file) = 0; 
		virtual void WriteXObjectHead(int objectId, ofstream* file) = 0;
		virtual void WriteXObjectTail(ofstream* file) = 0;
		friend class Page;
    };
}

#endif /* defined(__ImagePDF__StreamHead__) */

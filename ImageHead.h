//
//  ImageHead.h
//  ImagePDF
//
//  Created by 周聪辉 on 11/20/12.
//  Copyright (c) 2012 Neio. All rights reserved.
//

#ifndef __ImagePDF__ImageHead__
#define __ImagePDF__ImageHead__

#include <iostream>
#include <string>
#include "StreamHead.h"
#include "StreamEncodeProvider.h"

namespace PDF
{

	enum ColorSpace{

		//Device
			DeviceGray, 
			DeviceRGB, 
			DeviceCMYK,

		//CIE-based
			CalGray,
			CalRGB,
			Lab,
			ICCBased,

		//Special
			Indexed,
			Pattern,
			Separation,
			DeviceN
			
	};

	extern class Page;
    class ImageHead :StreamHead
    {
	public:
		ImageHead(int X, int Y, int Width, int Height,
			ColorSpace colorspace, int BitPerComponent,
			StreamEncodeProvider& provider);
		virtual int getResourceId();
		virtual string getName();

	private:
		virtual void WriteContent(ostream* file);
		virtual void WriteXObjectHead(int objectId, ostream* file);
		virtual void WriteXObjectTail(ostream* file);

		friend class Page;

	private:
		int x;
		int y;
		int width;
		int height;
		ColorSpace colorSpace;
		StreamEncodeProvider* provider;
		int bit;

		int id;
		long streamStart;

		int nameId;
    };

}

#endif /* defined(__ImagePDF__ImageHead__) */

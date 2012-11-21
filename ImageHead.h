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

	private:
		virtual void WriteContent(ofstream* file);
		virtual void WriteXObjectHead(int objectId, ofstream* file);
		virtual void WriteXObjectTail(ofstream* file);

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
    };

}

#endif /* defined(__ImagePDF__ImageHead__) */

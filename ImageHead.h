//
//  ImageHead.h
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

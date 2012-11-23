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

    class Page;
    class ImageHead : public StreamHead
    {
	public:
		ImageHead(int TargetX, int TargetY, int TargetWidth, int TargetHeight, 
				int ImageWidth,
				int ImageHeight,
			ColorSpace colorspace, int BitPerComponent);
		
		virtual size_t getResourceId();
		virtual string getName();

	protected:
		~ImageHead();
		virtual void WriteContent(ostream* file);
		virtual void WriteXObjectHead(size_t objectId, ostream* file);
		virtual long long WriteXObjectTail(ostream* file);

		friend class Page;

	private:
		int x;
		int y;
		int width;
		int height;
		
		int imageWidth;
		int imageHeight;
		ColorSpace colorSpace;
		
		int bit;

		size_t id;
		long long streamStart;

		int nameId;
		string* name;
    };

}

#endif /* defined(__ImagePDF__ImageHead__) */

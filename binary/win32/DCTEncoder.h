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
#include "jpeglib.h"


using namespace std;

namespace PDF
{

	typedef enum {
		DCT_UNKNOWN,		/* error/unspecified */
		DCT_GRAYSCALE,		/* monochrome */
		DCT_RGB,		/* red/green/blue */
		DCT_YCbCr,		/* Y/Cb/Cr (also known as YUV) */
		DCT_CMYK,		/* C/M/Y/K */
		DCT_YCCK		/* Y/Cb/Cr/K */
	} DCT_COLOR_SPACE;

    class DCTEncoder:  public StreamEncodeProvider
    {

	public:
		/*
		ImageWidth
		ImageHeight
		Quality Image quality [0...100]
		Components image components, default is 3.
		ColorSpace color space, CMYK, GRAYSCALE or RGB
		*/
		DCTEncoder(
			int ImageWidth, int ImageHeight, 
			int Quality, 
			int Components, DCT_COLOR_SPACE ColorSpace);

    public:
        virtual string getName();
		virtual void Begin();
		virtual void WriteData(unsigned  char* data, unsigned long length);
        virtual void End();
        
    private:

		/* Master record for a compression instance */
        jpeg_compress_struct cinfo;

		/* Error handler object */
        jpeg_error_mgr jerr;

		/* Data destination object for compression */
        jpeg_destination_mgr dmgr;

		/* Image Quality*/
        int quality;

        int image_width;
        int image_height;
		int components; 
		DCT_COLOR_SPACE colorSpace;

		/* This is what we put data*/
		JOCTET * out_buffer;
    };
    
}

#endif /* defined(__ImagePDF__JPXEncoder__) */

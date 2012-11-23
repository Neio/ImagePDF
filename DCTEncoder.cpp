//
//  JPXEncoder.cpp
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
#include "DCTEncoder.h"
#include "lib/jpeglib.h"

using namespace PDF;
using namespace std;

DCTEncoder::DCTEncoder(int ImageWidth, int ImageHeight, int Quality, int Components, DCT_COLOR_SPACE ColorSpace)
{
	this->image_width = ImageWidth;
	this->image_height = ImageHeight;
	this->quality = Quality;
	this->components = Components;
	this->colorSpace = DCT_RGB;
}


string DCTEncoder::getName()
{
	return "DCTDecode";
}

/* setup the buffer but we did that in the main function */
void init_buffer(jpeg_compress_struct* cinfo) {}

/* what to do when the buffer is full; this should almost never
 * happen since we allocated our buffer to be big to start with
 */
boolean empty_buffer(jpeg_compress_struct* cinfo) {
	return TRUE;
}

/* finalize the buffer and do any cleanup stuff */
void term_buffer(jpeg_compress_struct* cinfo) {}


void DCTEncoder::Begin()
{
	//prepare space & file
    
    /* create our in-memory output buffer to hold the jpeg */
	out_buffer  = new JOCTET[image_width * image_height * components];
    
	/* here is the magic */
	dmgr.init_destination    = init_buffer;
	dmgr.empty_output_buffer = empty_buffer;
	dmgr.term_destination    = term_buffer;

	dmgr.next_output_byte    = out_buffer;
	dmgr.free_in_buffer      = image_width * image_height * components;
    
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
    
	/* make sure we tell it about our manager */
	cinfo.dest = &dmgr;
    
	cinfo.image_width      = image_width;
	cinfo.image_height     = image_height;
	cinfo.input_components = components;
	cinfo.in_color_space   = (J_COLOR_SPACE)colorSpace;
    
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality (&cinfo, quality, true);
	jpeg_start_compress(&cinfo, true);
    
    
    
	//uint8_t *buffer    = (uint8_t*) image->pixels;
    
}


void DCTEncoder::WriteData(unsigned  char* data, unsigned long length)
{
	JSAMPROW row_pointer;

	//write data one line by one line
	unsigned long height = length / components/image_width;
	
	for(unsigned long i =0 ; i< height; i++)
	{
		row_pointer = (JSAMPROW) &data[i* components*image_width];
		jpeg_write_scanlines(&cinfo, &row_pointer,1);
	}
	

	



}


void DCTEncoder::End()
{

	//finish compression
    jpeg_finish_compress(&cinfo);

	
    //save to file
	int length = cinfo.dest->next_output_byte - out_buffer;
	this->output->write((char*)out_buffer,length);

	//clean up

    jpeg_destroy_compress(&cinfo);
    
	delete[] out_buffer;
    

}
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
	JOCTET * out_buffer   = new JOCTET[image_width * image_height *3];
    
	/* here is the magic */
	dmgr.init_destination    = init_buffer;
	dmgr.empty_output_buffer = empty_buffer;
	dmgr.term_destination    = term_buffer;
	dmgr.next_output_byte    = out_buffer;
	dmgr.free_in_buffer      = image_width * image_height *3;
    
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
    
	/* make sure we tell it about our manager */
	cinfo.dest = &dmgr;
    
	cinfo.image_width      = image_width;
	cinfo.image_height     = image_height;
	cinfo.input_components = 3;
	cinfo.in_color_space   = JCS_RGB;
    
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality (&cinfo, 75, true);
	jpeg_start_compress(&cinfo, true);
    
	JSAMPROW row_pointer;
    
    
	//uint8_t *buffer    = (uint8_t*) image->pixels;
    
}


void DCTEncoder::WriteData(unsigned  char* data, unsigned long length)
{
	//write data
  
    /*
    jpeg_write_scanlines(&cinfo, data, 1);
     
     while (cinfo.next_scanline < cinfo.image_height) {
     row_pointer = (JSAMPROW) &buffer[cinfo.next_scanline * image->pitch];
     jpeg_write_scanlines(&cinfo, &row_pointer, 1);
     }
  */

}


void DCTEncoder::End()
{
	//clean up
    
    jpeg_finish_compress(&cinfo);
    //fclose(outfile);
    
    //jpeg_destroy_compress(&cinfo);
    
    //save to file
    

}
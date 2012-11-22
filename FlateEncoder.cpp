//
//  FlateEncoder.cpp
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
#include "FlateEncoder.h"
#include <string>
#include <iostream>
#include <iomanip>

 //   #include "zlib/zipstream.hpp"
    #include "zlib/zlib.h"
//#include "zlib/zconf.h"



//using namespace zlib_stream;

using namespace PDF;
using namespace std;


int compress2(unsigned char* data, unsigned  long sizeDataOriginal,
	unsigned char* target, unsigned long* actLength)
{
	// So, we'll just play it safe and alloated 1.1x
    // as much memory + 12 bytes (110% original + 12 bytes)


	 int z_result = compress(
        
        target,         // destination buffer,
                                // must be at least
                                // (1.01X + 12) bytes as large
                                // as source.. we made it 1.1X + 12bytes

        actLength,    // pointer to var containing
                                // the current size of the
                                // destination buffer.
                                // WHEN this function completes,
                                // this var will be updated to
                                // contain the NEW size of the
                                // compressed data in bytes.

        data,           // source data for compression
        
        sizeDataOriginal ) ;    // size of source data in bytes

    switch( z_result )
    {
    case Z_OK:
        printf("***** SUCCESS! *****\n");
        break;

    case Z_MEM_ERROR:
        printf("out of memory\n");
        break;

    case Z_BUF_ERROR:
        printf("output buffer wasn't large enough!\n");
        break;
    }

	return z_result;

}


string FlateEncoder::getName(){
	return "FlateDecode";
}

//zip_ostream* zipper;

void FlateEncoder::Begin(){
	//DO nothing
	//zipper = new zip_ostream(*this->output, true /* gzip file*/);
}


void FlateEncoder::WriteData(unsigned  char* data, unsigned long length){
	//write data
	//for(int i = 0; i< length; i++){
	//	short d = (short)data[i] & 0xFF;
	//	(*this->output)<<setfill('0') <<setw(2)<<hex<<d;
	//}
	//(*this->output)<<dec;
	//this->output->write(data, length);
	//zipper->write(data, length);

	
    unsigned long sizeDataCompressed  = (length * 1.1) + 12;
    unsigned char * dataCompressed = (unsigned char*)malloc( sizeDataCompressed );

	if(compress2((unsigned char*)data, length, dataCompressed, &sizeDataCompressed) == 0)
	{
		this->output->write((char*)dataCompressed, sizeDataCompressed);
		free(dataCompressed);
	}
	else
	{
		//throw gzcompress not success
		throw new exception("zlib compress not success");
	}
}


void FlateEncoder::End(){
	//clean up
	//(*this->output)<<dec;
	//zipper->zflush();
	//delete zipper;
	//zipper = NULL;
}
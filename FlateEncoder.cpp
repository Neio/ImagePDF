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



//using namespace zlib_stream;

using namespace PDF;
using namespace std;

#define BUF_SIZE 65535
Bytef zdata[BUF_SIZE];
uLong nzdata = BUF_SIZE;
Bytef  odata[BUF_SIZE];
uLong nodata = BUF_SIZE;

int gzcompress(Bytef *data, uLong ndata, 
	Bytef *zdata, uLong *nzdata)
{
	z_stream c_stream;
	int err = 0;

	if(data && ndata > 0)
	{
		c_stream.zalloc = (alloc_func)0;
		c_stream.zfree = (free_func)0;
		c_stream.opaque = (voidpf)0;
		if(deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 
                    -MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK) return -1;
		c_stream.next_in  = data;
		c_stream.avail_in  = ndata;
		c_stream.next_out = zdata;
		c_stream.avail_out  = *nzdata;
		while (c_stream.avail_in != 0 && c_stream.total_out < *nzdata) 
		{
			if(deflate(&c_stream, Z_NO_FLUSH) != Z_OK) return -1;
		}
        if(c_stream.avail_in != 0) return c_stream.avail_in;
		for (;;) {
			if((err = deflate(&c_stream, Z_FINISH)) == Z_STREAM_END) break;
			if(err != Z_OK) return -1;
		}
		if(deflateEnd(&c_stream) != Z_OK) return -1;
		*nzdata = c_stream.total_out;
		return 0;
	}
	return -1;
}


string FlateEncoder::getName(){
	return "FlateDecode";
}

//zip_ostream* zipper;

void FlateEncoder::Begin(){
	//DO nothing
	//zipper = new zip_ostream(*this->output, true /* gzip file*/);
}


void FlateEncoder::WriteData(char* data, int length){
	//write data
	//for(int i = 0; i< length; i++){
	//	short d = (short)data[i] & 0xFF;
	//	(*this->output)<<setfill('0') <<setw(2)<<hex<<d;
	//}
	//(*this->output)<<dec;
	//this->output->write(data, length);
	//zipper->write(data, length);
	//if(gzcompress((Bytef *)data, length, zdata, &nzdata) == 0)
	//{
	//	this->output->write((char*)zdata, nzdata);
	//}
}


void FlateEncoder::End(){
	//clean up
	//(*this->output)<<dec;
	//zipper->zflush();
	//delete zipper;
	//zipper = NULL;
}
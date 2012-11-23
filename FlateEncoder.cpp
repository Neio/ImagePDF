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
#include "lib/zlib.h"

//#pragma comment(lib,"lib/zlib.lib")


using namespace PDF;
using namespace std;

FlateEncoder::FlateEncoder(int compressQuality)
{
    
    this->quality = compressQuality;
    if(quality >9)
        quality = 9;
}

string FlateEncoder::getName(){
	return "FlateDecode";
}


void FlateEncoder::Begin(){
	//DO nothing

	 /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = deflateInit(&strm, quality);
    if (ret != Z_OK)
        throw new exception();
    
    
}


void FlateEncoder::WriteData(unsigned  char* data, unsigned long length){
	//write data
	strm.avail_in = (unsigned int)length;
	strm.next_in = data;
	strm.avail_out = CHUNK;
    strm.next_out = out;

	int ret = deflate(&strm, Z_NO_FLUSH);    /* no bad return value */
    if(ret == Z_STREAM_ERROR)
	{
		throw new exception();
	}
	have = CHUNK - strm.avail_out;
	this->output->write((char*)out, have);
	
    /*unsigned long sizeDataCompressed  = (length * 1.1) + 12;
    unsigned char * dataCompressed = (unsigned char*)malloc( sizeDataCompressed );

	if(compress2((unsigned char*)data, length, dataCompressed, &sizeDataCompressed) == 0)
	{
		this->output->write((char*)dataCompressed, sizeDataCompressed);
		
	}
	else
	{
		//throw gzcompress not success
		throw new exception("zlib compress not success");
	}

	free(dataCompressed);*/
}


void FlateEncoder::End(){

	unsigned char empty[1];
	strm.avail_in = 0;
	strm.next_in = empty;
	strm.avail_out = CHUNK;
    strm.next_out = out;

	int ret = deflate(&strm, Z_FINISH );    /* no bad return value */
    if(ret == Z_STREAM_ERROR)
	{
		throw new exception();
	}
	have = CHUNK - strm.avail_out;
	this->output->write((char*)out, have);


	deflateEnd(&strm);

	//clean up
}
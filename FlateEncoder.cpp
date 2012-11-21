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
#include "zlib\zipstream.hpp"


using namespace zlib_stream;

using namespace PDF;
using namespace std;

string FlateEncoder::getName(){
	return "FlateDecode";
}

zip_ostream* zipper;

void FlateEncoder::Begin(){
	//DO nothing
	zipper = new zip_ostream(*this->output, true /* gzip file*/);
}


void FlateEncoder::WriteData(char* data, int length){
	//write data
	
	zipper->write(data, length);
}


void FlateEncoder::End(){
	//clean up

	zipper->zflush();
	delete zipper;
	zipper = NULL;
}
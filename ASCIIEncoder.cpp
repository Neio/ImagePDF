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
#include "ASCIIEncoder.h"
#include <string>
#include <iostream>
#include <iomanip>



using namespace PDF;
using namespace std;



string ASCIIEncoder::getName(){
	return "ASCIIHexDecode";
}


void ASCIIEncoder::Begin(){
	//DO nothing
}


void ASCIIEncoder::WriteData(unsigned  char* data, unsigned long length){
	//write data
	for(int i = 0; i< length; i++){
		short d = (short)data[i] & 0xFF;
		(*this->output)<<setfill('0') <<setw(2)<<hex<<d;
	}
	
}


void ASCIIEncoder::End(){
	(*this->output)<<dec;
}
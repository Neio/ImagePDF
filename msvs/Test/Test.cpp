// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\ImageHead.h"
#include "..\..\Document.h"
#include "..\..\FlateEncoder.h"
#include "..\..\StreamEncodeProvider.h"
#include "..\..\StreamHead.h"
#include <iostream>
#include <string>

using namespace std;
using namespace PDF;

int _tmain(int argc, _TCHAR* argv[])
{
	Document doc(string("test.pdf"));
	Page* page = doc.StartPage();
	ImageHead* header = new ImageHead(
		0,0,
		10,1, PDF::DeviceRGB,8);
	FlateEncoder* encoder = new FlateEncoder();
	//Stream* s =  page->StartStream(header, encoder);
	//char data[]= "Hello World";
	//s->WriteData(data, 5);
	//s->End();
	page->End();
	doc.Close();

	//delete s;
	delete encoder;
	

	return 0;
}




ImagePDF
==============================

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

---------------------------------------

Usage:
---------------


using PDF;

```C++

//random sample data
	srand ( time(NULL) );
	const unsigned long size = 80 * 20 * 3;
	unsigned char data[size];
	for(unsigned long i = 0; i<size; i++)
	{
		data[i] = rand() % 255;
	}


	//Create a PDF document
    string filename = "test.pdf";
    Document doc(filename);

	//Create a new page
	Page* page = doc.NewPage();
    page->setHeight(800);	//Set page height
    page->setWidth(600);	//Set page width

	
	//example using ASCII encoding
	Stream* s =  page->NewStream(
		new ImageHead(0,0,600,800, 40,40, PDF::DeviceRGB,8), 
		new ASCIIEncoder());
	s->WriteData(data, size);


	//start a new page
	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

	//example using Flate/zlib encoding
    s =  page->NewStream(
		new ImageHead(10  //Target X
				,10		  //Target Y
				,400		//Target Width
				,100		//Target Height
				, 80		//Image Width
				, 20		//Image Height
				, PDF::DeviceRGB	//Color
				,8),			//Bit per component
		new FlateEncoder(9));	 //use Flate/zlib compression
	s->WriteData(data, size/3);	//write image data
	s->WriteData(data + size/3, size/3);
	s->WriteData(data + size/3 + size/3, size/3);


	//example using JPEG/DCT encoding
	s =page->NewStream(
		new ImageHead(10,100,400,100, 80,20, PDF::DeviceRGB,8), 
		new DCTEncoder(80,20, 90, 3, PDF::DCT_RGB));
   
	//s->WriteData(data, size);

	s->WriteData(data, size/2);
	s->WriteData(data + size/2, size/2);

	//Create a new blank page
	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

	//Close document
	doc.Close();



```

Design:
----------------


#PDF STRUCTURE:

HEAD

BODY

XREF

TRAILER


#Classes Relation:

<pre>
                        ImageFile (currently jpg file only)
                         |
Document  <>---- Page <>-+---- Stream  <>------ StreamHead
                                 <>                ^
                                 |                |
                                 |           +------------+
                                 |           |            |
                                 |       ImageHead     OtherHead
                                 |
                     StreamEncodeProvider
								^
								|
                    +---------------------+------------------------(to be extended)
                    |                     |
    ZlibEncoder(FlateEncoder)       JpegEncoder(JPXEncoder)
	                                        NOTE: JPXEncoder may write the data to a temporary file 
											and then transform to JPEG
</pre>                                        







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

//create a new pdf file and write a header
Document doc("example.pdf");


//start a new page

Page* page = doc.NewPage();  //new page 
page->setHeight(800);	//Set page height
page->setWidth(600);	//Set page width

//insert an image to current page

//not implement it
//int id = page->Write(new ImageObject());


//insert an image stream
Stream* stream =page->NewStream(
		new ImageHead(	10,  //Target X
						10,  //Target Y
						400, //Target Width
						100, //Target Height
						40,	 //Image Width
						10,	 //Image Height
						PDF::DeviceRGB, //Color
						8),  //Bit per component
		new FlateEncoder()); //use Flate/zlib compression

//write image content
stream->Write(data1, length1);
stream->Write(data2, length2);


//new page 
Page* page2 = doc.StartPage();



//write pages/catalog information, xref, trailer
//then close the file
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





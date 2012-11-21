

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

//new page should be start after previous one closed ( End() called )

Page* page = doc.StartPage();


//insert an image to current page

//not implement it

//int id = page->Write(new ImageObject());

//insert an stream

StreamHead sHead = new ImageHead();
StreamEncodeProvider encoder = new FlateEncoder();

Stream* stream = page->StartStream(sHead, encoder);

stream->Write(data1, length1);
stream->Write(data2, length2);

stream->End();


//finish one page
page->End();


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





ImagePDF

Neio Zhou
2012 11 20

==================
Usage:
===================

using PDF;


//create a new pdf file and write a header
PDFDocument doc = PDFDocument.Create("example.pdf");


//start a new page
//new page should be start after previous one closed ( End() called )
Page* page = doc.StartPage();


//insert an image to current page
//not implement it
//int id = page->Write(new ImageObject());

//insert an integer
int id = page->Write(1);

//insert an stream
StreamHead sHead = new ImageHead();
Stream* stream = page->StartStream(sHead);
stream.Write(data1);
stream.Write(data2);
stream.End();



//get next id
int nextid = page->getNextId();

//finish one page
page->End();


//write pages/catalog information, xref, trailer
//then close the file
doc.Close();




==================
DESIGN:
===========
STRUCTURE:

HEAD
BODY
XREF
TRAILER

Classes Relation:

                        ImageFile (currently jpg file only)
                         |
Document  <>---- Page <>-+---- Stream  <>------ StreamHead
                                 |                ^
                                 |                |
                                 |           +------------+
                                 |           |            |
                                 |       ImageHead     OtherHead
                                \ /
                     StreamEncodeProvider
                         ^
                         |
                    +---------------------+------------------------(to be extended)
                    |                     |
    ZlibEncoder(FlateEncoder)       Jpeg2000Encoder(JPXEncoder)
                                        NOTE: JPXEncoder may write the data to a temporary file and then transform to JPEG2000 
                                        





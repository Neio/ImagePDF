// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\imagepdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>

using namespace std;
using namespace PDF;



inline double findnoise(double y)
{			 
 int x = ((int)y<<13) ^(int)y;
 return (double)( 1.0 -((x* (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);	
}



inline double findnoise2(double x,double y)
{
	int n=(int)x+(int)y*57;
	n=(n<<13)^n;
	int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
	return 1.0-((double)nn/1073741824.0);
}

inline double interpolate(double a,double b,double x)
{
 double ft=x * 3.1415927;
 double f=(1.0-cos(ft))* 0.5;
 return a*(1.0-f)+b*f;
}


double noise(double x,double y)
{
 double floorx=(double)((int)x);//This is kinda a cheap way to floor a double integer.
 double floory=(double)((int)y);
 double s,t,u,v;//Integer declaration
 s=findnoise2(floorx,floory); 
 t=findnoise2(floorx+1,floory);
 u=findnoise2(floorx,floory+1);//Get the surrounding pixels to calculate the transition.
 v=findnoise2(floorx+1,floory+1);
 double int1=interpolate(s,t,x-floorx);//Interpolate between the values.
 double int2=interpolate(u,v,x-floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
 return interpolate(int1,int2,y-floory);//Here we use y-floory, to get the 2nd dimension.
}


void RenderCloud(unsigned char* data, int w, int h)
{
	int octaves=2;
	int p =2; //persistent
	int zoom = 75;
	for(int y=0;y<h;y++)
	{//Loops to loop trough all the pixels
		for(int x=0;x<w;x++)
		{
			double getnoise =0;
			for(int a=0;a<octaves-1;a++)//This loops trough the octaves.
			{
		
				double frequency = powf(2,a);//This increases the frequency with every loop of the octave.
				double amplitude = powf(p,a);//This decreases the amplitude with every loop of the octave.
				getnoise += noise(((double)x)*frequency /zoom,
					((double)y)/zoom*frequency)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
			}//			
			//It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1

			int color= (int)((getnoise*128.0)+128.0);//Convert to 0-256 values.
			if(color>255)
				color=255;
			if(color<0)
				color=0;

			data[y*w*3+x*3] = color;
			data[y*w*3+x*3+1] = color;
			data[y*w*3+x*3+2] = color;
		}
	}
}




int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Star test!\n";
    
	//random sample data
	srand ( time(NULL) );
	const unsigned long w = 200;
	const unsigned long h = 200;
	const unsigned long size = w * h * 3;
	unsigned char data[size];
	for(unsigned long i = 0; i<size; i++)
	{
	//	data[i] = rand() % 255;
	}

	RenderCloud(data, w,h);


	//Create a PDF document
    string filename = "test.pdf";
    Document doc(filename);

	//Create a new page
	Page* page = doc.NewPage();
    page->setHeight(800);	//Set page height
    page->setWidth(600);	//Set page width

	
	//example using ASCII encoding
	Stream* s =  page->NewStream(
		new ImageHead(0,0,600,800, w,h, PDF::DeviceRGB,8), 
		new ASCIIEncoder());
	s->WriteData(data, size);


	//start a new page
	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

	


	//example using JPEG/DCT encoding
	s =page->NewStream(
		new ImageHead(0,400,400,400, w,h, PDF::DeviceRGB,8), 
		new DCTEncoder(w,h, 90, 3, PDF::DCT_RGB));
   
	//s->WriteData(data, size);

	s->WriteData(data, size/2);
	s->WriteData(data + size/2, size/2);


	//example using Flate/zlib encoding
    s =  page->NewStream(
		new ImageHead(0  //Target X
				,0		  //Target Y
				,400		//Target Width
				,400		//Target Height
				, w		//Image Width
				, h		//Image Height
				, PDF::DeviceRGB	//Color
				,8),			//Bit per component
		new FlateEncoder(9));	 //use Flate/zlib compression

	const unsigned long piece = size /200;
	for(unsigned long i = 0; i< size; i += piece)
	{
		s->WriteData(data + i, piece);	//write image data
	}
	//Create a new blank page
	page = doc.NewPage();
    page->setHeight(800);
    page->setWidth(600);

	//Close document
	doc.Close();


    std::cout << "Output finished!\n";
	

	return 0;
}


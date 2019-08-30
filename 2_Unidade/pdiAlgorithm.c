#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "image.h"

unsigned char validColor(int c){
	if (c < 0) return 0;
	if (c > 255) return 255;

	return ((unsigned char) c);
}


Image * img_ConvertGray(Image * origImg){
	int x, y;
	unsigned char red, green, blue, gray;
	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));

	if (rImg == NULL)
			return NULL;

	for (y = 0; y < imgGetHeight(origImg); y++)
			{
				for (x = 0; x < imgGetWidth(origImg); x++)
				{
					red = imgGetPixelRed(origImg, x, y);
					green = imgGetPixelGreen(origImg, x, y);
					blue = imgGetPixelBlue(origImg, x, y);

					gray = validColor(0.21*red + 0.71*green + 0.07*blue);

					imgSetPixel(rImg, x, y, gray, gray, gray);
				}
			}

	return rImg;
}

unsigned int * img_GetHistogram (Image * img) {

	unsigned int *hist;
	int i,x,y;
	unsigned char red, green, blue;

	if (img!=NULL ) {
		hist = 	(unsigned int *) malloc (3 * 256 * sizeof(unsigned int) );
		if (hist!=NULL ) {
			//initialization of the histogram
			for ( i=0; i<3*256; i++ )
				hist[i] = 0;
			// calculating the histogram
			for ( y=imgGetHeight(img)-1; y>=0; y-- )
					for ( x=0; x<imgGetWidth(img); x++ )
					{
						red   = imgGetPixelRed(img, x, y);
						hist[red] += 1;
						green = imgGetPixelGreen(img, x, y);
						hist[green+256] += 1;
						blue  = imgGetPixelBlue(img, x, y);
						hist[blue+512] += 1;
					}

		}
	}

	return hist;
}

void printHistogramToConsole(Image * img) {

	unsigned int *hist = img_GetHistogram (img);
	int i = 0;

	for (i=0;i<256;i++)
		printf("[%d]: %d\n",i,hist[i]);
}

Image * img_Blur(Image * origImg, int sizeMask){
	int x, y, m;
	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));

	if (rImg == NULL)
		return NULL;

	int step = (int)(sizeMask/2);
	int squareMask = sizeMask*sizeMask;

	for (y = step; y < imgGetHeight(origImg)-step; y++)
		{
			for (x = step; x < imgGetWidth(origImg)-step; x++)
			{
				m =  imgGetPixelRed(origImg, x-1, y-1) + imgGetPixelRed(origImg, x-1, y) + imgGetPixelRed(origImg, x-1, y+1) +
						imgGetPixelRed(origImg, x, y-1)   + imgGetPixelRed(origImg, x, y)   + imgGetPixelRed(origImg, x, y+1) +
						imgGetPixelRed(origImg, x+1, y-1) + imgGetPixelRed(origImg, x+1, y) + imgGetPixelRed(origImg, x+1, y+1);

				m = (int) ((float) m / (float) squareMask);
				m = validColor(m);

				imgSetPixel(origImg, x, y, m, m, m);

				//setPixelMap( cImage, i, j, ValidCor(m));
			}
		}

	return rImg;
}

Image * lineartranformation(Image * origImg, double A, double B, double a1, double b1, double a2, double b2, double a3, double b3){

	int x,y;
	double v1,v2,v3;
	double c1,c2,c3; 

	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
	
	//Image *rImg = img_ConvertGray(origImg);

	if (rImg == NULL)
        return NULL;
	

	for (y = 0; y < imgGetHeight(origImg); y++){
		for (x = 0; x < imgGetWidth(origImg); x++){
    		
    		v1 = imgGetPixelRed(origImg, x, y);
    		v2 = imgGetPixelGreen(origImg, x, y);
			v3 = imgGetPixelBlue(origImg, x, y);

			if(v1 < A)
				c1 = a1*v1 + b1;
			if(v1 >= A && v1 <= B)
				c1 = a2*v1 + b2;
			if(v1 > B)
				c1 = a3*v1 + b3;
			

			if(v2 < A)
				c2 = a1*v2 + b1;
			if(v2 >= A && v2 <= B)
				c2 = a2*v2 + b2;
			if(v2 > B)
				c2 = a3*v2 + b3;


			if(v3 < A)
				c3 = a1*v3 + b1;
			if(v3 >= A && v3 <= B)
				c3 = a2*v3 + b2;
			if(v3 > B)
				c3 = a3*v3 + b3;

			imgSetPixel(rImg, x, y, validColor (c1), validColor (c2), validColor (c3));    		
		}
	}

	return rImg;
}

Image * img_points(Image * origImg, int opcao, int a, int b){
	int x, y;
    int v1,v2,v3;
    int c1,c2,c3;
	

	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
    Image *rImg2 = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
    
    if (rImg == NULL)
        return NULL;
    if (rImg2 == NULL)
        return NULL;

	switch(opcao){
		case 1:{
			for (y = 0; y < imgGetHeight(origImg); y++){
        		for (x = 0; x < imgGetWidth(origImg); x++){
            		
        		v1 = imgGetPixelGreen(origImg, x, y);
        		v2 = imgGetPixelRed(origImg, x, y);
        		v3 = imgGetPixelBlue(origImg, x, y);

        		c1 = a*log(v1);
        		c2 = a*log(v2);
        		c3 = a*log(v3);
            	
            	imgSetPixel(rImg2, x, y, c1, c2, c3);
        		}
    		}
    		
			return rImg2;
			break;
		}
		case 2:{
			for (y = 0; y < imgGetHeight(origImg); y++){
        		for (x = 0; x < imgGetWidth(origImg); x++){
            		
        		v1 = imgGetPixelRed(origImg, x, y);
        		v2 = imgGetPixelGreen(origImg, x, y);
        		v3 = imgGetPixelBlue(origImg, x, y);

        		c1 = a*(pow(v1,b));
        		c2 = a*(pow(v2,b));
        		c3 = a*(pow(v3,b));
            	
            	imgSetPixel(rImg2, x, y, c1, c2, c3);
        		}
    		}
    		
			return rImg2;
			break;
		}
	}
}
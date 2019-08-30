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
Image * img_points(Image * origImg){
	int opcao;
	int a,b,c;
	int x, y;
    int j,i,soma;
    int v1,v2,v3;
    int c1,c2,c3;
    unsigned char red, green, blue;
	

	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
    Image *rImg2 = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
    Image *rImg3 = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
    
    if (rImg == NULL)
        return NULL;
    if (rImg2 == NULL)
        return NULL;
    if (rImg3 == NULL)
        return NULL;

	printf("Xablau\n");

	printf("Digite:\n1 - Funcao com 1 expoente\n2 - Funcao com 2 expoentes\n");
	scanf("%d",&opcao);

	switch(opcao){
		case 1:{
			printf("Digite os valores da equacao\nA = ");
			scanf("%d",&a);
			printf("B = ");
			scanf("%d",&b);
			printf("%dx + %d\n",a,b);


			for (y = 0; y < imgGetHeight(origImg); y++){
        		for (x = 0; x < imgGetWidth(origImg); x++){
            		
        		v1 = imgGetPixelGreen(rImg, x, y);
        		v2 = imgGetPixelRed(rImg, x, y);
        		v3 = imgGetPixelBlue(rImg, x, y);

        		c1 = a*log(v1);
        		c2 = a*log(v2);
        		c3 = a*log(v3);
            	
            	imgSetPixel(rImg2, x, y, c1, c2, c3);
        		}
    		}
    		

			break;
		}
		case 2:{
			printf("Case 2\n");
			break;
		}
	}


	return rImg2;
}

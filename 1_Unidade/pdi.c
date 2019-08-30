/*
 ============================================================================
 Name        : pdi.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "pdiAlgorithm.h"

int main(void){
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	
	Image *lenaImg = imgReadPPM("./images/lena.ppm");
	
	//imgWritePPM(lenaImg, "./images/lena256color.ppm");

	Image *lenaImgGray = img_ConvertGray(lenaImg);
	//imgWritePPM(lenaImgGray, "./images/lena256Gray.ppm");

	//Image *lenaImgPoints = img_points(lenaImg,2,10,1);
	//imgWritePPM(lenaImgPoints, "./images/lenaPoins.ppm");

	Image *lenaImgTrans = lineartranformation(lenaImgGray,80,200,1,0,2,0,1,0);
	imgWritePPM(lenaImgTrans, "./images/lenatrans.ppm");








	//Image *lenaImgTrans = lineartranformation(lenaImg,128,255,1,1,1,1,1,1);

	//Image *lenaImgTrans = lineartranformation(lenaImg,128,255,1.5,1.5,1.5,1.5,1.5,1.5);
	
	//Image *lenaImgTrans = lineartranformation(lenaImg,128,255,1,1,0,0,0,0);
	
	//Image *lenaImgTrans = lineartranformation(lenaImg,128,255,0,0,1,1,0,0);

	//Image *lenaImgTrans = lineartranformation(lenaImg,128,255,0,0,0,0,1,1);


	//Chamada com a imagem preto e branco
	//Image *lenaImgTrans = lineartranformation(lenaImgGray,128,255,1,1,1,1,1,1);
	
	//Image *lenaImgTrans = lineartranformation(lenaImgGray,128,255,1.5,1.5,1.5,1.5,1.5,1.5);

	

	//Image *lenaImgGrayBlur = img_Blur(lenaImgGray, 3);

	//imgWritePPM(lenaImgGrayBlur, "./images/lena256GrayBlur.ppm");

	//printHistogramToConsole(lenaImg);

	imgDestroy(lenaImg);
	//imgDestroy(lenaImgGray);
	return EXIT_SUCCESS;
}

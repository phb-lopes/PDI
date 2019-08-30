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
#include "morf_oper.h"


int main(void){
	// puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	strTypG str;
	

	// Image *lenacolorida = imgReadPPM("./images/lena.ppm");
	// Image *	lenagray = img_ConvertGray(lenacolorida);
	// Image *saida = imgCreate(imgGetWidth(lenacolorida) , imgGetHeight(lenacolorida));
	


	Image *entrada = imgReadPPM("./images/bola.ppm");
	Image *saida = imgCreate(imgGetWidth(entrada) , imgGetHeight(entrada));
	
	// saida = normal_mapping(lenagray);
	saida = normal_mapping(entrada);
	imgWritePPM(saida, "./images/mapping.ppm");

	return EXIT_SUCCESS;
}

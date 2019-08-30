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
	//puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	strTypG str;
	
	Image *entrada = imgReadPPM("./images/lena120GrayBin.ppm");

	Image *saida = imgCreate(imgGetWidth(entrada) , imgGetHeight(entrada));

	str = creaElemStr(3 , 3, 255, 1,1);
	saida = DilGrayScl(entrada, &str);
	imgWritePPM(saida, "./images/dilatacao.ppm");

	// str = creaElemStr(3 , 3, 255, 1,1);
	// saida = EroGrayScl(entrada, &str);
	// imgWritePPM(saida, "./images/erosao.ppm");

	// str = creaElemStr(3 , 3, 255, 1,1);
	// saida = OpeningGrayScl(entrada, &str);
	// imgWritePPM(saida, "./images/abertura.ppm");

	// str = creaElemStr(3 , 3, 255, 1,1);
	// saida = ClosingGrayScl(entrada, &str);
	// imgWritePPM(saida, "./images/fechamento.ppm");

	return EXIT_SUCCESS;
}

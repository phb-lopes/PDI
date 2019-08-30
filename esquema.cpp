/**********************************************************
 Modulo morf_oper.cpp
 Realiza as operacoes morfologicas na imagem

 Autor  : Wilfredo Blanco Figuerola
**********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "morf_oper.h"

unsigned char Clamp(int color) {
  if ( color < 0 ) 
    return 0;
  else if ( color > 255 ) 
    return 255;
  else
    return (unsigned char) color;
}

int inout(int w, int h){
	int matriz[w][h];
	return *matriz;
}

strTypG creaElemStr(int w, int h, unsigned char cor, int* matp, int rc, int cc){
	int i,j,y = 0, dim;
	strTypG strEl;

	strEl.dim = h*w;
	dim = h*w;

	if(dim != srtEl.dim)
		return NULL;
	
	//verificar se o tamanho de h*w é igual a matriz matp

	if ((strEl.matOper = new rcCor[w*h]) == NULL) {
		printf("Memoria insuficiente\n");
		exit(0);
	}

	
	for(i = -dim/2 ; i <= dim/2 ; i++)
		for(j = -dim/2 ; j <= dim/2 ; j++){
			strEl.matOper[y].r = i;
			strEl.matOper[y].c = j;
			strEl.matOper[y].cor = cor;
			++y;
		}
	return strEl;
}

rcCor *getMatElStr(strTypG *elemStr){
	return elemStr->matOper;
}

void freeElemStr(strTypG *elemStr){
	if (elemStr->matOper != NULL) {
		free(elemStr->matOper);
		elemStr->matOper = NULL;
	}
}

void setCorElemStr(unsigned char cor, strTypG *elemStr){
	int i,j,y = 0;

	if (elemStr==NULL) exit(8);
	for(i=-elemStr->dim/2;i<=elemStr->dim/2; i++)
		for(j=-elemStr->dim/2;j<=elemStr->dim/2; j++) {
			elemStr->matOper[y].cor = cor;
			++y;
		}
}

void DilGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl){
	int r,c,y,x,i,gv,max;

	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) outIm[r*imSizehor + c] = 0;

	for(r=0;r<imSizever;r++) {
		for(c=0;c<imSizehor;c++) {
			max = 0;
			for(i=0;i<strEl->dim*strEl->dim;i++) {
				y = r + strEl->matOper[i].r;
				x = c + strEl->matOper[i].c;
				
				if (y>=0 && x>=0 && y<imSizever && x<imSizehor) {
					gv = inIm[y*imSizehor+x] + strEl->matOper[i].cor;
					
					if (gv > max) 
						max = gv;
				}

			}
			outIm[r*imSizehor + c] = Clamp(max);
		}
	}
}

void EroGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl){
	int r,c,y,x,i,gv,min;

	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) 
			outIm[r*imSizehor + c] = 0;

	for(r=0;r<imSizever;r++) {
		for(c=0;c<imSizehor;c++) {
			min = 32767;
			for(i=0;i<strEl->dim*strEl->dim;i++) {
				y = r + strEl->matOper[i].r;
				x = c + strEl->matOper[i].c;
				if (y>=0 && x>=0 && y<imSizever && x<imSizehor) {
					gv = inIm[y*imSizehor+x] - strEl->matOper[i].cor;
					if (gv < min) 
						min = gv;
				}
			}
			outIm[r*imSizehor + c] = Clamp(min);
		}
	}

}

void OpeningGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl){
	unsigned char *imTemp;
	int r,c;
	
	EroGrayScl(imSizehor, imSizever, inIm, outIm, strEl);

	if ((imTemp = new unsigned char[imSizehor*imSizever]) == NULL) {
		
		printf("Memoria insuficiente\n");
		exit(0);
	}
	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) imTemp[r*imSizehor + c] = outIm[r*imSizehor + c];

	DilGrayScl(imSizehor, imSizever, imTemp, outIm, strEl);
	free(imTemp);
}

void ClosingGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl){
	unsigned char *imTemp;
	int r,c;
	
	DilGrayScl(imSizehor, imSizever, inIm, outIm, strEl);	

	if ((imTemp = new unsigned char[imSizehor*imSizever]) == NULL) {
		
		printf("Memoria insuficiente\n");
		exit(0);
	}
	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) imTemp[r*imSizehor + c] = outIm[r*imSizehor + c];

	EroGrayScl(imSizehor, imSizever, imTemp, outIm, strEl);
	free(imTemp);
}


void SmoothingGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl){
	unsigned char *imTemp;
	int r,c;

	OpeningGrayScl(imSizehor, imSizever, inIm, outIm, strEl);

	if ((imTemp = new unsigned char[imSizehor*imSizever]) == NULL) {
		
		printf("Memoria insuficiente\n");
		exit(0);
	}
	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) imTemp[r*imSizehor + c] = outIm[r*imSizehor + c];

	ClosingGrayScl(imSizehor, imSizever, imTemp, outIm, strEl);
	free(imTemp);
}

void Morf_GradGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl){
	unsigned char *imTemp;
	int r,c;
	
	DilGrayScl(imSizehor, imSizever, inIm, outIm, strEl);

	if ((imTemp = new unsigned char[imSizehor*imSizever]) == NULL) {
		
		printf("Memoria insuficiente\n");
		exit(0);
	}
	//imTemp guarda o resultado da dilatacao
	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) imTemp[r*imSizehor + c] = outIm[r*imSizehor + c];

	EroGrayScl(imSizehor, imSizever, inIm, outIm, strEl);

	unsigned char *imTemp2;
	//imTemp2 guarda o resultado da Erocao
	if ((imTemp2 = new unsigned char[imSizehor*imSizever]) == NULL) {
		printf("Memoria insuficiente\n");
		exit(0);
	}
	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) imTemp2[r*imSizehor + c] = outIm[r*imSizehor + c];

	// Resto imTemp y Imtemp2 -> outIm
	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) outIm[r*imSizehor + c] = Clamp(imTemp[r*imSizehor + c] - imTemp2[r*imSizehor + c]);

	free(imTemp);
	free(imTemp2);
}
  
void Top_hatGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl{
	int r,c;

	OpeningGrayScl(imSizehor, imSizever, inIm, outIm, strEl);

	for(r=0;r<imSizever;r++) 	
		for(c=0;c<imSizehor;c++) 
			outIm[r*imSizehor + c] =Clamp(inIm[r*imSizehor + c] - outIm[r*imSizehor + c]);
}

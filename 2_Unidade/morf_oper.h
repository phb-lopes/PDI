#ifndef MORF_OPER_H
#define MORF_OPER_H 1

#define Dilation	1
#define Erosion		2
#define Opening		3
#define Closing		4
#define MorfGrad	5
#define Smoothing	6
#define Top_hat		7

#include "image.h"

typedef struct {
	int r,c;
	unsigned char cor;
	unsigned char in;
} rcCor;

typedef struct {
	rcCor *matOper;
	int w,h;
	unsigned char rc;
	unsigned char cc;
} strTypG;

//int criarmatriz(int w, int h);
strTypG creaElemStr(int w, int h, unsigned char cor, int rc, int cc);
void freeElemStr(strTypG *elemStr);
void setCorElemStr(unsigned char cor, strTypG *elemStr);
rcCor *getMatElStr(strTypG *elemStr);

Image *DilGrayScl(Image *entrada, strTypG *SrtEl);
Image *EroGrayScl(Image *entrada, strTypG *SrtEl);

Image *OpeningGrayScl(Image *entrada, strTypG *SrtEl);
Image *ClosingGrayScl(Image *entrada, strTypG *SrtEl);

// void OpeningGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);
// void ClosingGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);
void SmoothingGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);
void Morf_GradGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);
void Top_hatGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);

#endif
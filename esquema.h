#ifndef MORF_OPER_H
#define MORF_OPER_H 1

#define Dilation	1
#define Erosion		2
#define Opening		3
#define Closing		4
#define MorfGrad	5
#define Smoothing	6
#define Top_hat		7


typedef struct {
	int r,c;
	unsigned char cor;
	unsigned char in;
} rcCor;

typedef struct {
	rcCor *matOper;
	int w,h;
} strTypG;

strTypG creaElemStr(int w, int h, unsigned char cor,int* matp, int rc, int cc);

void freeElemStr(strTypG *elemStr);
void setCorElemStr(unsigned char cor, strTypG *elemStr);
rcCor *getMatElStr(strTypG *elemStr);

void DilGrayScl(int imSize,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *SrtEl);
void EroGrayScl(int imSize,int imSizever,unsigned char *inIm, unsigned char *outIm, strTypG *SrtEl);

void OpeningGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);
void ClosingGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);
void SmoothingGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);
void Morf_GradGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);
void Top_hatGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl);

#endif
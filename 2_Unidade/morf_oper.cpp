/**********************************************************
 Modulo morf_oper.cpp
 Realiza as operacoes morfologicas na imagem

 Autor  : Wilfredo Blanco Figuerola
*********************************************************/

/*

	g++ pdiAlgorithm.c image.c  pdi.c morf_oper.cpp -o main
	
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "morf_oper.h"
#include "image.h"

unsigned char Clamp(int color) {
  if ( color < 0 ) 
    return 0;
  else if ( color > 255 ) 
    return 255;
  else
    return (unsigned char) color;
}


//largura, altura, cor, row center e coloum center(ponto central do pixel)
strTypG creaElemStr(int w, int h, unsigned char cor, int rc, int cc){
	int i,j,y = 0, dim;
	int matriz[w][h];
	strTypG strEl;

	// Cria o Elemento Estruturante
	if ((strEl.matOper = new rcCor[h*w]) == NULL) {
		printf("Memoria insuficiente\n");
		exit(0);
	}

	// Se as cordenadas do centro forem maior q a dimensao do Elemento Estruturante ou menores q 0 ele da erro
	if((rc > w || cc > h) || (rc < 0 || cc < 0) ){
		printf("Invalid Center\n");
		exit(0);
	}
	strEl.w = w;
	strEl.h = h;
	

	// Faz o elemento generica aqui, por enquanto ta todo mundo 1(todos pertencentes ao elemento)
	for (i = 0; i < w; ++i){
		for (j = 0; j < h; ++j){
			//scanf("%d",&matriz[i][j]);
			matriz[i][j] = 1;
		}	
	}

	// imprime a matriz de presenta com destaque para o valor do centro q ficara entre chaves []
	printf("Matriz de presenca\n");
	for (i = 0; i < w; ++i){
		for (j = 0; j < h; ++j){
			if(rc == i && cc == j)
				printf("[%d]\t", matriz[i][j]);
			else
				printf("%d\t", matriz[i][j]);
		}	
		printf("\n");
	}

	// inicializacao do Elemento Estruturante 
	for(i = 0  ; i < w ; i++){
		for(j = 0  ; j < h ; j++){

			strEl.matOper[y].r = i - rc;
			strEl.matOper[y].c = j - cc;
			strEl.matOper[y].cor = cor;
			strEl.matOper[y].in = matriz[i][j];
			
			++y;
		}
	}
	
	//ponto central do Elemento Estruturante
	strEl.rc = rc;
	strEl.cc = cc;

	return strEl;
}

// imprime o Elemento Estruturante mostrando Colunas , Linhas e Cores
void impimirelstr(strTypG *str){
	int i;
	for (i = 0; i < str->h * str->w; ++i){
		printf("C = %d R = %d\n",str->matOper[i].c,str->matOper[i].r);
	}

	for (i = 0; i < str->h * str->w; ++i){
		printf("Cor = %d \n",str->matOper[i].cor);
	}
}

// Pega o Elemento Estruturante 
rcCor *getMatElStr(strTypG *elemStr){
	return elemStr->matOper;
}

// Libera o Elemento Estruturante da memoria
void freeElemStr(strTypG *elemStr){
	if (elemStr->matOper != NULL) {
		free(elemStr->matOper);
		elemStr->matOper = NULL;
	}
}

// Seta uma cor especifica num ponto especifito do Elemento Estruturante
void setCorElemStr( strTypG *elemStr, unsigned char cor, int x, int y){

	if (elemStr == NULL) 
		exit(8);
	if((x > elemStr->w || y > elemStr->h))
		return;
	
	elemStr->matOper[(x*elemStr->w)+y].cor = cor;
	
}

Image * DilGrayScl(Image *entrada, strTypG *SrtEl){	
	int y, x, i, j, gv, x1, y1;
	printf("DILATACAO\n");

	// Cria uma nova imagem de saida com os mesmos tamanhos da entrada
	Image *saida = imgCreate(imgGetWidth(entrada), imgGetHeight(entrada));

	// Percorre a imagem
	for(y = 0; y < imgGetHeight(entrada); y++){
		for(x = 0; x < imgGetWidth(entrada); x++){
				
			// Confere se o centro do Elemento Estruturante está na imagem
			if(  ( (y + SrtEl->rc) < 0 || (y + SrtEl->rc) > imgGetHeight(entrada) ) || 
				(  (x + SrtEl->cc) < 0 || (x + SrtEl->cc) > imgGetWidth(entrada))
				)
				continue;

			// Confere se a cor do Elemento Estruturante central e a mesma da imagem
			if( SrtEl->matOper[(SrtEl->rc * SrtEl->w) + SrtEl->cc].cor & imgGetPixelRed(entrada,x,y)){
				for( i = 0 ; i < (SrtEl->w * SrtEl->h) ; i++) {

					y1 = y + SrtEl->matOper[i].r;
					x1 = x + SrtEl->matOper[i].c;

					// Confere se o restante do Elemento Estruturante esta na imagem
					if ((y1 >= 0 && x1 >= 0) && 
						(y1 < imgGetHeight (entrada)) && 
						(x1 < imgGetWidth(entrada))
						) {

						// Pega o valor do pixel da imagem com o do elemento estruturante e aplica na imagem
						gv = imgGetPixelRed(entrada,x1,y1) + SrtEl->matOper[i].cor;
						
						imgSetPixel(saida, x1, y1, Clamp(gv),Clamp(gv),Clamp(gv));
					}
				}
			}
		}
	}
	return saida;		
}

Image * EroGrayScl(Image *entrada, strTypG *SrtEl){	
	int y,x,i,j,x1,y1;
	unsigned char gv, cor_img;

	printf("EROSAO\n");

	Image *saida = imgCreate(imgGetWidth(entrada), imgGetHeight(entrada));
	
	// Cria uma nova imagem de saida com os mesmos tamanhos da entrada
	for(y = 0; y < imgGetHeight(entrada); y++){
		for(x = 0; x < imgGetWidth(entrada); x++){

			// Inicializa o valor GV em branco sempre q o pixel andar
			gv = 255;
			// Confere se o centro do Elemento Estruturante está na imagem
			if(  ( (y + SrtEl->rc) < 0 || (y + SrtEl->rc) > imgGetHeight(entrada) ) || 
				(  (x + SrtEl->cc) < 0 || (x + SrtEl->cc) > imgGetWidth(entrada))
				)
				continue;
			cor_img = imgGetPixelRed(entrada,x,y);

			// Confere se a cor do Elemento Estruturante central e a mesma da imagem
			if( SrtEl->matOper[(SrtEl->rc * SrtEl->w) + SrtEl->cc].cor & cor_img){
				// Se o ponto central estiver na imagem, percorre todo o Elemento Estruturante
				for( i = 0 ; i < (SrtEl->w * SrtEl->h) ; i++) {
					
					y1 = y + SrtEl->matOper[i].r;
					x1 = x + SrtEl->matOper[i].c;

					// Confere se o restante do Elemento Estruturante esta na imagem
					if (
						(y1 >= 0 && x1 >= 0) && 
						(y1 < imgGetHeight(entrada)) && 
						(x1 < imgGetWidth(entrada))
						) {
						
						// Faz um AND binario do pixel da imagem sempre com valor anterior
						gv = gv & imgGetPixelRed(entrada,x1,y1);
					}
				}
				// Ao sair do laço que percorre o Elemento Estruturante
				// Seta na imagem o valor 0 caso o gv final seja difertente de 255 (erosiona), se for igual, coloca os valor da  imagem original
				if(gv == 255)
					imgSetPixel(saida, x, y, cor_img,cor_img,cor_img);
				else
					imgSetPixel(saida, x, y, 0,0,0);
			}

		}
	}
	return saida;
}	



Image *OpeningGrayScl(Image *entrada, strTypG *SrtEl){
	
	printf("[ABERTURA]\n");
	// Cria uma nova imagem de saida com os mesmos tamanhos da entrada
	Image *saida = imgCreate(imgGetWidth(entrada), imgGetHeight(entrada));
	// Erosiona a imagem de entrada
	saida = EroGrayScl(entrada, SrtEl);
	// Pega a imagem de saida do processo de erosao e a dilata
	saida = DilGrayScl(saida, SrtEl);

	return saida;
}

Image *ClosingGrayScl(Image *entrada, strTypG *SrtEl){
	
	printf("[FECHAMENTO]\n");
	// Cria uma nova imagem de saida com os mesmos tamanhos da entrada
	Image *saida = imgCreate(imgGetWidth(entrada), imgGetHeight(entrada));
	
	// Dilata a imagem de entrada
	saida = DilGrayScl(entrada, SrtEl);
	// Pega a imagem de saida do processo de dilatacao e a erosiona
	saida = EroGrayScl(saida, SrtEl);

	return saida;
}


/*

void SmoothingGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl)
{
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

void Morf_GradGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl)
{
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
  
void Top_hatGrayScl(int imSizehor,int imSizever, unsigned char *inIm, unsigned char *outIm, strTypG *strEl)
{
	int r,c;

	OpeningGrayScl(imSizehor, imSizever, inIm, outIm, strEl);

	for(r=0;r<imSizever;r++) 
		for(c=0;c<imSizehor;c++) 
			outIm[r*imSizehor + c] =Clamp(inIm[r*imSizehor + c] - outIm[r*imSizehor + c]);
}

*/


/* Modulo: Implementação do TAD: Imagem
 *
 * Curso: Computação Gráfica - 2000
 * Ultima alteração: 06mar2000
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "image.h"

struct Image_impl{
	int   h;                  /* número de linhas da Image */
	int   w;                  /* número de colunas da Image */
	int color;				  /* [0,1] 0 - gray 1 - color image */
	unsigned char *red;       /* matriz das componentes vermelha  */
	unsigned char *green;     /* matriz das componentes verde  */
	unsigned char *blue;      /* matriz das componentes azul  */
};

Image *imgCreate(int _w, int _h){
	Image *img;
	if ( _w<=0 || _h<=0)  return NULL;
	img=(Image*) malloc(sizeof(Image));
	if (img!=NULL ){
		img->w=_w;
		img->h=_h; 
		img->red   = (unsigned char *) malloc (_w * _h * sizeof(unsigned char) ); 
		img->green = (unsigned char *) malloc (_w * _h * sizeof(unsigned char) ); 
		img->blue  = (unsigned char *) malloc (_w * _h * sizeof(unsigned char) ); 

		if (img->red==NULL || img->green==NULL || img->blue==NULL ) {
			if (img->red  !=NULL) free(img->red);
			if (img->green!=NULL) free(img->green);
			if (img->blue !=NULL) free(img->blue);
			free (img);
			return NULL;
		}
	}
	img->color = 1;
	return img;
}

void imgDestroy(Image * img){
	if (img !=NULL) {
		if (img->red)    free (img->red);
		if (img->green)  free (img->green);
		if (img->blue)   free (img->blue);
		free(img);
	}
}


unsigned char imgGetPixelRed(Image *img, int x, int y) {
	return img->red[y*img->w+x];
}


unsigned char imgGetPixelGreen(Image *img, int x, int y) {
	return img->green[y*img->w+x];
}

unsigned char imgGetPixelBlue(Image *img, int x, int y) {
	return img->blue[y*img->w+x];
}

void imgSetPixel(Image *img, int x, int y, unsigned char r, unsigned char g, unsigned char b){
	img->red[y*img->w+x] = r;
	img->green[y*img->w+x] = g;
	img->blue[y*img->w+x] = b;
	return;
}

int     imgGetWidth(Image *img) {
	return img->w;
}

int     imgGetHeight(Image *img) {
	return img->h;
}


unsigned char *imgGetRedChannel(Image *img) {
	return img->red;
}

unsigned char *imgGetGreenChannel(Image *img) {
	return img->green;
}

unsigned char *imgGetBlueChannel(Image *img) {
	return img->blue;
}

/* funções clientes das acima */
Image * imgReadPPM(char *filename) {
	Image *img=NULL; /* imagem criada */
	FILE *fp;
	char line[80];
	unsigned char pixel[3];
	int x,y;
	int w,h,maxcolor;

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("\n[%s:%d] unable to load image file '%s'.\n", __FILE__, __LINE__, filename);
		free(img);
		return img;
	}
	fgets(line,80,fp);

	if(strcmp(line,"P6\n")) {
		return img;
	}


	while (fscanf( fp, " %d ", &w ) != 1)
		fgets(line, 80, fp);
	while (fscanf( fp, " %d ", &h ) != 1)
		fgets(line, 80, fp);
	while (fscanf( fp, " %d", &maxcolor ) != 1)
		fgets(line, 80, fp);

	fgetc(fp);

	img = imgCreate(w,h);

	/* le invertendo as linhas */
	for ( y=imgGetHeight(img)-1; y>=0; y-- ) {
		for ( x=0; x<imgGetWidth(img); x++ ) {
			fread( pixel, 3, 1, fp );
			imgSetPixel(img, x, y, pixel[0], pixel[1], pixel[2]);
		}
	}

	fclose(fp);
	return img;
}

int imgWritePPM(Image * img, char * filename)
{
	FILE * fp;
	int  x,y;
	int  maxcolor=255;
	unsigned char red, green, blue;

	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("\n[%s:%d] unable to write image file '%s'\n",
				__FILE__, __LINE__, filename);
		return 0;
	}

	/*cabeçalho de um arquivo .ppm */
	fprintf(fp,"P6\n%d %d\n%d\n", img->w, img->h, maxcolor);

	/* gravando invertendo o eixo y */
	for ( y=imgGetHeight(img)-1; y>=0; y-- )
		for ( x=0; x<imgGetWidth(img); x++ )
		{
			red   = imgGetPixelRed(img, x, y);
			green = imgGetPixelGreen(img, x, y);
			blue  = imgGetPixelBlue(img, x, y);
			fprintf(fp,"%c%c%c", red, green, blue);
		}

	printf(" %s was written successfully.\n",filename);

	fclose(fp);
	return 1;
}

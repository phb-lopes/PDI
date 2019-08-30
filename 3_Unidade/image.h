/* Modulo: Imterface do TAD: Image
 *
 * Curso: Computação Gráfica - 2000
 * Ultima alteração: 06mar2000
 */

#ifndef IMAGE_H
#define IMAGE_H

struct Image_impl;
typedef struct Image_impl Image;

Image * imgCreate(int w, int h);
void    imgDestroy(Image * img);

unsigned char imgGetPixelRed(Image *img, int x, int y);
unsigned char imgGetPixelGreen(Image *img, int x, int y);
unsigned char imgGetPixelBlue(Image *img, int x, int y);

void          imgSetPixel(Image *img, int x, int y, 
						  unsigned char r, unsigned char g, unsigned char b);
int     imgGetWidth(Image *img);
int     imgGetHeight(Image *img);
//void img_points(Image *img);

unsigned char *imgGetRedChannel(Image *img);
unsigned char *imgGetGreenChannel(Image *img);
unsigned char *imgGetBlueChannel(Image *img);

Image * normal_mapping(Image * origImg);

Image * imgReadPPM(char *filename);
int     imgWritePPM(Image * img, char * filename);

#endif

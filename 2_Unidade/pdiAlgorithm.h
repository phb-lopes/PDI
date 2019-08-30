/*
 * pdiAlgorithm.h
 *
 *  Created on: 10/09/2012
 *      Author: wilfredo
 */


#ifndef PDIALGORITHM_H_
#define PDIALGORITHM_H_

Image * img_ConvertGray(Image * origImg);
Image * img_Blur(Image * origImg, int sizeMask);
Image * img_points(Image * origImg, int opcao, int a, int b);

Image * lineartranformation(Image * origImg, double A, double B, double a1, double b1, double a2, double b2, double a3, double b3);

unsigned int * img_GetHistogram (Image * img);

void printHistogramToConsole(Image * img);

#endif /* PDIALGORITHM_H_ */

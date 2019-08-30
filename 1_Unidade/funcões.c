
Image * lineartranformation(Image * origImg, double A, double B, double a1, double b1, double a2, double b2, double a3, double b3){

	int x,y;
	double v1,v2,v3;
	double c1,c2,c3; 

	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
	
	//Image *rImg = img_ConvertGray(origImg);

	if (rImg == NULL)
        return NULL;
	

	for (y = 0; y < imgGetHeight(origImg); y++){
		for (x = 0; x < imgGetWidth(origImg); x++){
    		
    		v1 = imgGetPixelRed(origImg, x, y);
    		v2 = imgGetPixelGreen(origImg, x, y);
			v3 = imgGetPixelBlue(origImg, x, y);

			if(v1 < A)
				c1 = a1*v1 + b1;
			if(v1 >= A && v1 <= B)
				c1 = a2*v1 + b2;
			if(v1 > B)
				c1 = a3*v1 + b3;
			

			if(v2 < A)
				c2 = a1*v2 + b1;
			if(v2 >= A && v2 <= B)
				c2 = a2*v2 + b2;
			if(v2 > B)
				c2 = a3*v2 + b3;


			if(v3 < A)
				c3 = a1*v3 + b1;
			if(v3 >= A && v3 <= B)
				c3 = a2*v3 + b2;
			if(v3 > B)
				c3 = a3*v3 + b3;

			imgSetPixel(rImg, x, y, validColor (c1), validColor (c2), validColor (c3));    		
		}
	}

	return rImg;
}

Image * img_points(Image * origImg, int opcao, int a, int b){
	int x, y;
    int v1,v2,v3;
    int c1,c2,c3;
	

	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
    Image *rImg2 = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
    
    if (rImg == NULL)
        return NULL;
    if (rImg2 == NULL)
        return NULL;

	switch(opcao){
		case 1:{
			for (y = 0; y < imgGetHeight(origImg); y++){
        		for (x = 0; x < imgGetWidth(origImg); x++){
            		
        		v1 = imgGetPixelGreen(origImg, x, y);
        		v2 = imgGetPixelRed(origImg, x, y);
        		v3 = imgGetPixelBlue(origImg, x, y);

        		c1 = a*log(v1);
        		c2 = a*log(v2);
        		c3 = a*log(v3);
            	
            	imgSetPixel(rImg2, x, y, c1, c2, c3);
        		}
    		}
    		
			return rImg2;
			break;
		}
		case 2:{
			for (y = 0; y < imgGetHeight(origImg); y++){
        		for (x = 0; x < imgGetWidth(origImg); x++){
            		
        		v1 = imgGetPixelRed(origImg, x, y);
        		v2 = imgGetPixelGreen(origImg, x, y);
        		v3 = imgGetPixelBlue(origImg, x, y);

        		c1 = a*(pow(v1,b));
        		c2 = a*(pow(v2,b));
        		c3 = a*(pow(v3,b));
            	
            	imgSetPixel(rImg2, x, y, c1, c2, c3);
        		}
    		}
    		
			return rImg2;
			break;
		}
	}
}
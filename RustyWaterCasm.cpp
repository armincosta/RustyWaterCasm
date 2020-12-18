/** RustyWaterCasm.dll

   This library can be used freely to render water effects efficiently

   Author: Armin Costa
   e-mail: armincosta@hotmail.com
   
#   
# Copyright (C) 2005, 2008 Armin Costa
# This file is part of RustyWaterCasm
#
# RustyWaterCasm is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# RustyWaterCasm is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License version 3
*/




#include "stdafx.h"
#include "RustyWaterCasm.h"




char *buffer;  // image buffer
char *buf;
int *w_old;
int *w_new;
int *tmp_;

int width = 256;
int height = 256;
int water_size = 256*256;
char *me = { "################################################################################ \n RWaterCasm.dll -- copyright(c) 2003-2008 \n  Author: Armin Costa \n e-mail: armincosta@rustyliquid.com \n \n A library coded in C++ and Asm to render Water-Effects in Java(tm) \n ########################################################################\n" };
int lum = 2; // to calculate water-reflaction --> spectrum



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
RUSTYWATERCASM_API int nRustyWaterCasm=0;

// This is an example of an exported function.
RUSTYWATERCASM_API int fnRustyWaterCasm(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see RustyWaterCasm.h for the class definition
CRustyWaterCasm::CRustyWaterCasm()
{ 
	return; 
}

RUSTYWATERCASM_API void filterMap(int w, int h){

     int y;
     int x;
     
     int tmp2 = 0;
     int tmp = 0;
     for(y = 1; y < h-1; y++){
	       tmp2 += w;
       for(x = 1; x < w-1; x++){
 	          tmp = tmp2 + x;
			int newh= ((  w_old[tmp + w]
				+ w_old[tmp - w]
				+ w_old[tmp + 1]
				+ w_old[tmp - 1]
				+ w_old[tmp - w - 1]  // 4 pixel-map would be sufficiend
				+ w_old[tmp + w - 1]
				+ w_old[tmp - w + 1]
				+ w_old[tmp + w + 1]
				) >> 2 )
				- w_new[tmp];

              

				w_new[tmp] = newh - (newh >> 3);

       }

     }

     
     tmp_ = w_old;
     w_old = w_new;

     w_new = tmp_;
     
 }

RUSTYWATERCASM_API void genTexture(){
	     int w = width;
		 int h = height;
		 int bs = water_size;

         int tmp=0;
         int t_ver = 0;
    
          int tm = 0;
          int tmp3 = 0;

          int y;
          int x;
		  int lum = 2;
		for(y=0; y<(h-1); y++) {
			for(x=0; x<(w-1); x++) {
							
				// calculate the 'slope' for the current pixel
				int dx = w_old[tmp] - w_old[tmp+1]; //x
				int dy = w_old[tmp] - w_old[tmp+w];  //y
				
				int ox = (dx>>3)+x;
				int oy = (dy>>3)+y;

				int shading = (dx+dy)>>lum;  // calc reflection

				// keep offset inside the array
				ox = ox >= w ? (w-1) : (ox < 0 ? 0 : ox);
				oy = oy >= h ? (h-1) : (oy < 0 ? 0 : oy);

                 int color = (int)buffer[ox + oy * w];


			        int r = (color & 0xff0000) >> 16;
			        int g = (color & 0xff00)>> 8;
			        int b = (color & 0xff);
			        
			        r = controlCol(r + shading);
				g = controlCol(g + shading);
				b = controlCol(b + shading);

                  int tmpX;
                  int tmpY;
                  int tmp2; 


                    tmp2 = tmp;


                   if((tmp2 >= bs)||(tmp2 <= 0)){
                                                             // prevent array index out of bounds

                   }else{



					        int col = 0xff000000 | (r << 16) | (g << 8) | b;//paint pixel at offset tmp2
						//	img1->putPixel(x, y, col);




                   }
								
				// increment one pixel
				tmp++;
				t_ver++;
			}
			tmp++;
		        t_ver++;

		}
		//draw(*img1);

}

int controlCol(int c) {
   return (c > 255 ? 255 : (c < 0 ? 0 : c));
}

RUSTYWATERCASM_API void addDrop(int x, int y, int h){
	w_old[x*y] = h; 
}
	
RUSTYWATERCASM_API void addBlob(int x, int y, int rad, int depth) {
		int w = width;
		int h = height;
	    // check/adjust position of blob 
		x = x<1 ? 1 : (x >= w ? w-1 : x);
		y = y<1 ? 1 : (y >= h ? h-1 : y);
			
		// check/adjust radius
		rad = x+(rad<<1) >= w ? (w-x)>>1 : rad;
		rad = y+(rad<<1) >= h ? (h-y)>>1 : rad;
			
		// precalcs/-casts
		double drad = (double)rad;
		double cx   = x+drad;
		double cy   = y+drad;
			
		for(int i=x; i < x+(rad*2); i++) {
			for(int j=y; j < y+(rad*2); j++) {
				// offsets from center
				double dx = (double)abs(cx - ((double)i));
				double dy = (double)abs(cy - ((double)j));
				// vector distance from center
				double l = (double)sqrt(dx*dx + dy*dy);
				// get inverse distance
				double mul;//Math::abs(drad-l, 0.0);

				if((drad-l) < 0.0 ? true : false){
						mul = 0.0;	
				}else {
						mul = drad-l;
				}
				// normalize it by radius
				mul /= drad;
				// multiply the depth with it to get a smooth blob
				// and add this value to the hmap at the current position
				//		the modulos shouldn't be necessary, but.....
				int d_f = 1;
				w_old[(i%w)+(j%h)*w] += (int)(mul*((double)depth*d_f));
			}

		}

	}


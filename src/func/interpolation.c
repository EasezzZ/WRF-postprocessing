#include "interpolation.h"

void interpolate_3d_z (float *data3d, float ip_level, float *levels, float *data2d) {
  
  int interp;
  int kp;
  
  int wN2D = wNX*wNY;

  int ip=0;
  int im=1;
  
  // does vertical coordinate increase or decrease with increasing k?
  //set offset appropriately
  if (levels[0] > levels[wN2D])  { //(x+y*wNX+z*wNX*wNY)
    ip=1;
    im=0;
  }
  
  int i;
  for (i=0; i<wN2D; i++) {

    // initialise to MISSING
    data2d[i] = NC_FILL_FLOAT; 
    interp = 0;
    kp = wNZ;
    
    while ( !interp && (kp >= 2) ) {
      size_t ixm = i+wN2D*(kp-im);
      size_t ixp = i+wN2D*(kp-ip);
      if ( (levels[ixm] <= ip_level) && (levels[ixp] > ip_level) ) {
	double w = (ip_level-levels[ixm]) / (levels[ixp]-levels[ixm]);
	data2d[i] = (1.-w)*data3d[ixm] + w*data3d[ixp];
	interp = 1;
      }
      kp--;
    }
  } 
}
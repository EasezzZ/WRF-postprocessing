#include "calc_uvmet.h"

int uvmet_need_rotate () {
  if (wMAP_PROJ == 1 || wMAP_PROJ == 2) {
    fprintf(stdout, "Wind needs to be rotated\n");
    return 1;
  } else {
    fprintf(stdout, "Wind do not need to be rotated\n");
    return 0;
  }
}

void uvmet_calc (float *u, float *v, float *umet, float *vmet, int ndims) {

  // global wNY
  // global wNX
  // global wN2D
  // global wCEN_LON
  // global wLAT
  // global wLON
  // global NC_FILL_FLOAT
  // global wMAP_PROJ
  // global wTRUELAT1
  // global wTRUELAT2
  
  

  
  double * longca;
  double * longcb;

  double deg2rad = M_PI/180;
  double cone;
  
  if (wMAP_PROJ == 1 || wMAP_PROJ == 2) {
    if (wMAP_PROJ == 1) { // lambert conformal	
	if ( (fabs(wTRUELAT1 - wTRUELAT2) > 0.1)  && (fabs(wTRUELAT2 - 90.) > 0.1)) {
	  cone = ( pow(10, cos(wTRUELAT1*deg2rad)) - pow(10, cos(wTRUELAT2*deg2rad)) )
		/ ( pow(10, tan(45. -fabs(wTRUELAT1/2.)*deg2rad))
		    - pow(10, tan(45. -fabs(wTRUELAT2/2.)*deg2rad)) );
	} else {
	  cone = sin(fabs(wTRUELAT1)*deg2rad);
	}	
    } else if (wMAP_PROJ == 2) { // polar stereographic
      cone = 1.;
    }
  } else {
    fprintf(stderr, "calc_uvmet: ERROR : this projection do not need wind rotation\n");
    exit(-1);
  }
  
  
  longca = malloc(wN2D * sizeof(double));
  if (longca==NULL) {fprintf(stderr, "calc_uvmet.c : Cannot allocate LONGCA\n"); exit(-1);}
  longcb = malloc(wN2D * sizeof(double));
  if (longcb==NULL) {fprintf(stderr, "calc_uvmet.c : Cannot allocate LONGCB\n"); exit(-1);}


  // in compute_uvmet

  int i;
  for (i=0; i<wN2D; i++) {

      longca[i] = wLON[i] - wCEN_LON;
      
      if (longca[i] > 180.) {
	longca[i] -= 360.;
      }
      
      if (longca[i] < -180.) {
	longca[i] = longca[i] + 360.;
      }

      if (wLAT[i] < 0.) {
	longcb[i] = -longca[i]*cone*deg2rad;
      } else {
	longcb[i] = longca[i]*cone*deg2rad;
      }

      longca[i] = cos(longcb[i]);
      longcb[i] = sin(longcb[i]);
  }

  // computing velocities

  int x,y,z;
  
  if (ndims == 2) {
    
    for (y=0; y<wNY; y++) {
      for (x=0; x<wNX; x++) {
	size_t i = x+y*wNX;

	umet[i] = v[i]*longcb[i] + u[i]*longca[i];
	vmet[i] = v[i]*longca[i] - u[i]*longcb[i];
    
      }
    }
    
  } else {
    
    for (z=0; z<wNZ; z++) {
      for (y=0; y<wNY; y++) {
	for (x=0; x<wNX; x++) {
	  size_t i = x+y*wNX+z*wN2D;
	  size_t i2d = x+y*wNX;

	  umet[i] = v[i]*longcb[i2d] + u[i]*longca[i2d];
	  vmet[i] = v[i]*longca[i2d] - u[i]*longcb[i2d];
	  
	}
      }
    }
    
  }

  free (longca);
  free (longcb);

}
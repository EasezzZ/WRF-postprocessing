#include "calc_uvmet.h"

void calc_uvmet (float *u, float *v, float *umet, float *vmet, double cone, int is_stag, int is_missing_val) {

  // global wNY
  // global wNX
  // global wN2D
  // global wCEN_LON
  // global wLAT
  // global wLON
  // global NC_FILL_FLOAT
  
  
  //TODO: vérifier qu'on utilise bien wLAT et wLON pour du staggered
  // sinon, c'est wLAT_U et wLAT_V ? voir dans wrfW.c / wrf_user.f
  
  //ISTAG should be 0 if the U,V grids are not staggered.
  //That is, NY = NYP1 and NX = NXP1.
  
  
  double * longca;
  double * longcb;

  double deg2rad = M_PI/180;

  longca = malloc(wN2D * sizeof(double));
  if (longca==NULL) {fprintf(stderr, "calc_uvmet.c : Cannot allocate LONGCA\n"); exit(-1);}
  longcb = malloc(wN2D * sizeof(double));
  if (longcb==NULL) {fprintf(stderr, "calc_uvmet.c : Cannot allocate LONGCB\n"); exit(-1);}


  // in compute_uvmet

  int i;
  for (i=0; i<wN2D; i++) {

      longca[i] = wLON[i] - wCEN_LON;
      if (longca[i] > 180.) {
	longca[i] = longca[i] - 360.;
      } else if (longca[i] < 180.) {
	longca[i] = longca[i] + 360.;
      }

      if (wLAT[i] < 0.) {
	longcb[i] = -longca[i]*cone*deg2rad;
      } else {
	longcb[i] = -longca[i]*cone*deg2rad;
      }

      longca[i] = cos(longcb[i]);
      longcb[i] = sin(longcb[i]);
  }

  // computing velocities

  int x,y;
  for (y=0; y<wNY; y++) {
    for (x=0; x<wNX; x++) {
      size_t i = x+y*wNX;
      size_t next_x = x+1+y*wNX;
      size_t next_y = x+(y+1)*wNX;
      if (is_stag==1) {
	if (is_missing_val && (u[i]==NC_FILL_FLOAT || v[i]==NC_FILL_FLOAT ||
			      u[next_x]==NC_FILL_FLOAT || v[next_y]==NC_FILL_FLOAT))
	  {
	    umet[i] = NC_FILL_FLOAT;
	    vmet[i] = NC_FILL_FLOAT;
	  } else {
	    double uk = 0.5 * (u[i]+u[next_x]);
	    double vk = 0.5 * (v[i]+v[next_y]);
	    umet[i] = vk*longcb[i] + uk*longca[i];
	    vmet[i] = vk*longca[i] - uk*longcb[i];
	  }
      } else {
	if (is_missing_val && (u[i]==NC_FILL_FLOAT || v[i]==NC_FILL_FLOAT)) {
	  umet[i] = NC_FILL_FLOAT;
	  vmet[i] = NC_FILL_FLOAT;
	} else {
	  double uk = u[i];
	  double vk = u[i];
	  umet[i] = vk*longcb[i] + uk*longca[i];
	  vmet[i] = vk*longca[i] - uk*longcb[i];
	}
      }
    }
  }

  free (longca);
  free (longcb);

}
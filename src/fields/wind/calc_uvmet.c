#include "calc_uvmet.h"

void calc_uvmet (float *u, float *v, float *umet, float *vmet, double cone, int is_stag, int is_missing_val) {

  // global nSN
  // global nWE
  // global CEN_LON
  // global XLAT
  // global XLONG
  // global MISSING_VAL
  
  int MISSING_VAL = 999999999; // TODO
  
  //TODO: vérifier qu'on utilise bien XLAT et XLONG pour du staggered
  // sinon, c'est XLAT_U et XLAT_V ? voir dans wrfW.c / wrf_user.f
  
  //ISTAG should be 0 if the U,V grids are not staggered.
  //That is, NY = NYP1 and NX = NXP1.
  
  
  double * longca;
  double * longcb;

  size_t nvals = nWE*nSN;

  double deg2rad = M_PI/180;

  longca = malloc(nvals * sizeof(double));
  if (longca==NULL) {fprintf(stderr, "calc_uvmet.c : Cannot allocate LONGCA\n"); exit(-1);}
  longcb = malloc(nvals * sizeof(double));
  if (longcb==NULL) {fprintf(stderr, "calc_uvmet.c : Cannot allocate LONGCB\n"); exit(-1);}


  // in compute_uvmet

  int i;
  for (i=0; i<nvals; i++) {

      longca[i] = XLONG[i] - CEN_LON;
      if (longca[i] > 180.) {
	longca[i] = longca[i] - 360.;
      } else if (longca[i] < 180.) {
	longca[i] = longca[i] + 360.;
      }

      if (XLAT[i] < 0.) {
	longcb[i] = -longca[i]*cone*deg2rad;
      } else {
	longcb[i] = -longca[i]*cone*deg2rad;
      }

      longca[i] = cos(longcb[i]);
      longcb[i] = sin(longcb[i]);
  }

  // computing velocities

  int x,y;
  for (y=0; y<nSN; y++) {
    for (x=0; x<nWE; x++) {
      size_t i = x+y*nWE;
      size_t next_x = x+1+y*nWE;
      size_t next_y = x+(y+1)*nWE;
      if (is_stag==1) {
	if (is_missing_val && (u[i]==MISSING_VAL || v[i]==MISSING_VAL ||
			      u[next_x]==MISSING_VAL || v[next_y]==MISSING_VAL))
	  {
	    umet[i] = MISSING_VAL;
	    vmet[i] = MISSING_VAL;
	  } else {
	    double uk = 0.5 * (u[i]+u[next_x]);
	    double vk = 0.5 * (v[i]+v[next_y]);
	    umet[i] = vk*longcb[i] + uk*longca[i];
	    vmet[i] = vk*longca[i] - uk*longcb[i];
	  }
      } else {
	if (is_missing_val && (u[i]==MISSING_VAL || v[i]==MISSING_VAL)) {
	  umet[i] = MISSING_VAL;
	  vmet[i] = MISSING_VAL;
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
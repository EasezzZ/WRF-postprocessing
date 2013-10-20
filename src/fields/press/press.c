#include "press.h"

void load_PRESS () {

  fprintf(stdout, "Loading PRESS\n");
  
  // base state pressure
  int b_press_id;
  nc_error(nc_inq_varid (wrfout_id, "PB", &b_press_id));
  // perturbation pressure
  int p_press_id;
  nc_error(nc_inq_varid (wrfout_id, "P", &p_press_id));
  
  wPB = malloc (wN3D * sizeof(float));
  if (wPB==NULL) {fprintf(stderr, "press.c : Cannot allocate wPB\n"); exit(-1);}

  wPP = malloc (wN3D * sizeof(float));
  if (wPP==NULL) {fprintf(stderr, "press.c : Cannot allocate wPP\n"); exit(-1);}
  
  wPRESS = malloc (wN3D * sizeof(float));
  if (wPRESS==NULL) {fprintf(stderr, "press.c : Cannot allocate wPRESS\n"); exit(-1);}  
  
  /*wPRESS_M = malloc (wN2D * ip_nALEVELS * sizeof(float));
  if (wPRESS==NULL) {fprintf(stderr, "press.c : Cannot allocate wPRESS_M\n"); exit(-1);}*/
  
  nc_error(nc_get_var_float(wrfout_id, b_press_id, wPB));
  nc_error(nc_get_var_float(wrfout_id, p_press_id, wPP));
  
  // Full model pressure [=base pressure (PB) + pertubation pressure (P)]
  int i;
  #pragma omp parallel for private(i)
  for (i=0; i<wN3D; i++) {
    wPRESS[i] = (wPB[i] + wPP[i]) * 0.01;
  }
  
  /*for (i=0; i<ip_nALEVELS; i++) {
    interpolate_3d_z (wPRESS, ip_ALEVELS[i], wHEIGHT, &wPRESS_M[wN2D*i]);
  }*/
  

}


void write_PRESS () {
  fprintf(stdout, "Writing PRESS\n");

  nc_error(nc_put_var_float(ncout_ID, idPRESS, wPRESS));
  //nc_error(nc_put_var_float(ncout_ID, idPRESS_M, wPRESS_M));
}

void set_meta_PRESS () {
  
  ncout_def_var_float("press", 3, ncout_3D_DIMS, &idPRESS);
  //ncout_def_var_float("press_m", 3, ncout_3DA_DIMS, &idPRESS_M);

  ncout_set_meta (idPRESS, "long_name", "air_pressure");
  ncout_set_meta (idPRESS, "standard_name", "air_pressure");
  ncout_set_meta (idPRESS, "description", "");
  ncout_set_meta (idPRESS, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/press/press.c");
  ncout_set_meta (idPRESS, "units", "hPa");
  ncout_set_meta (idPRESS, "coordinates", "model_level lon lat");
  
}


void free_PRESS () {
 
  free (wPB);
  free (wPP);
  free (wPRESS);
  //free (wPRESS_M);
  
}
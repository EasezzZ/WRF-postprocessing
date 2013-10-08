#include "press.h"

void load_PRESS () {

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
  
  nc_error(nc_get_var_float(wrfout_id, b_press_id, wPB));
  nc_error(nc_get_var_float(wrfout_id, p_press_id, wPP));
  
  // Full model pressure [=base pressure (PB) + pertubation pressure (P)]
  int i;
  for (i=0; i<wN3D; i++) {
    wPRESS[i] = (wPB[i] + wPP[i]) * 0.01;
  }

}


void write_PRESS () {
  nc_error(nc_put_var_float(ncout_ID, idPRESS, wPRESS));
}

void set_meta_PRESS () {
  
  int dim_ids[3];
  
  dim_ids[0] = ncout_DIM_Z;
  dim_ids[1] = ncout_DIM_Y;
  dim_ids[2] = ncout_DIM_X;
  
  ncout_def_var_float("press", 3, dim_ids, &idPRESS);

  ncout_set_meta (idPRESS, "long_name", "air_pressure");
  ncout_set_meta (idPRESS, "standard_name", "air_pressure");
  ncout_set_meta (idPRESS, "description", "");
  ncout_set_meta (idPRESS, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/press/press.c");
  ncout_set_meta (idPRESS, "units", "hPa");
  ncout_set_meta (idPRESS, "coordinates", "level lon lat");
  
}


void free_PRESS () {
 
  free (wPB);
  free (wPP);
  free (wPRESS);
  
}
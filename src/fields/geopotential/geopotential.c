#include "geopotential.h"

void load_GEOPOTENTIAL () {

  // base state geopotential
  int b_geopotential_id;
  nc_error(nc_inq_varid (wrfout_id, "PHB", &b_geopotential_id));
  // perturbation geopotential
  int p_geopotential_id;
  nc_error(nc_inq_varid (wrfout_id, "PH", &p_geopotential_id));
  
  int n_stag_vals = wNX*wNY*wNZS;
  
  wsPHB = malloc (n_stag_vals * sizeof(float));
  if (wsPHB==NULL) {fprintf(stderr, "geopotential.c : Cannot allocate wsPHB\n"); exit(-1);}

  wsPH = malloc (n_stag_vals * sizeof(float));
  if (wsPH==NULL) {fprintf(stderr, "geopotential.c : Cannot allocate wsPH\n"); exit(-1);}
  
  wGEOPOTENTIAL = malloc (wN3D * sizeof(float));
  if (wGEOPOTENTIAL==NULL) {fprintf(stderr, "geopotential.c : Cannot allocate wGEOPOTENTIAL\n"); exit(-1);}  
  
  nc_error(nc_get_var_float(wrfout_id, b_geopotential_id, wsPHB));
  nc_error(nc_get_var_float(wrfout_id, p_geopotential_id, wsPH));
  
  int i;
  for (i=0; i<wN3D; i++) {
    // unstagger, then geopotential = PH + PHB
    wGEOPOTENTIAL[i] = 0.5 * (wsPHB[i]+wsPHB[i+wN2D]+wsPH[i]+wsPH[i+wN2D]);
  }

}


void write_GEOPOTENTIAL () {
  nc_error(nc_put_var_float(ncout_ID, idGEOPOTENTIAL, wGEOPOTENTIAL));
}

void set_meta_GEOPOTENTIAL () {
  
  int dim_ids[3];
  
  dim_ids[0] = ncout_DIM_Z;
  dim_ids[1] = ncout_DIM_Y;
  dim_ids[2] = ncout_DIM_X;
  
  ncout_def_var_float("geopotential", 3, dim_ids, &idGEOPOTENTIAL);

  ncout_set_meta (idGEOPOTENTIAL, "long_name", "geopotential");
  ncout_set_meta (idGEOPOTENTIAL, "standard_name", "geopotential");
  ncout_set_meta (idGEOPOTENTIAL, "description", "Geopotential is the sum of the specific gravitational potential energy relative to the geoid and the specific centripetal potential energy.");
  ncout_set_meta (idGEOPOTENTIAL, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/geopotential/geopotential.c");
  ncout_set_meta (idGEOPOTENTIAL, "units", "m2 s-2");
  ncout_set_meta (idGEOPOTENTIAL, "coordinates", "level lon lat");
  
}


void free_GEOPOTENTIAL () {
 
  free (wsPH);
  free (wsPHB);
  free (wGEOPOTENTIAL);
  
}
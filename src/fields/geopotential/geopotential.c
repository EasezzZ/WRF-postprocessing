#include "geopotential.h"

void load_GEOPOTENTIAL () {

  fprintf(stdout, "Loading GEOPOTENTIAL\n");
  
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
  
  wHEIGHT = malloc (wN3D * sizeof(float));
  if (wHEIGHT==NULL) {fprintf(stderr, "geopotential.c : Cannot allocate wHEIGHT\n"); exit(-1);} 
  
  wHEIGHT_STAG = malloc (n_stag_vals * sizeof(float));
  if (wHEIGHT_STAG==NULL) {fprintf(stderr, "geopotential.c : Cannot allocate wHEIGHT_STAG\n"); exit(-1);}
  
  wGEOPOTENTIAL_P = malloc (wN2D * ip_nPLEVELS * sizeof(float));
  if (wGEOPOTENTIAL_P==NULL) {fprintf(stderr, "geopotential.c : Cannot allocate wGEOPOTENTIAL_P\n"); exit(-1);}  
  
  nc_error(nc_get_var_float(wrfout_id, b_geopotential_id, wsPHB));
  nc_error(nc_get_var_float(wrfout_id, p_geopotential_id, wsPH));
  
  int i;
  #pragma omp parallel for private(i)
  for (i=0; i<wN3D; i++) {
    // unstagger, then geopotential = PH + PHB
    wGEOPOTENTIAL[i] = 0.5 * (wsPHB[i]+wsPHB[i+wN2D]+wsPH[i]+wsPH[i+wN2D]);
    // geopotential height = geopotential / 9.81
    wHEIGHT[i] = wGEOPOTENTIAL[i] / 9.81;
  }
  
  for (i=0; i<n_stag_vals; i++) {
    wHEIGHT_STAG[i] = (wsPHB[i]+wsPH[i])/9.81;
  }
  
  #pragma omp parallel for private(i)
  for (i=0; i<ip_nPLEVELS; i++) {
   interpolate_3d_z (wGEOPOTENTIAL, ip_PLEVELS[i], wPRESS, &wGEOPOTENTIAL_P[wN2D*i]);
  }

}


void write_GEOPOTENTIAL () {
  fprintf(stdout, "Writing GEOPOTENTIAL\n");
  nc_error(nc_put_var_float(ncout_ID, idGEOPOTENTIAL, wGEOPOTENTIAL));
  nc_error(nc_put_var_float(ncout_ID, idGEOPOTENTIAL_P, wGEOPOTENTIAL_P));
  nc_error(nc_put_var_float(ncout_ID, idHEIGHT, wHEIGHT));
}

void set_meta_GEOPOTENTIAL () {
  
  ncout_def_var_float("geopotential", 3, ncout_3D_DIMS, &idGEOPOTENTIAL);

  ncout_set_meta (idGEOPOTENTIAL, "long_name", "geopotential");
  ncout_set_meta (idGEOPOTENTIAL, "standard_name", "geopotential");
  ncout_set_meta (idGEOPOTENTIAL, "description", "Geopotential is the sum of the specific gravitational potential energy relative to the geoid and the specific centripetal potential energy.");
  ncout_set_meta (idGEOPOTENTIAL, "reference", "http://doc.omd.li/wrfpp/geopotential");
  ncout_set_meta (idGEOPOTENTIAL, "units", "m2 s-2");
  ncout_set_meta (idGEOPOTENTIAL, "coordinates", "model_level lon lat");
  
  
  ncout_def_var_float("height", 3, ncout_3D_DIMS, &idHEIGHT);

  ncout_set_meta (idHEIGHT, "long_name", "geopotential_height");
  ncout_set_meta (idHEIGHT, "standard_name", "geopotential_height");
  ncout_set_meta (idHEIGHT, "description", "Geopotential is the sum of the specific gravitational potential energy relative to the geoid and the specific centripetal potential energy. Geopotential height is the geopotential divided by the standard acceleration due to gravity. It is numerically similar to the altitude (or geometric height) and not to the quantity with standard name height, which is relative to the surface.");
  ncout_set_meta (idHEIGHT, "reference", "http://doc.omd.li/wrfpp/height");
  ncout_set_meta (idHEIGHT, "units", "m");
  ncout_set_meta (idHEIGHT, "coordinates", "model_level lon lat");
  
  
  ncout_def_var_float("geopotential_p", 3, ncout_3DP_DIMS, &idGEOPOTENTIAL_P);

  ncout_set_meta (idGEOPOTENTIAL_P, "long_name", "geopotential_on_pressure_levels");
  ncout_set_meta (idGEOPOTENTIAL_P, "standard_name", "geopotential");
  ncout_set_meta (idGEOPOTENTIAL_P, "description", "Geopotential is the sum of the specific gravitational potential energy relative to the geoid and the specific centripetal potential energy.");
  ncout_set_meta (idGEOPOTENTIAL_P, "reference", "http://doc.omd.li/wrfpp/geopotential_p");
  ncout_set_meta (idGEOPOTENTIAL_P, "units", "m2 s-2");
  ncout_set_meta (idGEOPOTENTIAL_P, "coordinates", "press_level lon lat");
  
}


void free_GEOPOTENTIAL () {
 
  free (wsPH);
  free (wsPHB);
  free (wGEOPOTENTIAL);
  free (wHEIGHT);
  free (wHEIGHT_STAG);
  free (wGEOPOTENTIAL_P);
  
}
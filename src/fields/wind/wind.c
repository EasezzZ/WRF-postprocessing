#include "wind.h"

void load_WIND () {
  fprintf(stdout, "Loading WIND\n");

  int u_id;
  int v_id;

  nc_error(nc_inq_varid (wrfout_id, "U", &u_id));
  nc_error(nc_inq_varid (wrfout_id, "V", &v_id));
  
  
  wU_raw = malloc (wNXS * wNY * wNZ * sizeof(float));
  if (wU_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wU_raw\n"); exit(-1);}
  
  wV_raw = malloc (wNX * wNYS * wNZ * sizeof(float));
  if (wV_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wV_raw\n"); exit(-1);}
  
  
  wU_unstag_raw = malloc (wN3D * sizeof(float));
  if (wU_unstag_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wU_unstag_raw\n"); exit(-1);}
  
  wV_unstag_raw = malloc (wN3D * sizeof(float));
  if (wV_unstag_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wV_unstag_raw\n"); exit(-1);}
  
  
  wWIND_U = malloc (wN3D * sizeof(float));
  if (wWIND_U==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_U\n"); exit(-1);}
  
  wWIND_V = malloc (wN3D * sizeof(float));
  if (wWIND_V==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_V\n"); exit(-1);}
  
  
  nc_error(nc_get_var_float(wrfout_id, u_id, wU_raw));
  nc_error(nc_get_var_float(wrfout_id, v_id, wV_raw));
  
  // unstagger
  int x, y, z;
  int i, iu, iv;
  for (z=0; z<wNZ; z++) {
    for (y=0; y<wNY; y++) {
      for (x=0; x<wNX; x++) {
	i = x + y*wNX + z*wNX*wNY;
	iu = x + y*wNXS + z*wNXS*wNY;
	iv = x + y*wNX + z*wNX*wNYS;
	wU_unstag_raw[i] = 0.5 * (wU_raw[iu] + wU_raw[iu+1]);
	wV_unstag_raw[i] = 0.5 * (wV_raw[iv] + wV_raw[iv+wNX]);
      }
    }
  }
  
  free (wU_raw);
  free (wV_raw);
  
  
  if (uvmet_need_rotate()) {
    uvmet_calc (wU_unstag_raw, wV_unstag_raw, wWIND_U, wWIND_V, 3);
    //TODO: check results
  } else {
    wWIND_U = wU_unstag_raw;
    wWIND_V = wV_unstag_raw;
    //TODO: make sure we are passing arrays values
  }
  
  free (wU_unstag_raw);
  free (wV_unstag_raw); 
  
  
  
  // interpolation to meters and pressure levels
  
   
  wWIND_U_P = malloc (wN2D * ip_nPLEVELS * sizeof(float));
  if (wWIND_U_P==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_U_P\n"); exit(-1);}
  wWIND_V_P = malloc (wN2D * ip_nPLEVELS * sizeof(float));
  if (wWIND_V_P==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_V_P\n"); exit(-1);}
  
  wWIND_U_M = malloc (wN2D * ip_nMLEVELS * sizeof(float));
  if (wWIND_U_M==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_U_M\n"); exit(-1);}
  wWIND_V_M = malloc (wN2D * ip_nMLEVELS * sizeof(float));
  if (wWIND_V_M==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_V_M\n"); exit(-1);}
  
  
  for (i=0; i<ip_nPLEVELS; i++) {
   interpolate_3d_z (wWIND_U, ip_PLEVELS[i], wPRESS, &wWIND_U_P[wN2D*i]);
   interpolate_3d_z (wWIND_V, ip_PLEVELS[i], wPRESS, &wWIND_V_P[wN2D*i]);
  }
  for (i=0; i<ip_nMLEVELS; i++) {
   interpolate_3d_z (wWIND_U, ip_MLEVELS[i], wHEIGHT, &wWIND_U_M[wN2D*i]);
   interpolate_3d_z (wWIND_V, ip_MLEVELS[i], wHEIGHT, &wWIND_V_M[wN2D*i]);
  }
  
}


void write_WIND () {
  
  fprintf(stdout, "Writing WIND\n");

  nc_error(nc_put_var_float(ncout_ID, idWIND_U, wWIND_U));
  nc_error(nc_put_var_float(ncout_ID, idWIND_V, wWIND_V));
  
  nc_error(nc_put_var_float(ncout_ID, idWIND_U_P, wWIND_U_P));
  nc_error(nc_put_var_float(ncout_ID, idWIND_V_P, wWIND_V_P));
  nc_error(nc_put_var_float(ncout_ID, idWIND_U_M, wWIND_U_M));
  nc_error(nc_put_var_float(ncout_ID, idWIND_V_M, wWIND_V_M));
}

void set_meta_WIND () {
  
  ncout_def_var_float("wind_u", 3, ncout_3D_DIMS, &idWIND_U);
  ncout_def_var_float("wind_v", 3, ncout_3D_DIMS, &idWIND_V);
  
  ncout_def_var_float("wind_u_p", 3, ncout_3DP_DIMS, &idWIND_U_P);
  ncout_def_var_float("wind_v_p", 3, ncout_3DP_DIMS, &idWIND_V_P);
  ncout_def_var_float("wind_u_m", 3, ncout_3DM_DIMS, &idWIND_U_M);
  ncout_def_var_float("wind_v_m", 3, ncout_3DM_DIMS, &idWIND_V_M);

  
  /*ncout_set_meta (idRH, "long_name", "relative_humidity");
  ncout_set_meta (idRH, "standard_name", "relative_humidity");
  ncout_set_meta (idRH, "description", "");
  ncout_set_meta (idRH, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/humidity/rh.c");
  ncout_set_meta (idRH, "units", "percent");
  ncout_set_meta (idRH, "coordinates", "lon lat");*/
  
  
}


void free_WIND () {
  free (wWIND_U);
  free (wWIND_V);
  free(wWIND_U_P);
  free(wWIND_V_P);
  free(wWIND_U_M);
  free(wWIND_V_M);
}
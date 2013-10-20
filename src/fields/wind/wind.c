#include "wind.h"

void load_WIND () {
  fprintf(stdout, "Loading WIND\n");

  int u_id;
  int v_id;
  int w_id;

  nc_error(nc_inq_varid (wrfout_id, "U", &u_id));
  nc_error(nc_inq_varid (wrfout_id, "V", &v_id));
  nc_error(nc_inq_varid (wrfout_id, "W", &w_id));
  
  
  wU_raw = malloc (wNXS * wNY * wNZ * sizeof(float));
  if (wU_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wU_raw\n"); exit(-1);}
  
  wV_raw = malloc (wNX * wNYS * wNZ * sizeof(float));
  if (wV_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wV_raw\n"); exit(-1);}
  
  wW_raw = malloc (wNX * wNY * wNZS * sizeof(float));
  if (wW_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wW_raw\n"); exit(-1);}
  
  
  wU_unstag_raw = malloc (wN3D * sizeof(float));
  if (wU_unstag_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wU_unstag_raw\n"); exit(-1);}
  
  wV_unstag_raw = malloc (wN3D * sizeof(float));
  if (wV_unstag_raw==NULL) {fprintf(stderr, "wind.c : Cannot allocate wV_unstag_raw\n"); exit(-1);}
 
  
  wWIND_U = malloc (wN3D * sizeof(float));
  if (wWIND_U==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_U\n"); exit(-1);}
  
  wWIND_V = malloc (wN3D * sizeof(float));
  if (wWIND_V==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_V\n"); exit(-1);}
  
  wWIND_W = malloc (wN3D * sizeof(float));
  if (wWIND_W==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_W\n"); exit(-1);}
  
  
  nc_error(nc_get_var_float(wrfout_id, u_id, wU_raw));
  nc_error(nc_get_var_float(wrfout_id, v_id, wV_raw));
  nc_error(nc_get_var_float(wrfout_id, w_id, wW_raw));
  
  // unstagger
  int x, y, z;
  int i, iu, iv;
  #pragma omp parallel for private(z)
  for (z=0; z<wNZ; z++) {
    for (y=0; y<wNY; y++) {
      for (x=0; x<wNX; x++) {
	i = x + y*wNX + z*wNX*wNY;
	iu = x + y*wNXS + z*wNXS*wNY;
	iv = x + y*wNX + z*wNX*wNYS;
	wU_unstag_raw[i] = 0.5 * (wU_raw[iu] + wU_raw[iu+1]);
	wV_unstag_raw[i] = 0.5 * (wV_raw[iv] + wV_raw[iv+wNX]);
	wWIND_W[i] = 0.5 * (wW_raw[i] + wW_raw[i+wN2D]);
      }
    }
  }
  
  free (wU_raw);
  free (wV_raw);
  free (wW_raw);
  
  
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
  wWIND_W_P = malloc (wN2D * ip_nPLEVELS * sizeof(float));
  if (wWIND_W_P==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_W_P\n"); exit(-1);}
  
  wWIND_U_A = malloc (wN2D * ip_nALEVELS * sizeof(float));
  if (wWIND_U_A==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_U_A\n"); exit(-1);}
  wWIND_V_A = malloc (wN2D * ip_nALEVELS * sizeof(float));
  if (wWIND_V_A==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_V_A\n"); exit(-1);}
  wWIND_W_A = malloc (wN2D * ip_nALEVELS * sizeof(float));
  if (wWIND_W_A==NULL) {fprintf(stderr, "wind.c : Cannot allocate wWIND_W_A\n"); exit(-1);}
  
  
  #pragma omp parallel for private(i)
  for (i=0; i<ip_nPLEVELS; i++) {
   interpolate_3d_z (wWIND_U, ip_PLEVELS[i], wPRESS, &wWIND_U_P[wN2D*i]);
   interpolate_3d_z (wWIND_V, ip_PLEVELS[i], wPRESS, &wWIND_V_P[wN2D*i]);
   interpolate_3d_z (wWIND_W, ip_PLEVELS[i], wPRESS, &wWIND_W_P[wN2D*i]);
  }
  #pragma omp parallel for private(i)
  for (i=0; i<ip_nALEVELS; i++) {
   interpolate_3d_z (wWIND_U, ip_ALEVELS[i], wHEIGHT, &wWIND_U_A[wN2D*i]);
   interpolate_3d_z (wWIND_V, ip_ALEVELS[i], wHEIGHT, &wWIND_V_A[wN2D*i]);
   interpolate_3d_z (wWIND_W, ip_ALEVELS[i], wHEIGHT, &wWIND_W_A[wN2D*i]);
  }
  
}


void write_WIND () {
  
  fprintf(stdout, "Writing WIND\n");

  nc_error(nc_put_var_float(ncout_ID, idWIND_U, wWIND_U));
  nc_error(nc_put_var_float(ncout_ID, idWIND_V, wWIND_V));
  nc_error(nc_put_var_float(ncout_ID, idWIND_W, wWIND_W));
  
  nc_error(nc_put_var_float(ncout_ID, idWIND_U_P, wWIND_U_P));
  nc_error(nc_put_var_float(ncout_ID, idWIND_V_P, wWIND_V_P));
  nc_error(nc_put_var_float(ncout_ID, idWIND_W_P, wWIND_W_P));
  
  nc_error(nc_put_var_float(ncout_ID, idWIND_U_A, wWIND_U_A));
  nc_error(nc_put_var_float(ncout_ID, idWIND_V_A, wWIND_V_A));
  nc_error(nc_put_var_float(ncout_ID, idWIND_W_A, wWIND_W_A));
}

void set_meta_WIND () {
  
  ncout_def_var_float("wind_u", 3, ncout_3D_DIMS, &idWIND_U);
  ncout_def_var_float("wind_v", 3, ncout_3D_DIMS, &idWIND_V);
  ncout_def_var_float("wind_w", 3, ncout_3D_DIMS, &idWIND_W);
  
  ncout_def_var_float("wind_u_p", 3, ncout_3DP_DIMS, &idWIND_U_P);
  ncout_def_var_float("wind_v_p", 3, ncout_3DP_DIMS, &idWIND_V_P);
  ncout_def_var_float("wind_w_p", 3, ncout_3DP_DIMS, &idWIND_W_P);
  
  ncout_def_var_float("wind_u_a", 3, ncout_3DA_DIMS, &idWIND_U_A);
  ncout_def_var_float("wind_v_a", 3, ncout_3DA_DIMS, &idWIND_V_A);
  ncout_def_var_float("wind_w_a", 3, ncout_3DA_DIMS, &idWIND_W_A);

  
  ncout_set_meta (idWIND_U, "long_name", "wind_u_vector");
  ncout_set_meta (idWIND_U, "standard_name", "");
  ncout_set_meta (idWIND_U, "description", "Wind vector on X axis.");
  ncout_set_meta (idWIND_U, "reference", "http://doc.omd.li/wrfpp/wind_u");
  ncout_set_meta (idWIND_U, "units", "m s-1");
  ncout_set_meta (idWIND_U, "coordinates", "model_level lon lat");
  
  ncout_set_meta (idWIND_V, "long_name", "wind_v_vector");
  ncout_set_meta (idWIND_V, "standard_name", "");
  ncout_set_meta (idWIND_V, "description", "Wind vector on Y axis.");
  ncout_set_meta (idWIND_V, "reference", "http://doc.omd.li/wrfpp/wind_v");
  ncout_set_meta (idWIND_V, "units", "m s-1");
  ncout_set_meta (idWIND_V, "coordinates", "model_level lon lat");
  
  ncout_set_meta (idWIND_W, "long_name", "wind_w_vector");
  ncout_set_meta (idWIND_W, "standard_name", "");
  ncout_set_meta (idWIND_W, "description", "Wind vector on Z axis.");
  ncout_set_meta (idWIND_W, "reference", "http://doc.omd.li/wrfpp/wind_w");
  ncout_set_meta (idWIND_W, "units", "m s-1");
  ncout_set_meta (idWIND_W, "coordinates", "model_level lon lat");
  
  
  
  ncout_set_meta (idWIND_U_P, "long_name", "wind_u_vector_on_pressure_level");
  ncout_set_meta (idWIND_U_P, "standard_name", "");
  ncout_set_meta (idWIND_U_P, "description", "Wind vector on X axis. Interpolated to pressure levels.");
  ncout_set_meta (idWIND_U_P, "reference", "http://doc.omd.li/wrfpp/wind_u_p");
  ncout_set_meta (idWIND_U_P, "units", "m s-1");
  ncout_set_meta (idWIND_U_P, "coordinates", "press_level lon lat");
  
  ncout_set_meta (idWIND_V_P, "long_name", "wind_v_vector_on_pressure_level");
  ncout_set_meta (idWIND_V_P, "standard_name", "");
  ncout_set_meta (idWIND_V_P, "description", "Wind vector on Y axis. Interpolated to pressure levels");
  ncout_set_meta (idWIND_V_P, "reference", "http://doc.omd.li/wrfpp/wind_v_p");
  ncout_set_meta (idWIND_V_P, "units", "m s-1");
  ncout_set_meta (idWIND_V_P, "coordinates", "press_level lon lat");
  
  ncout_set_meta (idWIND_W_P, "long_name", "wind_w_vector_on_pressure_level");
  ncout_set_meta (idWIND_W_P, "standard_name", "");
  ncout_set_meta (idWIND_W_P, "description", "Wind vector on Z axis. Interpolated to pressure levels");
  ncout_set_meta (idWIND_W_P, "reference", "http://doc.omd.li/wrfpp/wind_w_p");
  ncout_set_meta (idWIND_W_P, "units", "m s-1");
  ncout_set_meta (idWIND_W_P, "coordinates", "press_level lon lat");
  
  
  ncout_set_meta (idWIND_U_A, "long_name", "wind_u_vector_on_altitude_level");
  ncout_set_meta (idWIND_U_A, "standard_name", "");
  ncout_set_meta (idWIND_U_A, "description", "Wind vector on X axis. Interpolated to altitude levels.");
  ncout_set_meta (idWIND_U_A, "reference", "http://doc.omd.li/wrfpp/wind_u_a");
  ncout_set_meta (idWIND_U_A, "units", "m s-1");
  ncout_set_meta (idWIND_U_A, "coordinates", "alti_level lon lat");
  
  ncout_set_meta (idWIND_V_A, "long_name", "wind_v_vector_on_altitude_level");
  ncout_set_meta (idWIND_V_A, "standard_name", "");
  ncout_set_meta (idWIND_V_A, "description", "Wind vector on Y axis. Interpolated to altitude levels");
  ncout_set_meta (idWIND_V_A, "reference", "http://doc.omd.li/wrfpp/wind_v_a");
  ncout_set_meta (idWIND_V_A, "units", "m s-1");
  ncout_set_meta (idWIND_V_A, "coordinates", "alti_level lon lat");
  
  ncout_set_meta (idWIND_W_A, "long_name", "wind_w_vector_on_altitude_level");
  ncout_set_meta (idWIND_W_A, "standard_name", "");
  ncout_set_meta (idWIND_W_A, "description", "Wind vector on Z axis. Interpolated to altitude levels");
  ncout_set_meta (idWIND_W_A, "reference", "http://doc.omd.li/wrfpp/wind_w_a");
  ncout_set_meta (idWIND_W_A, "units", "m s-1");
  ncout_set_meta (idWIND_W_A, "coordinates", "alti_level lon lat");
  
  
}


void free_WIND () {
  free (wWIND_U);
  free (wWIND_V);
  free (wWIND_W);
  
  free(wWIND_U_P);
  free(wWIND_V_P);
  free(wWIND_W_P);
  
  free(wWIND_U_A);
  free(wWIND_V_A);
  free(wWIND_W_A);
}
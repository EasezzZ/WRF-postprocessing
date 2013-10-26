#include "temp.h"

void load_TEMP () {
  
 
  fprintf(stdout, "Loading TEMP\n");
  
  int theta_id;
  
  //perturbation potential temperature (theta-t0)
  nc_error(nc_inq_varid (wrfout_id, "T", &theta_id));
  
  wTHETA = malloc (wN3D * sizeof(float));
  if (wTHETA==NULL) {fprintf(stderr, "temp.c : Cannot allocate wTHETA\n"); exit(-1);}
  
  wTEMP = malloc (wN3D * sizeof(float));
  if (wTEMP==NULL) {fprintf(stderr, "temp.c : Cannot allocate wTEMP\n"); exit(-1);}
  
  wTK = malloc (wN3D * sizeof(float));
  if (wTK==NULL) {fprintf(stderr, "temp.c : Cannot allocate wTK\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, theta_id, wTHETA));
  
  double p1000mb = 100000.;
  double r_d = 287.;
  double cp = 7.*r_d/2.;
  double pi;
  
  int i;
  #pragma omp parallel for private(i)
  for (i=0; i<wN3D; i++) {
    wTHETA[i] += 300;
    pi = pow( (wPRESS[i]*100/p1000mb), (r_d/cp) );
    wTK[i] = pi*wTHETA[i];
    wTEMP[i] = wTK[i] - 273.16;
  }
  
  wTEMP_A = malloc (wN2D * ip_nALEVELS * sizeof(float));
  if (wTEMP_A==NULL) {fprintf(stderr, "rh.c : Cannot allocate wTEMP_A\n"); exit(-1);}
  wTEMP_P = malloc (wN2D * ip_nPLEVELS * sizeof(float));
  if (wTEMP_P==NULL) {fprintf(stderr, "rh.c : Cannot allocate wTEMP_P\n"); exit(-1);}
  
  #pragma omp parallel for private(i)
  for (i=0; i<ip_nALEVELS; i++) {
   interpolate_3d_z (wTEMP, ip_ALEVELS[i], wHEIGHT, &wTEMP_A[wN2D*i]);
  }
  #pragma omp parallel for private(i)
  for (i=0; i<ip_nPLEVELS; i++) {
   interpolate_3d_z (wTEMP, ip_PLEVELS[i], wPRESS, &wTEMP_P[wN2D*i]);
  }

}


void write_TEMP () {
  fprintf(stdout, "Writing TEMP\n");

  nc_error(nc_put_var_float(ncout_ID, idTEMP, wTEMP));
  nc_error(nc_put_var_float(ncout_ID, idTEMP_A, wTEMP_A));
  nc_error(nc_put_var_float(ncout_ID, idTEMP_P, wTEMP_P));
}

void set_meta_TEMP () {
  
  ncout_def_var_float("temp", 3, ncout_3D_DIMS, &idTEMP);
  ncout_def_var_float("temp_a", 3, ncout_3DA_DIMS, &idTEMP_A);
  ncout_def_var_float("temp_p", 3, ncout_3DP_DIMS, &idTEMP_P);

  ncout_set_meta (idTEMP, "long_name", "air_temperature");
  ncout_set_meta (idTEMP, "standard_name", "air_temperature");
  ncout_set_meta (idTEMP, "description", "");
  ncout_set_meta (idTEMP, "reference", "http://doc.omd.li/wrfpp/temp");
  ncout_set_meta (idTEMP, "units", "degree_Celsius");
  ncout_set_meta (idTEMP, "coordinates", "model_level lon lat");
  
  ncout_set_meta (idTEMP_A, "long_name", "air_temperature_on_altitude_level");
  ncout_set_meta (idTEMP_A, "standard_name", "air_temperature");
  ncout_set_meta (idTEMP_A, "description", "air temperature, interpolated to altitude levels");
  ncout_set_meta (idTEMP_A, "reference", "http://doc.omd.li/wrfpp/temp_a");
  ncout_set_meta (idTEMP_A, "units", "degree_Celsius");
  ncout_set_meta (idTEMP_A, "coordinates", "alti_level lon lat");
  
  
  ncout_set_meta (idTEMP_P, "long_name", "air_temperature_on_pressure_level");
  ncout_set_meta (idTEMP_P, "standard_name", "air_temperature");
  ncout_set_meta (idTEMP_P, "description", "air temperature, interpolated to pressure levels");
  ncout_set_meta (idTEMP_P, "reference", "http://doc.omd.li/wrfpp/temp_p");
  ncout_set_meta (idTEMP_P, "units", "degree_Celsius");
  ncout_set_meta (idTEMP_P, "coordinates", "press_level lon lat");
  
}


void free_TEMP () {
 
  free (wTEMP);
  free (wTEMP_A);
  free (wTEMP_P);
  free (wTHETA);
  free (wTK);
  
}
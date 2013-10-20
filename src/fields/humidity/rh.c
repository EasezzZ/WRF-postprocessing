#include "rh.h"

void load_RH () {
  fprintf(stdout, "Loading RH\n");
  int qvapor_id;

  nc_error(nc_inq_varid (wrfout_id, "QVAPOR", &qvapor_id));
  
  wRH = malloc (wN3D * sizeof(float));
  if (wRH==NULL) {fprintf(stderr, "rh.c : Cannot allocate wRH\n"); exit(-1);}
  
  wQVAPOR = malloc (wN3D * sizeof(float));
  if (wQVAPOR==NULL) {fprintf(stderr, "rh.c : Cannot allocate wQVAPOR\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, qvapor_id, wQVAPOR));
  
  double svp1=0.6112;
  double svp2=17.67;
  double svp3=29.65;
  double ep_3=0.622;
  double es;
  double qvs;
  
  int i;
  #pragma omp parallel for private(i)
  for (i=0; i<wN3D; i++) {
    es = 10.*svp1*exp(svp2*(wTEMP[i])/(wTK[i]-svp3));
    qvs = ep_3*es/ (wPRESS[i] - (1.-ep_3)*es);
    wRH[i] = 100.*MAX(MIN(wQVAPOR[i]/qvs,1.0),0.0);
  }
  
  
  wRH_A = malloc (wN2D * ip_nALEVELS * sizeof(float));
  if (wRH_A==NULL) {fprintf(stderr, "rh.c : Cannot allocate wRH_A\n"); exit(-1);}
  wRH_P = malloc (wN2D * ip_nPLEVELS * sizeof(float));
  if (wRH_P==NULL) {fprintf(stderr, "rh.c : Cannot allocate wRH_P\n"); exit(-1);}
  
  #pragma omp parallel for private(i)
  for (i=0; i<ip_nALEVELS; i++) {
   interpolate_3d_z (wRH, ip_ALEVELS[i], wHEIGHT, &wRH_A[wN2D*i]);
  }
  #pragma omp parallel for private(i)
  for (i=0; i<ip_nPLEVELS; i++) {
   interpolate_3d_z (wRH, ip_PLEVELS[i], wPRESS, &wRH_P[wN2D*i]);
  }
}


void write_RH () {
  fprintf(stdout, "Writing RH\n");
  nc_error(nc_put_var_float(ncout_ID, idRH, wRH));
  nc_error(nc_put_var_float(ncout_ID, idRH_A, wRH_A));
  nc_error(nc_put_var_float(ncout_ID, idRH_P, wRH_P));
}

void set_meta_RH () {
  
  ncout_def_var_float("rh", 3, ncout_3D_DIMS, &idRH);
  ncout_def_var_float("rh_a", 3, ncout_3DA_DIMS, &idRH_A);
  ncout_def_var_float("rh_p", 3, ncout_3DP_DIMS, &idRH_P);

  
  ncout_set_meta (idRH, "long_name", "relative_humidity");
  ncout_set_meta (idRH, "standard_name", "relative_humidity");
  ncout_set_meta (idRH, "description", "");
  ncout_set_meta (idRH, "reference", "http://doc.omd.li/wrfpp/rh");
  ncout_set_meta (idRH, "units", "percent");
  ncout_set_meta (idRH, "coordinates", "model_level lon lat");
  
  ncout_set_meta (idRH_A, "long_name", "relative_humidity_on_altitude_level");
  ncout_set_meta (idRH_A, "standard_name", "relative_humidity");
  ncout_set_meta (idRH_A, "description", "relative humidity in air, interpolated to altitude levels");
  ncout_set_meta (idRH_A, "reference", "http://doc.omd.li/wrfpp/rh_a");
  ncout_set_meta (idRH_A, "units", "percent");
  ncout_set_meta (idRH_A, "coordinates", "alti_level lon lat");
  
  ncout_set_meta (idRH_P, "long_name", "relative_humidity_on_pressure_level");
  ncout_set_meta (idRH_P, "standard_name", "relative_humidity");
  ncout_set_meta (idRH_P, "description", "relative humidity in air, interpolated to pressure levels");
  ncout_set_meta (idRH_P, "reference", "http://doc.omd.li/wrfpp/rh_p");
  ncout_set_meta (idRH_P, "units", "percent");
  ncout_set_meta (idRH_P, "coordinates", "press_level lon lat");
  
  
}


void free_RH () {
 
  free(wRH_A);
  free(wRH_P);
  
  free (wRH);
  free (wQVAPOR);
  
}
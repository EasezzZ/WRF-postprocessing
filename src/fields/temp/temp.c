#include "temp.h"

void load_TEMP () {
  
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
  
  int i;
  for (i=0; i<wN3D; i++) {
    wTHETA[i] += 300;
    double pi = pow( (wPRESS[i]*100/p1000mb), (r_d/cp) );
    wTK[i] = pi*wTHETA[i];
    wTEMP[i] = wTK[i] - 273.16;
  }
           

}


void write_TEMP () {
  nc_error(nc_put_var_float(ncout_ID, idTEMP, wTEMP));
}

void set_meta_TEMP () {
  
  ncout_def_var_float("temp", 3, ncout_3D_DIMS, &idTEMP);

  ncout_set_meta (idTEMP, "long_name", "air_temperature");
  ncout_set_meta (idTEMP, "standard_name", "air_temperature");
  ncout_set_meta (idTEMP, "description", "");
  ncout_set_meta (idTEMP, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/temp/temp.c");
  ncout_set_meta (idTEMP, "units", "degree_Celsius");
  ncout_set_meta (idTEMP, "coordinates", "levels lon lat");
  
}


void free_TEMP () {
 
  free (wTEMP);
  free (wTHETA);
  free (wTK);
  
}
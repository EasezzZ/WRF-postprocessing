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
  for (i=0; i<wN3D; i++) {
    es = 10.*svp1*exp(svp2*(wTEMP[i])/(wTK[i]-svp3));
    qvs = ep_3*es/ (wPRESS[i] - (1.-ep_3)*es);
    wRH[i] = 100.*MAX(MIN(wQVAPOR[i]/qvs,1.0),0.0);
  }
  

}


void write_RH () {
  fprintf(stdout, "Writing RH\n");
  nc_error(nc_put_var_float(ncout_ID, idRH, wRH));
}

void set_meta_RH () {
  
  ncout_def_var_float("rh", 3, ncout_3D_DIMS, &idRH);

  
  ncout_set_meta (idRH, "long_name", "relative_humidity");
  ncout_set_meta (idRH, "standard_name", "relative_humidity");
  ncout_set_meta (idRH, "description", "");
  ncout_set_meta (idRH, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/humidity/rh.c");
  ncout_set_meta (idRH, "units", "percent");
  ncout_set_meta (idRH, "coordinates", "model_level lon lat");
  
  
}


void free_RH () {
 
  free (wRH);
  free (wQVAPOR);
  
}
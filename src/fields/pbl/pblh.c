#include "pblh.h"

void load_PBLH () {
  
  int pblh_id;

  nc_error(nc_inq_varid (wrfout_id, "PBLH", &pblh_id));
  
  wPBLH = malloc (wN2D * sizeof(float));
  if (wPBLH==NULL) {fprintf(stderr, "pblh.c : Cannot allocate wPBLH\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, pblh_id, wPBLH));

}


void write_PBLH () {
  nc_error(nc_put_var_float(ncout_ID, idPBLH, wPBLH));
}

void set_meta_PBLH () {

  int dim_ids[2];
  
  dim_ids[0] = ncout_DIM_Y;
  dim_ids[1] = ncout_DIM_X;
  
  ncout_def_var_float("pblh", 2, dim_ids, &idPBLH);

  ncout_set_meta (idPBLH, "long_name", "atmosphere_boundary_layer_thickness");
  ncout_set_meta (idPBLH, "standard_name", "atmosphere_boundary_layer_thickness");
  ncout_set_meta (idPBLH, "description", "The atmosphere boundary layer thickness is the \"depth\" or \"height\" of the (atmosphere) planetary boundary layer.");
  ncout_set_meta (idPBLH, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/pbl/pblh.c");
  ncout_set_meta (idPBLH, "units", "m");
  ncout_set_meta (idPBLH, "coordinates", "lon lat");
  
}


void free_PBLH () {
 
  free (wPBLH);
  
}
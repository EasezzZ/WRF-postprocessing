#include "pblh.h"

void load_PBLH () {
  
  int pblh_id;

  nc_error(nc_inq_varid (wrfout_id, "PBLH", &pblh_id));
  
  wPBLH = malloc (wN2D * sizeof(float));
  if (wPBLH==NULL) {fprintf(stderr, "pblh.c : Cannot allocate wPBLH\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, pblh_id, wPBLH));

}


void write_PBLH () {
  
  int nc_id;
  int dim_ids[2];  
  int pblh_id, lat_id, lon_id;
  
  ncout_init("pbl", "pblh", DIM_X | DIM_Y, &nc_id, dim_ids);
  
  nc_error(nc_def_var (nc_id, "pblh", NC_FLOAT, 2, dim_ids, &pblh_id));
  
  set_LATLON_meta(nc_id, dim_ids, &lat_id, &lon_id);

  ncout_set_global_meta (nc_id);

  ncout_set_meta (nc_id, pblh_id, "long_name", "atmosphere_boundary_layer_thickness");
  ncout_set_meta (nc_id, pblh_id, "standard_name", "atmosphere_boundary_layer_thickness");
  ncout_set_meta (nc_id, pblh_id, "description", "The atmosphere boundary layer thickness is the \"depth\" or \"height\" of the (atmosphere) planetary boundary layer.");
  ncout_set_meta (nc_id, pblh_id, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/pbl/pblh.c");
  ncout_set_meta (nc_id, pblh_id, "units", "m");
  ncout_set_meta (nc_id, pblh_id, "coordinates", "lon lat");
  
  nc_error(nc_enddef(nc_id));
  
  nc_error(nc_put_var_float(nc_id, pblh_id, wPBLH));
  
  set_LATLON_data(nc_id, lat_id, lon_id);
  
  ncout_close(nc_id);
  
}


void free_PBLH () {
 
  free (wPBLH);
  
}
#include "topo.h"

void load_TOPO () {
  
  int topo_id;

  nc_error(nc_inq_varid (wrfout_id, "HGT", &topo_id));
  
  wTOPO = malloc (wN2D * sizeof(float));
  if (wTOPO==NULL) {fprintf(stderr, "topo.c : Cannot allocate wTOPO\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, topo_id, wTOPO));

}


void write_TOPO () {
  
  int nc_id;
  int dim_ids[2];  
  int topo_id, lat_id, lon_id;
  
  ncout_init("grid", "topo", DIM_X | DIM_Y, &nc_id, dim_ids);
  
  nc_error(nc_def_var (nc_id, "topo", NC_FLOAT, 2, dim_ids, &topo_id));
  
  set_LATLON_meta(nc_id, dim_ids, &lat_id, &lon_id);

  ncout_set_global_meta (nc_id);

  ncout_set_meta (nc_id, topo_id, "long_name", "model_terrain_elevation");
  ncout_set_meta (nc_id, topo_id, "standard_name", "");
  ncout_set_meta (nc_id, topo_id, "description", "Terrain elevation above mean sea level, as seen by the numerical model. Terrain is smoothed to the model's grid resolution.");
  ncout_set_meta (nc_id, topo_id, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/grid/topo.c");
  ncout_set_meta (nc_id, topo_id, "units", "m");
  ncout_set_meta (nc_id, topo_id, "coordinates", "lon lat");
  
  nc_error(nc_enddef(nc_id));
  
  nc_error(nc_put_var_float(nc_id, topo_id, wTOPO));
  
  set_LATLON_data(nc_id, lat_id, lon_id);
  
  ncout_close(nc_id);
  
}


void free_TOPO () {
 
  free (wTOPO);
  
}
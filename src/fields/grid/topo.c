#include "topo.h"

void load_TOPO () {
  
  int topo_id;

  nc_error(nc_inq_varid (wrfout_id, "HGT", &topo_id));
  
  wTOPO = malloc (wNX * wNY * sizeof(float));
  if (wTOPO==NULL) {fprintf(stderr, "topo.c : Cannot allocate wTOPO\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, topo_id, wTOPO));

}


void write_TOPO () {
  
  int nc_id;
  int dim_ids[2];  
  int topo_id;
  int lat_id, lon_id;
  
  ncout_init("grid", "topo", DIM_X | DIM_Y, &nc_id, dim_ids);
  
  nc_error(nc_def_var (nc_id, "topo", NC_FLOAT, 2, dim_ids, &topo_id));

  ncout_set_global_meta (nc_id);

  set_LATLON_meta(nc_id, dim_ids, &lat_id, &lon_id);

  static char coordinates[]          = "lon lat";
  static char units[]          = "m";
  nc_error(nc_put_att_text (nc_id, topo_id, "coordinates", strlen(coordinates), coordinates));
  nc_error(nc_put_att_text (nc_id, topo_id, "units", strlen(units), units));
  
  nc_error(nc_enddef(nc_id));
  
  nc_error(nc_put_var_float(nc_id, topo_id, wTOPO));
  
  set_LATLON_data(nc_id, lat_id, lon_id);
  
  ncout_close(nc_id);
  
}


void free_TOPO () {
 
  free (wTOPO);
  
}
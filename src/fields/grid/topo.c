#include "topo.h"

void load_TOPO () {
  
  int topo_id;

  nc_error(nc_inq_varid (wrfout_id, "HGT", &topo_id));
  
  wTOPO = malloc (wNX * wNY * sizeof(float));
  if (wTOPO==NULL) {fprintf(stderr, "terrain.c : Cannot allocate wTOPO\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, topo_id, wTOPO));

}


void write_TOPO () {
  
  int nc_id;
  int dim_ids[2];  
  int topo_id;
  
  ncout_init("out/terrain.nc", DIM_X | DIM_Y, &nc_id, dim_ids);
  
  nc_error(nc_def_var (nc_id, "terrain", NC_FLOAT, 2, dim_ids, &topo_id));

  ncout_set_global_meta (nc_id);
  nc_error(nc_enddef(nc_id));
  
  nc_error(nc_put_var_float(nc_id, topo_id, wTOPO));
  
  ncout_close(nc_id);
  
}


void free_TOPO () {
 
  free (wTOPO);
  
}
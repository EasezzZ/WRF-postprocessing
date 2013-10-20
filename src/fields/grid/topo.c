#include "topo.h"

void load_TOPO () {
  fprintf(stdout, "Loading TOPO\n");
  int topo_id;

  nc_error(nc_inq_varid (wrfout_id, "HGT", &topo_id));
  
  wTOPO = malloc (wN2D * sizeof(float));
  if (wTOPO==NULL) {fprintf(stderr, "topo.c : Cannot allocate wTOPO\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, topo_id, wTOPO));

}


void write_TOPO () {
  fprintf(stdout, "Writing TOPO\n");
  nc_error(nc_put_var_float(ncout_ID, idTOPO, wTOPO));
}

void set_meta_TOPO () {
  
  ncout_def_var_float("topo", 2, ncout_2D_DIMS, &idTOPO);

  ncout_set_meta (idTOPO, "long_name", "model_terrain_elevation");
  ncout_set_meta (idTOPO, "standard_name", "");
  ncout_set_meta (idTOPO, "description", "Terrain elevation above mean sea level, as seen by the numerical model. Terrain is smoothed to the model's grid resolution.");
  ncout_set_meta (idTOPO, "reference", "http://doc.omd.li/wrfpp/topo");
  ncout_set_meta (idTOPO, "units", "m");
  ncout_set_meta (idTOPO, "coordinates", "lon lat");
  
}


void free_TOPO () {
 
  free (wTOPO);
  
}
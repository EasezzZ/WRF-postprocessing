#include "model_level.h"

void load_MODEL_LEVEL () {
  fprintf(stdout, "Loading MODEL_LEVEL\n");
  int model_level_id;

  nc_error(nc_inq_varid (wrfout_id, "ZNU", &model_level_id));
  
  wMODEL_LEVEL = malloc (wNZ * sizeof(float));
  if (wMODEL_LEVEL==NULL) {fprintf(stderr, "model_level.c : Cannot allocate wMODEL_LEVEL\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, model_level_id, wMODEL_LEVEL));

}


void write_MODEL_LEVEL () {
  fprintf(stdout, "Writing MODEL_LEVEL\n");
  nc_error(nc_put_var_float(ncout_ID, idMODEL_LEVEL, wMODEL_LEVEL));
}

void set_meta_MODEL_LEVEL () {
  
  ncout_def_var_float("model_level", 1, ncout_1DZ_DIM, &idMODEL_LEVEL);

  ncout_set_meta (idMODEL_LEVEL, "long_name", "model_sigma_levels");
  ncout_set_meta (idMODEL_LEVEL, "standard_name", "");
  ncout_set_meta (idMODEL_LEVEL, "description", "Vertical levels of the model grid");
  ncout_set_meta (idMODEL_LEVEL, "reference", "http://doc.omd.li/wrfpp/model_level");
  ncout_set_meta (idMODEL_LEVEL, "units", "");
  ncout_set_meta (idMODEL_LEVEL, "coordinates", "model_level");
  // TODO : ncout_set_meta (idLON, "_CoordinateAxisType", "Sigma");

}


void free_MODEL_LEVEL () {
 
  free (wMODEL_LEVEL);
  
}
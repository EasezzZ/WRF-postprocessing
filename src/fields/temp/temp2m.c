#include "temp2m.h"

void load_TEMP2M () {
  fprintf(stdout, "Loading TEMP2M\n");

  int temp2m_id;

  nc_error(nc_inq_varid (wrfout_id, "T2", &temp2m_id));
  
  wTEMP2M = malloc (wN2D * sizeof(float));
  if (wTEMP2M==NULL) {fprintf(stderr, "temp2m.c : Cannot allocate wTEMP2M\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, temp2m_id, wTEMP2M));
  
  int i;
  for (i=0; i<wN2D; i++) {
    wTEMP2M[i] -= 273.16;
  }

}


void write_TEMP2M () {
  fprintf(stdout, "Writing TEMP2M\n");
  nc_error(nc_put_var_float(ncout_ID, idTEMP2M, wTEMP2M));
}

void set_meta_TEMP2M () {
  
  ncout_def_var_float("temp2m", 2, ncout_2D_DIMS, &idTEMP2M);

  ncout_set_meta (idTEMP2M, "long_name", "air_temperature_2m_above_surface");
  ncout_set_meta (idTEMP2M, "standard_name", "air_temperature_2m_above_surface");
  ncout_set_meta (idTEMP2M, "description", "2m Air temperature is the bulk temperature of the air, 2 meters above surface. ");
  ncout_set_meta (idTEMP2M, "reference", "http://doc.omd.li/wrfpp/temp2m");
  ncout_set_meta (idTEMP2M, "units", "degree_Celsius");
  ncout_set_meta (idTEMP2M, "coordinates", "lon lat");
  
}


void free_TEMP2M () {
 
  free (wTEMP2M);
  
}
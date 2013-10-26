#include "tc2.h"

void load_TC2 () {
  fprintf(stdout, "Loading TC2\n");

  int tc2_id;

  nc_error(nc_inq_varid (wrfout_id, "T2", &tc2_id));
  
  wTC2 = malloc (wN2D * sizeof(float));
  if (wTC2==NULL) {fprintf(stderr, "tc2.c : Cannot allocate wTC2\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, tc2_id, wTC2));
  
  int i;
  for (i=0; i<wN2D; i++) {
    wTC2[i] -= 273.16;
  }

}


void write_TC2 () {
  fprintf(stdout, "Writing TC2\n");
  nc_error(nc_put_var_float(ncout_ID, idTC2, wTC2));
}

void set_meta_TC2 () {
  
  ncout_def_var_float("tc2", 2, ncout_2D_DIMS, &idTC2);

  ncout_set_meta (idTC2, "long_name", "air_temperature_2m_above_surface");
  ncout_set_meta (idTC2, "standard_name", "air_temperature_2m_above_surface");
  ncout_set_meta (idTC2, "description", "2m Air temperature is the bulk temperature of the air, 2 meters above surface. ");
  ncout_set_meta (idTC2, "reference", "http://doc.omd.li/wrfpp/tc2");
  ncout_set_meta (idTC2, "units", "degree_Celsius");
  ncout_set_meta (idTC2, "coordinates", "lon lat");
  
}


void free_TC2 () {
 
  free (wTC2);
  
}
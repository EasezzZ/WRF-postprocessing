#include "tc2.h"

void load_TC2 () {
  
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
  
  int nc_id;
  int dim_ids[2];  
  int tc2_id, lat_id, lon_id;
  
  ncout_init("temp", "tc2", DIM_X | DIM_Y, &nc_id, dim_ids);
  
  nc_error(nc_def_var (nc_id, "tc2", NC_FLOAT, 2, dim_ids, &tc2_id));
  
  set_LATLON_meta(nc_id, dim_ids, &lat_id, &lon_id);

  ncout_set_global_meta (nc_id);

  ncout_set_meta (nc_id, tc2_id, "long_name", "air_temperature_2m_above_surface");
  ncout_set_meta (nc_id, tc2_id, "standard_name", "air_temperature_2m_above_surface");
  ncout_set_meta (nc_id, tc2_id, "description", "2m Air temperature is the bulk temperature of the air, 2 meters above surface. ");
  ncout_set_meta (nc_id, tc2_id, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/temp/tc2.c");
  ncout_set_meta (nc_id, tc2_id, "units", "degree_Celsius");
  ncout_set_meta (nc_id, tc2_id, "coordinates", "lon lat");
  
  nc_error(nc_enddef(nc_id));
  
  nc_error(nc_put_var_float(nc_id, tc2_id, wTC2));
  
  set_LATLON_data(nc_id, lat_id, lon_id);
  
  ncout_close(nc_id);
  
}


void free_TC2 () {
 
  free (wTC2);
  
}
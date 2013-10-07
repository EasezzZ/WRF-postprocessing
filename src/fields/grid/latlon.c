#include "latlon.h"

void load_LATLON () {
  
  int lat_id;
  int lon_id;

  nc_error(nc_inq_varid (wrfout_id, "XLAT", &lat_id));
  nc_error(nc_inq_varid (wrfout_id, "XLONG", &lon_id));
  
  wLAT = malloc (wNX * wNY * sizeof(float));
  if (wLAT==NULL) {fprintf(stderr, "latlon.c : Cannot allocate wLAT\n"); exit(-1);}
  wLON = malloc (wNX * wNY * sizeof(float));
  if (wLON==NULL) {fprintf(stderr, "latlon.c : Cannot allocate wLON\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, lat_id, wLAT));
  nc_error(nc_get_var_float(wrfout_id, lon_id, wLON));
  
}


void write_LATLON () {
  
  int nc_id;
  
  int dim_ids[2];  
  
  int lat_id;
  int lon_id;
  
  ncout_init("grid", "latlon", DIM_X | DIM_Y, &nc_id, dim_ids);
  
  set_LATLON_meta(nc_id, dim_ids, &lat_id, &lon_id);
  
  ncout_set_global_meta (nc_id);
  
  nc_error(nc_enddef(nc_id));

  set_LATLON_data(nc_id, lat_id, lon_id);
  
  ncout_close(nc_id);

}

void set_LATLON_data (int nc_id, int lat_id, int lon_id) {
  nc_error(nc_put_var_float(nc_id, lat_id, wLAT));
  nc_error(nc_put_var_float(nc_id, lon_id, wLON)); 
}

void set_LATLON_meta (int nc_id, int *dim_ids, int *lat_idp, int *lon_idp) {
  
  nc_error(nc_def_var (nc_id, "lat", NC_FLOAT, 2, dim_ids, lat_idp));
  nc_error(nc_def_var (nc_id, "lon", NC_FLOAT, 2, dim_ids, lon_idp));

  static char lat_name[]          = "latitude";
  static char lat_units[]          = "degrees_north";
  static char lat_axis[]          = "Lat";
  static char coordinates[]          = "lon lat";
  nc_error(nc_put_att_text (nc_id, *lat_idp, "long_name", strlen(lat_name), lat_name));
  nc_error(nc_put_att_text (nc_id, *lat_idp, "standard_name", strlen(lat_name), lat_name));
  nc_error(nc_put_att_text (nc_id, *lat_idp, "units", strlen(lat_units), lat_units));
  nc_error(nc_put_att_text (nc_id, *lat_idp, "_CoordinateAxisType", strlen(lat_axis), lat_axis));
  nc_error(nc_put_att_text (nc_id, *lat_idp, "coordinates", strlen(coordinates), coordinates));
  
  static char lon_name[]          = "longitude";
  static char lon_units[]          = "degrees_east";
  static char lon_axis[]          = "Lon";
  
  nc_error(nc_put_att_text (nc_id, *lon_idp, "long_name", strlen(lon_name), lon_name));
  nc_error(nc_put_att_text (nc_id, *lon_idp, "standard_name", strlen(lon_name), lon_name));
  nc_error(nc_put_att_text (nc_id, *lon_idp, "units", strlen(lon_units), lon_units));
  nc_error(nc_put_att_text (nc_id, *lon_idp, "_CoordinateAxisType", strlen(lon_axis), lon_axis));
  nc_error(nc_put_att_text (nc_id, *lon_idp, "coordinates", strlen(coordinates), coordinates));

  
}

void free_LATLON () {
 
  free (wLAT);
  free (wLON);
  
}
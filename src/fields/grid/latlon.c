#include "latlon.h"

void load_LATLON () {
  
  int lat_id;
  int lon_id;

  nc_error(nc_inq_varid (wrfout_id, "XLAT", &lat_id));
  nc_error(nc_inq_varid (wrfout_id, "XLONG", &lon_id));
  
  wLAT = malloc (wN2D * sizeof(float));
  if (wLAT==NULL) {fprintf(stderr, "latlon.c : Cannot allocate wLAT\n"); exit(-1);}
  wLON = malloc (wN2D * sizeof(float));
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

  ncout_set_meta (nc_id, *lat_idp, "long_name", "latitude");
  ncout_set_meta (nc_id, *lat_idp, "standard_name", "latitude");
  ncout_set_meta (nc_id, *lat_idp, "units", "degrees_north");
  ncout_set_meta (nc_id, *lat_idp, "_CoordinateAxisType", "Lat");
  ncout_set_meta (nc_id, *lat_idp, "coordinates", "lon lat");
  
  ncout_set_meta (nc_id, *lon_idp, "long_name", "longitude");
  ncout_set_meta (nc_id, *lon_idp, "standard_name", "longitude");
  ncout_set_meta (nc_id, *lon_idp, "units", "degrees_east");
  ncout_set_meta (nc_id, *lon_idp, "_CoordinateAxisType", "Lon");
  ncout_set_meta (nc_id, *lon_idp, "coordinates", "lon lat");
  
}

void free_LATLON () {
 
  free (wLAT);
  free (wLON);
  
}
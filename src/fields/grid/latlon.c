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
  nc_error(nc_put_var_float(ncout_ID, idLAT, wLAT));
  nc_error(nc_put_var_float(ncout_ID, idLON, wLON)); 
}

void set_meta_LATLON () {
  
  int dim_ids[2];
  
  dim_ids[0] = ncout_DIM_Y;
  dim_ids[1] = ncout_DIM_X;
  
  ncout_def_var_float("lat", 2, dim_ids, &idLAT);
  ncout_def_var_float("lon", 2, dim_ids, &idLON);

  ncout_set_meta (idLAT, "long_name", "latitude");
  ncout_set_meta (idLAT, "standard_name", "latitude");
  ncout_set_meta (idLAT, "units", "degrees_north");
  ncout_set_meta (idLAT, "_CoordinateAxisType", "Lat");
  ncout_set_meta (idLAT, "coordinates", "lon lat");
  
  ncout_set_meta (idLON, "long_name", "longitude");
  ncout_set_meta (idLON, "standard_name", "longitude");
  ncout_set_meta (idLON, "units", "degrees_east");
  ncout_set_meta (idLON, "_CoordinateAxisType", "Lon");
  ncout_set_meta (idLON, "coordinates", "lon lat");
  
}

void free_LATLON () {
 
  free (wLAT);
  free (wLON);
  
}
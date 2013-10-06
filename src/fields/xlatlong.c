#include "xlatlong.h"

void load_XLATLONG () {
  
  int xlat_id;
  int xlong_id;

  nc_error(nc_inq_varid (wrfout_id, "XLAT", &xlat_id));
  nc_error(nc_inq_varid (wrfout_id, "XLONG", &xlong_id));
  
  XLAT = malloc (nWE * nSN * sizeof(float));
  if (XLAT==NULL) {fprintf(stderr, "xlatlong.c : Cannot allocate XLAT\n"); exit(-1);}
  XLONG = malloc (nWE * nSN * sizeof(float));
  if (XLONG==NULL) {fprintf(stderr, "xlatlong.c : Cannot allocate XLONG\n"); exit(-1);}

  nc_get_var_float(wrfout_id, xlat_id, XLAT);
  nc_get_var_float(wrfout_id, xlong_id, XLONG);
  
}


void write_XLATLONG () {
  
  int nc_id;
  
  int dim_ids[2];  
  
  int lat_id;
  int lon_id;
  
  static char title[] = "example netCDF dataset";
  
  nc_error(nc_create("out/latlon.nc", 0, &nc_id));
  
  nc_error(nc_def_dim(nc_id, "south_north", nSN, &dim_ids[0]));
  nc_error(nc_def_dim(nc_id, "west_east", nWE, &dim_ids[1]));
  
  nc_error(nc_def_var (nc_id, "latitude", NC_FLOAT, 2, dim_ids, &lat_id));
  nc_error(nc_def_var (nc_id, "longitude", NC_FLOAT, 2, dim_ids, &lon_id));
  
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "title", strlen(title), title));
  
  nc_error(nc_enddef(nc_id));
  
  nc_error(nc_put_var_float(nc_id, lat_id, XLAT));
  nc_error(nc_put_var_float(nc_id, lon_id, XLONG));
  
  
}


void free_XLATLONG () {
 
  free (XLAT);
  free (XLONG);
  
}
#include "uv10.h"

void load_UV10 () {
  
  int u10_id;
  int v10_id;

  nc_error(nc_inq_varid (wrfout_id, "U10", &u10_id));
  nc_error(nc_inq_varid (wrfout_id, "V10", &v10_id));
  
  U10 = malloc (nWE * nSN * sizeof(float));
  if (U10==NULL) {fprintf(stderr, "uv10.c : Cannot allocate U10\n"); exit(-1);}
  V10 = malloc (nWE * nSN * sizeof(float));
  if (V10==NULL) {fprintf(stderr, "uv10.c : Cannot allocate V10\n"); exit(-1);}

  nc_get_var_float(wrfout_id, u10_id, U10);
  nc_get_var_float(wrfout_id, v10_id, V10);
  
  double deg2rad = M_PI/180;
  
  if (MAP_PROJ == 1 || MAP_PROJ == 2) {
    double cone;
    
    if (MAP_PROJ == 1) { // lambert conformal	
	if ( (fabs(TRUELAT1 - TRUELAT2) > 0.1)  && (fabs(TRUELAT2 - 90.) > 0.1)) {
	  cone = ( pow(10, cos(TRUELAT1*deg2rad)) - pow(10, cos(TRUELAT2*deg2rad)) )
		/ ( pow(10, tan(45. -fabs(TRUELAT1/2.)*deg2rad))
		    - pow(10, tan(45. -fabs(TRUELAT2/2.)*deg2rad)) );
	} else {
	  cone = sin(fabs(TRUELAT1)*deg2rad);
	}	
    } else if (MAP_PROJ == 2) { // polar stereographic
      cone = 1.;
    }
    
    float * umet10 = malloc (nWE * nSN * sizeof(float));
    if (umet10==NULL) {fprintf(stderr, "uv10.c : Cannot allocate UMET10\n"); exit(-1);}
    float * vmet10 = malloc (nWE * nSN * sizeof(float));
    if (vmet10==NULL) {fprintf(stderr, "uv10.c : Cannot allocate VMET10\n"); exit(-1);}
    
    int is_stag = 1;
    int is_missing_val = 0;
    calc_uvmet (U10, V10, umet10, vmet10, cone, is_stag, is_missing_val);
    
    U10 = umet10;
    V10 = vmet10;
    
    free (umet10);
    free (vmet10);
    
  }
  
  
}


void write_UV10 () {
  
  int nc_id;
  
  int dim_ids[2];  
  
  int u10_id;
  int v10_id;
  
  static char title[] = "example netCDF dataset";

  
  nc_error(nc_create("out/wind/uv10.vec.nc", 0, &nc_id));
  
  nc_error(nc_def_dim(nc_id, "south_north", nSN, &dim_ids[0]));
  nc_error(nc_def_dim(nc_id, "west_east", nWE, &dim_ids[1]));
  
  nc_error(nc_def_var (nc_id, "u10", NC_FLOAT, 2, dim_ids, &u10_id));
  nc_error(nc_def_var (nc_id, "v10", NC_FLOAT, 2, dim_ids, &v10_id));
  
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "title", strlen(title), title));
  
  nc_error(nc_enddef(nc_id));
  
  nc_error(nc_put_var_float(nc_id, u10_id, U10));
  nc_error(nc_put_var_float(nc_id, v10_id, V10));
  

  
}

void write_UV10_pol () {
  
  int nc_id;
  
  int dim_ids[2];  
  
  int dir10_id;
  int speed10_id;
  
  static char title[] = "example netCDF dataset";
  
  
  float * dir10 = malloc (nWE * nSN * sizeof(float));
  if (dir10==NULL) {fprintf(stderr, "uv10.c : Cannot allocate DIR10\n"); exit(-1);}
  float * speed10 = malloc (nWE * nSN * sizeof(float));
  if (speed10==NULL) {fprintf(stderr, "uv10.c : Cannot allocate SPEED10\n"); exit(-1);}
  
  int i;
  int nvals = nWE * nSN;
  for (i=0; i<nvals; i++) {
    dir10[i] = fmod( (atan2(V10[i], U10[i]) * 180 / M_PI + 360) , 360);
    speed10[i] = sqrt( pow(U10[i],2) + pow(V10[i],2) );
  }
  
  nc_error(nc_create("out/wind/uv10.pol.nc", 0, &nc_id));
  
  nc_error(nc_def_dim(nc_id, "south_north", nSN, &dim_ids[0]));
  nc_error(nc_def_dim(nc_id, "west_east", nWE, &dim_ids[1]));
  
  nc_error(nc_def_var (nc_id, "dir10", NC_FLOAT, 2, dim_ids, &dir10_id));
  nc_error(nc_def_var (nc_id, "speed10", NC_FLOAT, 2, dim_ids, &speed10_id));
  
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "title", strlen(title), title));
  
  nc_error(nc_enddef(nc_id));
  
  nc_error(nc_put_var_float(nc_id, dir10_id, dir10));
  nc_error(nc_put_var_float(nc_id, speed10_id, speed10));
  
    
  free (dir10);
  free (speed10);
  
}


void free_UV10 () {
 
  free (U10);
  free (V10);
  
}
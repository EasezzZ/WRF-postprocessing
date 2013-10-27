#include "lambert.h"

void set_meta_LAMBERT () {
  
  int idLAMBERT;
    
  nc_def_var (ncout_ID, "Lambert_Conformal", NC_INT, 0, 0, &idLAMBERT);
  ncout_set_meta (idLAMBERT, "grid_mapping_name", "lambert_conformal_conic");
  

  float att[2];
  int att_int[1];

  
  nc_get_att_float(wrfout_id, NC_GLOBAL, "TRUELAT1", &att[0]);
  nc_get_att_float(wrfout_id, NC_GLOBAL, "TRUELAT2", &att[1]);
  nc_put_att_float(ncout_ID, idLAMBERT, "standard_parallel", NC_FLOAT, 2, att);
    
  nc_get_att_float(wrfout_id, NC_GLOBAL, "STAND_LON", &att[0]);
  nc_put_att_float(ncout_ID, idLAMBERT, "longitude_of_central_meridian", NC_FLOAT, 1, att);
  
  nc_get_att_float(wrfout_id, NC_GLOBAL, "MOAD_CEN_LAT", &att[0]);
  nc_put_att_float(ncout_ID, idLAMBERT, "latitude_of_projection_origin", NC_FLOAT, 1, att);
  
  att[0] = 6370000.;
  nc_put_att_float(ncout_ID, idLAMBERT, "earth_radius", NC_FLOAT, 1, att);
  
  nc_get_att_float(wrfout_id, NC_GLOBAL, "DX", &att[0]);
  nc_put_att_float(ncout_ID, idLAMBERT, "grid_dx", NC_FLOAT, 1, att);
  
  nc_get_att_float(wrfout_id, NC_GLOBAL, "DY", &att[0]);
  nc_put_att_float(ncout_ID, idLAMBERT, "grid_dy", NC_FLOAT, 1, att);
  
  att_int[0] = wNX;
  nc_put_att_int(ncout_ID, idLAMBERT, "grid_nx", NC_INT, 1, att_int);
  
  att_int[0] = wNY;
  nc_put_att_int(ncout_ID, idLAMBERT, "grid_ny", NC_INT, 1, att_int);
  
  nc_get_att_float(wrfout_id, NC_GLOBAL, "CEN_LAT", &att[0]);
  nc_put_att_float(ncout_ID, idLAMBERT, "grid_center_lat", NC_FLOAT, 1, att);
  
  nc_get_att_float(wrfout_id, NC_GLOBAL, "CEN_LON", &att[0]);
  nc_put_att_float(ncout_ID, idLAMBERT, "grid_center_lon", NC_FLOAT, 1, att);
  
  att[0] = wLAT[0];
  nc_put_att_float(ncout_ID, idLAMBERT, "sw_corner_lat", NC_FLOAT, 1, att);
  att[0] = wLON[0];
  nc_put_att_float(ncout_ID, idLAMBERT, "sw_corner_lon", NC_FLOAT, 1, att);
  
  ncout_set_meta (idLAMBERT, "reference", "http://doc.omd.li/wrfpp/lambert_conformal");


}
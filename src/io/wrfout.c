#include "wrfout.h"

void open_wrfout (const char *path) {
  
  nc_error(nc_open(path, NC_NOWRITE, &wrfout_id));
  
  int WE_id; // west_east
  int SN_id; // south_north
  int BT_id; // bottom_top
  int time_id; // bottom_top
    
  nc_error(nc_inq_dimid(wrfout_id, "west_east", &WE_id));
  nc_error(nc_inq_dimid(wrfout_id, "south_north", &SN_id));
  nc_error(nc_inq_dimid(wrfout_id, "bottom_top", &BT_id));
  nc_error(nc_inq_dimid(wrfout_id, "Time", &time_id));
  
  nc_error(nc_inq_dimlen(wrfout_id, WE_id, &nWE));
  nc_error(nc_inq_dimlen(wrfout_id, SN_id, &nSN));
  nc_error(nc_inq_dimlen(wrfout_id, BT_id, &nBT));
  
  int ntime;
  nc_error(nc_inq_dimlen(wrfout_id, time_id, &ntime));
  
  if (ntime != 1) {
    fprintf(stderr, "FATAL : wrfout with n Time != 1 is not supported\n");
    exit(-1);
  } 
  
  nc_error(nc_get_att_int(wrfout_id, NC_GLOBAL, "MAP_PROJ", &MAP_PROJ));
  nc_error(nc_get_att_int(wrfout_id, NC_GLOBAL, "TRUELAT1", &TRUELAT1));
  nc_error(nc_get_att_int(wrfout_id, NC_GLOBAL, "TRUELAT2", &TRUELAT2));
  nc_error(nc_get_att_int(wrfout_id, NC_GLOBAL, "CEN_LON", &CEN_LON));
  
}



void close_wrfout () {
   nc_error(nc_close(wrfout_id));
}
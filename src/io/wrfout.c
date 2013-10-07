#include "wrfout.h"

void open_wrfout (const char *path) {
  
  nc_error(nc_open(path, NC_NOWRITE, &wrfout_id));
  
  int X_id; // west_east
  int Y_id; // south_north
  int Z_id; // bottom_top
  int time_id; // bottom_top

  
  nc_error(nc_inq_dimid(wrfout_id, "west_east", &X_id));
  nc_error(nc_inq_dimid(wrfout_id, "south_north", &Y_id));
  nc_error(nc_inq_dimid(wrfout_id, "bottom_top", &Z_id));
  nc_error(nc_inq_dimid(wrfout_id, "Time", &time_id));
  
  int ntime;
  nc_error(nc_inq_dimlen(wrfout_id, time_id, &ntime));
  
  if (ntime != 1) {
    fprintf(stderr, "FATAL : wrfout with n Time != 1 is not supported\n");
    exit(-1);
  } 
  
  nc_error(nc_inq_dimlen(wrfout_id, X_id, &wNX));
  nc_error(nc_inq_dimlen(wrfout_id, Y_id, &wNY));
  nc_error(nc_inq_dimlen(wrfout_id, Z_id, &wNZ));
  
  wN2D = wNX*wNY;
  wN3D = wN2D*wNZ;
  
  nc_error(nc_get_att_int(wrfout_id, NC_GLOBAL, "MAP_PROJ", &wMAP_PROJ));
  nc_error(nc_get_att_int(wrfout_id, NC_GLOBAL, "TRUELAT1", &wTRUELAT1));
  nc_error(nc_get_att_int(wrfout_id, NC_GLOBAL, "TRUELAT2", &wTRUELAT2));
  nc_error(nc_get_att_int(wrfout_id, NC_GLOBAL, "CEN_LON", &wCEN_LON));
  
  
}



void close_wrfout () {
   nc_error(nc_close(wrfout_id));
}
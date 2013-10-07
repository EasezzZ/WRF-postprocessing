#include "wrfout.h"

void open_wrfout (int argc, char *argv[]) {
  // ./wrfpp domain 2013-10-07_12 2013-10-08_04:00:00 2013-10-08_03:00:00

  
  wDOMAIN = argv[1];
  wRUN  = argv[2];
  wFRAME  = argv[3];
  if (argc == 5) {
    wFRAME_LAST = argv[4];
  } else {
    wFRAME_LAST = NULL;
  }
  
  int len = (strlen(wDOMAIN)*2+strlen(wRUN)+strlen(wFRAME)+10)* sizeof(char);
  char *path = malloc(len);

  snprintf(path, len, "in/%s/%s/%s_%s.nc", wDOMAIN, wRUN, wDOMAIN, wFRAME);
  
  fprintf(stdout, "Input file : %s\n", path);
  
  nc_error(nc_open(path, NC_NOWRITE, &wrfout_id));
  
  free (path);
  
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
  
  int run_start_len;
  nc_error(nc_inq_attlen (wrfout_id, NC_GLOBAL, "SIMULATION_START_DATE", &run_start_len));
  wRUN_START = malloc((run_start_len+1) * sizeof(char));
  nc_error(nc_get_att_text(wrfout_id, NC_GLOBAL, "SIMULATION_START_DATE", wRUN_START));
  wRUN_START[run_start_len] = '\0';
    
}



void close_wrfout () {
   nc_error(nc_close(wrfout_id));
   free(wRUN_START);
}
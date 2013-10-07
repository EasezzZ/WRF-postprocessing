#include "ncout.h"

int dim_ids[2];  


void ncout_init (const char* cat, const char* fname, int dims, int *nc_idp, int *dim_idsp) {
  
  int len = (strlen(wDOMAIN)+strlen(wRUN)+strlen(cat)+7)* sizeof(char);
  char *dir = malloc(len);

  snprintf(dir, len, "out/%s/%s/%s", wDOMAIN, wRUN, cat);
  
  int len_cmd = len + 10*sizeof(char);
  char *cmd = malloc(len_cmd);
  snprintf(cmd, len_cmd, "mkdir -p %s", dir);
  system(cmd);
  
  len += (strlen(wDOMAIN)+strlen(fname)+strlen(wFRAME)+7)* sizeof(char);
  char *path = malloc(len);
  snprintf(path, len, "%s/%s.%s.%s.nc", dir, wDOMAIN, fname, wFRAME);
  
  fprintf(stdout, "* output %s/%s\n",cat, fname);
  
  nc_error(nc_create(path, 0, nc_idp));  
  
  free (dir);
  free (cmd);
  free (path);
  
 if (dims == (DIM_X | DIM_Y)) {
    nc_error(nc_def_dim(*nc_idp, "y", wNY, &dim_idsp[0]));
    nc_error(nc_def_dim(*nc_idp, "x", wNX, &dim_idsp[1]));
  } else if (dims == (DIM_X | DIM_Y | DIM_Z)) {
    nc_error(nc_def_dim(*nc_idp, "z", wNZ, &dim_idsp[0]));
    nc_error(nc_def_dim(*nc_idp, "y", wNY, &dim_idsp[1]));
    nc_error(nc_def_dim(*nc_idp, "x", wNZ, &dim_idsp[2]));   
  } else {
    fprintf(stdout, "erreur ncout_init\n");
  }
  
}


void ncout_set_global_meta (int nc_id) {

  ncout_set_meta (nc_id, NC_GLOBAL, "title", "OpenMeteoData WRF-Europe model");
  ncout_set_meta (nc_id, NC_GLOBAL, "institution", "OpenMeteoData http://openmeteodata.org");
  ncout_set_meta (nc_id, NC_GLOBAL, "source", "WRF-ARW initialized from NCEP GFS + OMD Post-processing");
  //ncout_set_meta (nc_id, NC_GLOBAL, "history", "");
  ncout_set_meta (nc_id, NC_GLOBAL, "references", "http://wiki.openmeteodata.org/wiki/OMD_WRF");
  //ncout_set_meta (nc_id, NC_GLOBAL, "comment", "");
  ncout_set_meta (nc_id, NC_GLOBAL, "conventions", "CF-1.6");
  ncout_set_meta (nc_id, NC_GLOBAL, "license", "ODC-By http://opendatacommons.org/licenses/by/summary/");
  ncout_set_meta (nc_id, NC_GLOBAL, "run", wRUN);
  ncout_set_meta (nc_id, NC_GLOBAL, "run_start", wRUN_START);
  ncout_set_meta (nc_id, NC_GLOBAL, "frame", wFRAME);
  ncout_set_meta (nc_id, NC_GLOBAL, "domain", wDOMAIN);
  
}

void ncout_set_meta (int nc_id, int var_id, const char *name, const char * text) {
    nc_error(nc_put_att_text (nc_id, var_id, name, strlen(text), text));
}

void ncout_close (int nc_id) {
  nc_error(nc_close(nc_id));
}
#include "ncout.h"

void ncout_open () {



  // file name
  int len = (strlen(wDOMAIN) + strlen(wFRAME) + 8) * sizeof(char);
  char* filename = malloc(len);
  snprintf(filename, len, "%s-pp_%s.nc", wDOMAIN, wFRAME);

  fprintf(stdout, "Output file : %s\n", filename);
  
  nc_error(nc_create(filename, 0, &ncout_ID));

  free (filename);

  nc_error(nc_def_dim(ncout_ID, "model_level", wNZ, &ncout_DIM_Z));
  nc_error(nc_def_dim(ncout_ID, "y", wNY, &ncout_DIM_Y));
  nc_error(nc_def_dim(ncout_ID, "x", wNX, &ncout_DIM_X));
  nc_error(nc_def_dim(ncout_ID, "press_level", ip_nPLEVELS, &ncout_DIM_PLEVEL));
  nc_error(nc_def_dim(ncout_ID, "meters_level", ip_nMLEVELS, &ncout_DIM_MLEVEL));

  
  ncout_1DZ_DIM[0] = ncout_DIM_Z;
  ncout_1DP_DIM[0] = ncout_DIM_PLEVEL;
  ncout_1DM_DIM[0] = ncout_DIM_MLEVEL;
  
  ncout_2D_DIMS[0] = ncout_DIM_Y;
  ncout_2D_DIMS[1] = ncout_DIM_X;
  
  
  ncout_3D_DIMS[0] = ncout_DIM_Z;
  ncout_3D_DIMS[1] = ncout_DIM_Y;
  ncout_3D_DIMS[2] = ncout_DIM_X;
  
  ncout_3DP_DIMS[0] = ncout_DIM_PLEVEL;
  ncout_3DP_DIMS[1] = ncout_DIM_Y;
  ncout_3DP_DIMS[2] = ncout_DIM_X;
  
  ncout_3DM_DIMS[0] = ncout_DIM_MLEVEL;
  ncout_3DM_DIMS[1] = ncout_DIM_Y;
  ncout_3DM_DIMS[2] = ncout_DIM_X;
  

  ncout_set_meta (NC_GLOBAL, "title", "OpenMeteoData WRF-Europe model");
  ncout_set_meta (NC_GLOBAL, "institution", "OpenMeteoData http://openmeteodata.org");
  ncout_set_meta (NC_GLOBAL, "source", "WRF-ARW initialized from NCEP GFS + OMD Post-processing");
  //ncout_set_meta (NC_GLOBAL, "history", "");
  ncout_set_meta (NC_GLOBAL, "references", "http://wiki.openmeteodata.org/wiki/OMD_WRF");
  //ncout_set_meta (NC_GLOBAL, "comment", "");
  ncout_set_meta (NC_GLOBAL, "conventions", "CF-1.6");
  ncout_set_meta (NC_GLOBAL, "license", "ODC-By http://opendatacommons.org/licenses/by/summary/");
  ncout_set_meta (NC_GLOBAL, "run", wRUN);
  ncout_set_meta (NC_GLOBAL, "run_start", wRUN_START);
  ncout_set_meta (NC_GLOBAL, "frame", wFRAME);
  ncout_set_meta (NC_GLOBAL, "domain", wDOMAIN);
  ncout_set_meta (NC_GLOBAL, "_wrfpp-git-commit", git_commit);
  ncout_set_meta (NC_GLOBAL, "_wrfpp-git-status", git_status);

}


void ncout_set_meta (int var_id, const char *name, const char * text) {
    nc_error(nc_put_att_text (ncout_ID, var_id, name, strlen(text), text));
}

void ncout_def_var_float (char * name, int ndims, int *dim_ids, int *var_id) {
    nc_error(nc_def_var (ncout_ID, name, NC_FLOAT, ndims, dim_ids, var_id));
}

void ncout_close () {
  nc_error(nc_close(ncout_ID));
}

void ncout_enddef() {
  nc_error(nc_enddef(ncout_ID));
}
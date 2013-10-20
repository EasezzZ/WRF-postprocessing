#include "cloud.h"

void load_CLOUD () {
  fprintf(stdout, "Loading CLOUD\n");

  int cloud_id;

  nc_error(nc_inq_varid (wrfout_id, "CLDFRA", &cloud_id));
  
  wCLOUD = malloc (wN3D * sizeof(float));
  if (wCLOUD==NULL) {fprintf(stderr, "cloud.c : Cannot allocate wCLOUD\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, cloud_id, wCLOUD));
  
  
  wCLOUDPCT_H = malloc (wN2D * sizeof(float));
  if (wCLOUDPCT_H==NULL) {fprintf(stderr, "cloud.c : Cannot allocate wCLOUDPCT_H\n"); exit(-1);}
  wCLOUDPCT_M = malloc (wN2D * sizeof(float));
  if (wCLOUDPCT_M==NULL) {fprintf(stderr, "cloud.c : Cannot allocate wCLOUDPCT_M\n"); exit(-1);}
  wCLOUDPCT_L = malloc (wN2D * sizeof(float));
  if (wCLOUDPCT_L==NULL) {fprintf(stderr, "cloud.c : Cannot allocate wCLOUDPCT_L\n"); exit(-1);}
  
  int nzh, nzm, nzl;
  int nzhc, nzmc, nzlc;
  int i2d, z, i;
  for (i2d=0; i2d<wN2D; i2d++) {
    nzh=nzm=nzl=0;
    nzhc=nzmc=nzlc=0;
    for (z=0; z<wNZ; z++) {
      i = i2d+z*wN2D;
     
      if (wPRESS[i] > 800.) {
	nzl++;
	if (wCLOUD[i] > 0.) nzlc++;
      } else if (wPRESS[i] > 450.) {
	nzm++;
	if (wCLOUD[i] > 0.) nzmc++;
      } else {
	nzh++;
	if (wCLOUD[i] > 0.) nzhc++;
      }
      
    }
    if (nzl > 0) {
      wCLOUDPCT_L[i2d] = 100.*nzlc/nzl;
    } else {
      wCLOUDPCT_L[i2d] = NC_FILL_FLOAT ;
    }
    if (nzm > 0) {
      wCLOUDPCT_M[i2d] = 100.*nzmc/nzm;
    } else {
      wCLOUDPCT_M[i2d] = NC_FILL_FLOAT ;
    }
    if (nzh > 0) {
      wCLOUDPCT_H[i2d] = 100.*nzhc/nzh;
    } else {
      wCLOUDPCT_H[i2d] = NC_FILL_FLOAT ;
    }
  }

}


void write_CLOUD () {
  fprintf(stdout, "Writing CLOUD\n");
  nc_error(nc_put_var_float(ncout_ID, idCLOUD, wCLOUD));
  nc_error(nc_put_var_float(ncout_ID, idCLOUDPCT_H, wCLOUDPCT_H));
  nc_error(nc_put_var_float(ncout_ID, idCLOUDPCT_M, wCLOUDPCT_M));
  nc_error(nc_put_var_float(ncout_ID, idCLOUDPCT_L, wCLOUDPCT_L));
}

void set_meta_CLOUD () {
  
  ncout_def_var_float("cloud", 3, ncout_3D_DIMS, &idCLOUD);
  
  ncout_def_var_float("cloudpct_h", 2, ncout_2D_DIMS, &idCLOUDPCT_H);
  ncout_def_var_float("cloudpct_m", 2, ncout_2D_DIMS, &idCLOUDPCT_M);
  ncout_def_var_float("cloudpct_l", 2, ncout_2D_DIMS, &idCLOUDPCT_L);

  ncout_set_meta (idCLOUD, "long_name", "cloud");
  ncout_set_meta (idCLOUD, "standard_name", "cloud");
  ncout_set_meta (idCLOUD, "description", "Cloud presence.");
  ncout_set_meta (idCLOUD, "reference", "");
  ncout_set_meta (idCLOUD, "units", "0=no cloud, 1=cloud");
  ncout_set_meta (idCLOUD, "coordinates", "model_level lon lat");
  
  ncout_set_meta (idCLOUDPCT_H, "long_name", "high_clouds_percentage");
  ncout_set_meta (idCLOUDPCT_H, "standard_name", "");
  ncout_set_meta (idCLOUDPCT_H, "description", "Percentage of clouds on vertical grid points above 450hPa level.");
  ncout_set_meta (idCLOUDPCT_H, "reference", "");
  ncout_set_meta (idCLOUDPCT_H, "units", "percent");
  ncout_set_meta (idCLOUDPCT_H, "coordinates", "lon lat");
  
  ncout_set_meta (idCLOUDPCT_M, "long_name", "medium_clouds_percentage");
  ncout_set_meta (idCLOUDPCT_M, "standard_name", "");
  ncout_set_meta (idCLOUDPCT_M, "description", "Percentage of clouds on vertical grid points between 800hPa and 450hPa levels.");
  ncout_set_meta (idCLOUDPCT_M, "reference", "");
  ncout_set_meta (idCLOUDPCT_M, "units", "percent");
  ncout_set_meta (idCLOUDPCT_M, "coordinates", "lon lat");
  
  
  ncout_set_meta (idCLOUDPCT_L, "long_name", "low_clouds_percentage");
  ncout_set_meta (idCLOUDPCT_L, "standard_name", "");
  ncout_set_meta (idCLOUDPCT_L, "description", "Percentage of clouds on vertical grid points below 800hPa level.");
  ncout_set_meta (idCLOUDPCT_L, "reference", "");
  ncout_set_meta (idCLOUDPCT_L, "units", "percent");
  ncout_set_meta (idCLOUDPCT_L, "coordinates", "lon lat");
  
}


void free_CLOUD () {
  
  free (wCLOUD);
  
 
  free (wCLOUDPCT_H);
  free (wCLOUDPCT_M);
  free (wCLOUDPCT_L);
}
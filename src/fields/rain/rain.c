#include "rain.h"

void load_RAIN () {
  fprintf(stdout, "Loading RAIN\n");

  int rain_id;
  int rainc_id;

  nc_error(nc_inq_varid (wrfout_id, "RAINNC", &rain_id));
  nc_error(nc_inq_varid (wrfout_id, "RAINC", &rainc_id));
  
  wRAIN = malloc (wN2D * sizeof(float));
  if (wRAIN==NULL) {fprintf(stderr, "rain.c : Cannot allocate wRAIN\n"); exit(-1);}
  
  wRAINC = malloc (wN2D * sizeof(float));
  if (wRAINC==NULL) {fprintf(stderr, "rain.c : Cannot allocate wRAINC\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, rain_id, wRAIN));
  nc_error(nc_get_var_float(wrfout_id, rainc_id, wRAINC));
  
  int i;
  
  if (wFRAME_LAST != NULL) {
    fprintf(stdout, "Getting accumulated rain values from previous file\n");
    
    int rain_last_id;
    int rainc_last_id;

    nc_error(nc_inq_varid (wrfout_last_id, "RAINNC", &rain_last_id));
    nc_error(nc_inq_varid (wrfout_last_id, "RAINC", &rainc_last_id));
    
    wRAIN_LAST = malloc (wN2D * sizeof(float));
    if (wRAIN_LAST==NULL) {fprintf(stderr, "rain.c : Cannot allocate wRAIN_LAST\n"); exit(-1);}
    
    wRAINC_LAST = malloc (wN2D * sizeof(float));
    if (wRAINC_LAST==NULL) {fprintf(stderr, "rain.c : Cannot allocate wRAINC_LAST\n"); exit(-1);}
    
    nc_error(nc_get_var_float(wrfout_last_id, rain_last_id, wRAIN_LAST));
    nc_error(nc_get_var_float(wrfout_last_id, rainc_last_id, wRAINC_LAST));
    
    #pragma omp parallel for private(i)
    for (i=0; i<wN2D; i++) {
      wRAIN[i] -= wRAIN_LAST[i];
      wRAINC[i] -= wRAINC_LAST[i];
    }
    
    free(wRAIN_LAST);
    free(wRAINC_LAST);
    
  } else {
    fprintf(stderr, "rain.c : WARNING : no previous rain. Using raw values.\n");
  }
  for (i=0; i<wN2D; i++) {
    wRAIN[i] += wRAINC[i];
  }

}


void write_RAIN () {
  fprintf(stdout, "Writing RAIN\n");
  nc_error(nc_put_var_float(ncout_ID, idRAIN, wRAIN));
  nc_error(nc_put_var_float(ncout_ID, idRAINC, wRAINC));
}

void set_meta_RAIN () {
  
  ncout_def_var_float("rain", 2, ncout_2D_DIMS, &idRAIN);
  ncout_def_var_float("rainc", 2, ncout_2D_DIMS, &idRAINC);

  ncout_set_meta (idRAIN, "long_name", "rainfall_over_last_hour");
  ncout_set_meta (idRAIN, "standard_name", "");
  ncout_set_meta (idRAIN, "description", "Total rainfall accumulated over last hour. Convective rainfall is included.");
  ncout_set_meta (idRAIN, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/rain/rain.c");
  ncout_set_meta (idRAIN, "units", "mm h-1");
  ncout_set_meta (idRAIN, "coordinates", "lon lat");
  
  ncout_set_meta (idRAINC, "long_name", "convective_rainfall_over_last_hour");
  ncout_set_meta (idRAINC, "standard_name", "");
  ncout_set_meta (idRAINC, "description", "Rainfall from convective clouds accumulated over last hour");
  ncout_set_meta (idRAINC, "reference", "https://github.com/OpenMeteoData/WRF-postprocessing/blob/master/src/fields/rain/rain.c");
  ncout_set_meta (idRAINC, "units", "mm h-1");
  ncout_set_meta (idRAINC, "coordinates", "lon lat");
  
}


void free_RAIN () {
 
  free (wRAIN);
  free (wRAINC);
  
}
#include "interpolation.h"

void write_ip_levels () {
  nc_error(nc_put_var_float(ncout_ID, idALEVELS, ip_ALEVELS));
  nc_error(nc_put_var_float(ncout_ID, idPLEVELS, ip_PLEVELS));
}

void set_meta_ip_levels () {
 
  ncout_def_var_float("alti_level", 1, ncout_1DA_DIM, &idALEVELS);
  ncout_def_var_float("press_level", 1, ncout_1DP_DIM, &idPLEVELS);

  ncout_set_meta (idALEVELS, "long_name", "altitude_levels");
  ncout_set_meta (idALEVELS, "standard_name", "");
  ncout_set_meta (idALEVELS, "description", "Interpolated altitude levels above mean sea level.");
  ncout_set_meta (idALEVELS, "units", "m");
  ncout_set_meta (idALEVELS, "reference", "http://doc.omd.li/wrfpp/alti_level");
  ncout_set_meta (idALEVELS, "_CoordinateAxisType", "Height");
  ncout_set_meta (idALEVELS, "coordinates", "alti_level");
  
  ncout_set_meta (idPLEVELS, "long_name", "pressure_levels");
  ncout_set_meta (idPLEVELS, "standard_name", "");
  ncout_set_meta (idPLEVELS, "description", "Interpolated pressure levels.");
  ncout_set_meta (idPLEVELS, "units", "hPa");
  ncout_set_meta (idPLEVELS, "reference", "http://doc.omd.li/wrfpp/press_level");
  ncout_set_meta (idPLEVELS, "_CoordinateAxisType", "Pressure");
  ncout_set_meta (idPLEVELS, "coordinates", "press_level");
}


void interpolate_3d_z (float *data3d, float ip_level, float *levels, float *data2d) {
  _interpolate_3d_z (data3d, ip_level, levels, data2d, IP_NOSTAGGER);
}

void interpolate_3d_zstag (float *data3d, float ip_level, float *levels, float *data2d) {
  _interpolate_3d_z (data3d, ip_level, levels, data2d, IP_STAGGER);
}


void _interpolate_3d_z (float *data3d, float ip_level, float *levels, float *data2d, int is_stagger) {
  
  int interp;
  int kp;
  
  int wN2D = wNX*wNY;

  int ip=0;
  int im=1;
  
  // does vertical coordinate increase or decrease with increasing k?
  //set offset appropriately
  if (levels[0] > levels[wN2D])  { //(x+y*wNX+z*wNX*wNY)
    ip=1;
    im=0;
  }
  
  int i;
  for (i=0; i<wN2D; i++) {

    // initialise to MISSING
    data2d[i] = NC_FILL_FLOAT; 
    interp = 0;
    if (is_stagger) { 
      kp = wNZS;
    } else {
      kp = wNZ;      
    }
    
    while ( !interp && (kp >= 2) ) {
      size_t ixm = i+wN2D*(kp-im);
      size_t ixp = i+wN2D*(kp-ip);
      if ( (levels[ixm] <= ip_level) && (levels[ixp] > ip_level) ) {
	double w = (ip_level-levels[ixm]) / (levels[ixp]-levels[ixm]);
	data2d[i] = (1.-w)*data3d[ixm] + w*data3d[ixp];
	interp = 1;
      }
      kp--;
    }
  } 
}
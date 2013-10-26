#include "wind10m.h"

void load_WIND10M () {
  fprintf(stdout, "Loading WIND10M\n");

  int wind10m_u_id;
  int wind10m_v_id;

  float *wind10m_u_raw;
  float *wind10m_v_raw;
  
  nc_error(nc_inq_varid (wrfout_id, "U10", &wind10m_u_id));
  nc_error(nc_inq_varid (wrfout_id, "V10", &wind10m_v_id));
  
  wind10m_u_raw = malloc (wN2D * sizeof(float));
  if (wind10m_u_raw==NULL) {fprintf(stderr, "wind10m.c : Cannot allocate wind10m_u_raw\n"); exit(-1);}
  wind10m_v_raw = malloc (wN2D * sizeof(float));
  if (wind10m_v_raw==NULL) {fprintf(stderr, "wind10m.c : Cannot allocate wind10m_v_raw\n"); exit(-1);}
  
  wWIND10M_U = malloc (wN2D * sizeof(float));
  if (wWIND10M_U==NULL) {fprintf(stderr, "wind10m.c : Cannot allocate wWIND10M_U\n"); exit(-1);}
  wWIND10M_V = malloc (wN2D * sizeof(float));
  if (wWIND10M_V==NULL) {fprintf(stderr, "wind10m.c : Cannot allocate wWIND10M_V\n"); exit(-1);}

  nc_error(nc_get_var_float(wrfout_id, wind10m_u_id, wind10m_u_raw));
  nc_error(nc_get_var_float(wrfout_id, wind10m_v_id, wind10m_v_raw));
  
  if (uvmet_need_rotate()) {
    uvmet_calc (wind10m_u_raw, wind10m_v_raw, wWIND10M_U, wWIND10M_V, 2);
    //TODO: check results
  } else {
    wWIND10M_U = wind10m_u_raw;
    wWIND10M_V = wind10m_v_raw;
    //TODO: make sure we are passing arrays values
  }
  
  
  free (wind10m_u_raw);
  free (wind10m_v_raw);

}


void write_WIND10M () {
  fprintf(stdout, "Writing WIND10M\n");
  nc_error(nc_put_var_float(ncout_ID, idWIND10M_U, wWIND10M_U));
  nc_error(nc_put_var_float(ncout_ID, idWIND10M_V, wWIND10M_V));
}

void set_meta_WIND10M () {
  
  ncout_def_var_float("wind10m_u", 2, ncout_2D_DIMS, &idWIND10M_U);
  ncout_def_var_float("wind10m_v", 2, ncout_2D_DIMS, &idWIND10M_V);

  ncout_set_meta (idWIND10M_U, "long_name", "wind10m_u_vector");
  ncout_set_meta (idWIND10M_U, "standard_name", "");
  ncout_set_meta (idWIND10M_U, "description", "Wind vector on X axis. 10 meters above ground level.");
  ncout_set_meta (idWIND10M_U, "reference", "http://doc.omd.li/wrfpp/wind10m_u");
  ncout_set_meta (idWIND10M_U, "units", "m s-1");
  ncout_set_meta (idWIND10M_U, "coordinates", "lon lat");
  
  ncout_set_meta (idWIND10M_V, "long_name", "wind10m_v_vector");
  ncout_set_meta (idWIND10M_V, "standard_name", "");
  ncout_set_meta (idWIND10M_V, "description", "Wind vector on Y axis. 10 meters above ground level.");
  ncout_set_meta (idWIND10M_V, "reference", "http://doc.omd.li/wrfpp/wind10m_v");
  ncout_set_meta (idWIND10M_V, "units", "m s-1");
  ncout_set_meta (idWIND10M_V, "coordinates", "lon lat");
  
}


void free_WIND10M () {
 
  free (wWIND10M_U);
  free (wWIND10M_V);
  
}
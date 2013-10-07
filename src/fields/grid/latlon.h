#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wLAT;
float *wLON;

void load_LATLON ();
void free_LATLON ();
void write_LATLON ();
void set_LATLON_meta (int nc_id, int *dim_ids, int *lat_idp, int *lon_idp);
void set_LATLON_data (int nc_id, int lat_id, int lon_id);
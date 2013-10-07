#include <netcdf.h>
#include <string.h>
#include <sys/stat.h>
#include "wrfout.h"
#include "nc_error.h"

#define DIM_X 1
#define DIM_Y 2
#define DIM_Z 4

void ncout_init (const char* cat, const char* fname, int dims, int *nc_idp, int *dim_idsp);

void ncout_set_global_meta (int nc_id);

void ncout_close (int nc_id);
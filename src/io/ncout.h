#include <netcdf.h>
#include <string.h>
#include <sys/stat.h>
#include "wrfout.h"
#include "nc_error.h"

#define DIM_X 1
#define DIM_Y 2
#define DIM_Z 4

int ncout_ID;
int ncout_DIM_X;
int ncout_DIM_Y;
int ncout_DIM_Z;

void ncout_open ();

void ncout_set_meta (int var_id, const char *name, const char * text);

void ncout_def_var_float (char * name, int ndims, int *dim_ids, int *var_id);

void ncout_close ();
void ncout_enddef();
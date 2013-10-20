#ifndef	_NCOUT_H
#define	_NCOUT_H

#include <netcdf.h>
#include <string.h>
#include <sys/stat.h>
#include "wrfout.h"
#include "nc_error.h"
#include "../func/interpolation.h"
#include "../../gitversion.h"


#define DIM_X 1
#define DIM_Y 2
#define DIM_Z 4
#define DIM_MLEVEL 8
#define DIM_PLEVEL 16


int ncout_ID;
int ncout_DIM_X;
int ncout_DIM_Y;
int ncout_DIM_Z;
int ncout_DIM_ALEVEL;
int ncout_DIM_PLEVEL;


int ncout_2D_DIMS[2];
int ncout_3D_DIMS[3];
int ncout_3DP_DIMS[3];
int ncout_3DA_DIMS[3];
int ncout_1DZ_DIM[1];
int ncout_1DP_DIM[1];
int ncout_1DA_DIM[1];

void ncout_open ();

void ncout_set_meta (int var_id, const char *name, const char * text);

void ncout_def_var_float (char * name, int ndims, int *dim_ids, int *var_id);

void ncout_close ();
void ncout_enddef();

#endif
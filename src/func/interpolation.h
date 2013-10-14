#include "../io/wrfout.h"

#ifndef	_INTERPOLATION_H
#define	_INTERPOLATION_H

static const float ip_PLEVELS[] = {1024, 1000, 900, 800, 700, 600, 500, 400, 300, 200, 100};
static const float ip_MLEVELS[] = {0, 250, 500, 750, 1000, 1250, 1500, 1750, 2000};

static const int ip_nPLEVELS = 11;
static const int ip_nMLEVELS = 9;

void interpolate_3d_z (float *data3d, float ip_level, float *levels, float *data2d);

#endif
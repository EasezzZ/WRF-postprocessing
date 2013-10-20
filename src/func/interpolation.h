#ifndef	_INTERPOLATION_H
#define	_INTERPOLATION_H

#include "../io/wrfout.h"
#include "../io/ncout.h"


static const float ip_PLEVELS[] = {1000, 975, 950, 925, 900, 875, 850, 825, 800,
                                   775, 750, 725, 700, 675, 650, 625, 600, 575,
                                   550, 525, 500, 475, 450, 425, 400, 375, 350,
                                   325, 300, 275, 250, 225, 200, 175, 150, 125};
                                   
static const float ip_ALEVELS[] = {50, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 
                                   1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200,
                                   3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800,
                                   5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500,
                                   9000, 9500, 10000, 10500, 11000};

static const int ip_nPLEVELS = 36;
// TODO: findout why segfault if n=37 and last level = 100 (no fault if last = 120)
static const int ip_nALEVELS = 38;

int idPLEVELS;
int idALEVELS;

void write_ip_levels ();
void set_meta_ip_levels ();

void interpolate_3d_z (float *data3d, float ip_level, float *levels, float *data2d);

#endif
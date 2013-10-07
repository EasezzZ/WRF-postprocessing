#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../io/wrfout.h"
#include "../fields/grid/latlon.h"

void calc_uvmet (float *u, float *v, float *umet, float *vmet, double cone, int is_stag, int is_missing_val);

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../io/wrfout.h"
#include "../fields/grid/latlon.h"

int uvmet_need_rotate();
void uvmet_calc (float *u, float *v, float *umet, float *vmet, int ndims);

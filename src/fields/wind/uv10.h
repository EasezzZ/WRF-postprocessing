#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../../io/wrfout.h"



float *U10;
float *V10;

void load_UV10 ();
void free_UV10 ();
void write_UV10 ();
void write_UV10_pol ();
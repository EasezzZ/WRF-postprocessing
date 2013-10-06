#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io/wrfout.h"



float *XLAT;
float *XLONG;

void load_XLATLONG ();
void free_XLATLONG ();
void write_XLATLONG ();
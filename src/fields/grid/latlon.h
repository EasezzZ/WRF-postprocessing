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
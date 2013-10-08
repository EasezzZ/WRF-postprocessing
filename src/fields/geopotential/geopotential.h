#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wsPH;
float *wsPHB;
float *wGEOPOTENTIAL;

int idGEOPOTENTIAL;

void load_GEOPOTENTIAL ();
void free_GEOPOTENTIAL ();
void write_GEOPOTENTIAL ();
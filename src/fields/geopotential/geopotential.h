#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"

#include "../press/press.h"

float *wsPH;
float *wsPHB;
float *wGEOPOTENTIAL;
float *wGEOPOTENTIAL_P;
float *wHEIGHT;
float *wHEIGHT_STAG;

int idGEOPOTENTIAL;
int idGEOPOTENTIAL_P;
int idHEIGHT;

void load_GEOPOTENTIAL ();
void free_GEOPOTENTIAL ();
void write_GEOPOTENTIAL ();
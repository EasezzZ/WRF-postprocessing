#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"
//#include "../geopotential/geopotential.h"

float *wPP;
float *wPB;
float *wPRESS;
float *wPRESS_M;

int idPRESS;
int idPRESS_M;

void load_PRESS ();
void free_PRESS ();
void write_PRESS ();
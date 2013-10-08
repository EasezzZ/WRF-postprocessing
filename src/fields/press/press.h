#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wPP;
float *wPB;
float *wPRESS;

int idPRESS;

void load_PRESS ();
void free_PRESS ();
void write_PRESS ();
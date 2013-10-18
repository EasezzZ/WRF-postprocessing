#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wMODEL_LEVEL;

int idMODEL_LEVEL;

void load_MODEL_LEVEL ();
void free_MODEL_LEVEL ();
void write_MODEL_LEVEL ();
void set_meta_MODEL_LEVEL ();

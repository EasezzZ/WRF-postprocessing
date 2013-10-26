#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wTEMP2M;
int idTEMP2M;

void load_TEMP2M ();
void free_TEMP2M ();
void write_TEMP2M ();
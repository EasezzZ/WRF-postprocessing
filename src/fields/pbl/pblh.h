#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wPBLH;

int idPBLH;

void load_PBLH ();
void free_PBLH ();
void write_PBLH ();
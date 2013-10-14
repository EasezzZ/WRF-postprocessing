#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"
#include "../grid/topo.h"

float *wPBLH;
float *wPBLTOP;

int idPBLH;

void load_PBLH ();
void free_PBLH ();
void write_PBLH ();
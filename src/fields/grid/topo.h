#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wTOPO;

void load_TOPO ();
void free_TOPO ();
void write_TOPO ();
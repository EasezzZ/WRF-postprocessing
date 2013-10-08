#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wTOPO;

int idTOPO;

void load_TOPO ();
void free_TOPO ();
void write_TOPO ();
void set_meta_TOPO ();

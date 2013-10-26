#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wWIND10M_U;
float *wWIND10M_V;
int idWIND10M_U;
int idWIND10M_V;

void load_WIND10M ();
void free_WIND10M ();
void write_WIND10M ();
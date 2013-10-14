#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wRAIN;
float *wRAINC;
float *wRAIN_LAST;
float *wRAINC_LAST;
int idRAIN;
int idRAINC;

void load_RAIN ();
void free_RAIN ();
void write_RAIN ();
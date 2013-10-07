#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"


float *wTC2;

void load_TC2 ();
void free_TC2 ();
void write_TC2 ();
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"
#include "../press/press.h"

float *wTEMP;
float *wTK;
float *wTHETA;

int idTEMP;

void load_TEMP ();
void free_TEMP ();
void write_TEMP ();
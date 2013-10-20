#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"
#include "../press/press.h"
#include "../geopotential/geopotential.h"

float *wTEMP;
float *wTEMP_A;
float *wTEMP_P;
float *wTK;
float *wTHETA;

int idTEMP;
int idTEMP_A;
int idTEMP_P;

void load_TEMP ();
void free_TEMP ();
void write_TEMP ();
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"

#include "../temp/temp.h"
#include "../press/press.h"
#include "../geopotential/geopotential.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

float *wRH;
float *wRH_A;
float *wRH_P;
float *wQVAPOR;

int idRH;
int idRH_A;
int idRH_P;

void load_RH ();
void free_RH ();
void write_RH ();
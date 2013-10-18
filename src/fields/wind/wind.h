#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"

#include "../../func/calc_uvmet.h"
#include "../press/press.h"
#include "../geopotential/geopotential.h"

float *wWIND_U;
float *wWIND_V;
float *wWIND_U_P;
float *wWIND_V_P;
float *wWIND_U_M;
float *wWIND_V_M;

float *wU_raw;
float *wV_raw;
float *wU_unstag_raw;
float *wV_unstag_raw;

int idWIND_U;
int idWIND_V;
int idWIND_U_P;
int idWIND_V_P;
int idWIND_U_M;
int idWIND_V_M;

void load_WIND ();
void free_WIND ();
void write_WIND ();
void set_meta_WIND ();
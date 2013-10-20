#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../io/wrfout.h"
#include "../../io/ncout.h"
#include "../press/press.h"

float *wCLOUD;
float *wCLOUDPCT_H;
float *wCLOUDPCT_M;
float *wCLOUDPCT_L;

int idCLOUD;
int idCLOUDPCT_H;
int idCLOUDPCT_M;
int idCLOUDPCT_L;

void load_CLOUD ();
void free_CLOUD ();
void write_CLOUD ();
#include <netcdf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wrfout_id;

size_t wNX; // west_east
size_t wNY; // south_north
size_t wNZ; // bottom_top

size_t wN2D;
size_t wN3D;

int wMAP_PROJ;
int wTRUELAT1;
int wTRUELAT2;
int wCEN_LON;

char *wDOMAIN;
char *wRUN;
char *wRUN_START;
char *wFRAME;
char *wFRAME_LAST;

void open_wrfout (int argc, char *argv[]);
void close_wrfout ();
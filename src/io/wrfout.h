#include <netcdf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wrfout_id;

size_t wNX; // west_east
size_t wNY; // south_north
size_t wNZ; // bottom_top
size_t wNXS; // west_east staggered
size_t wNYS; // south_north staggered
size_t wNZS; // bottom_top staggered

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

void wrfout_open (int argc, char *argv[]);
void wrfout_close ();
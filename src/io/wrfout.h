#include <netcdf.h>
#include <stdio.h>
#include <stdlib.h>

int wrfout_id;

size_t nWE; // west_east
size_t nSN; // south_north
size_t nBT; // bottom_top

int MAP_PROJ;
int TRUELAT1;
int TRUELAT2;
int CEN_LON;

void open_wrfout (const char *path);
void close_wrfout ();
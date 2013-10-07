#include "io/wrfout.h"

#include "fields/grid/latlon.h"
#include "fields/grid/topo.h"
//#include "fields/wind/uv10.h"

int main(int argc, char *argv[]) {

  if (argc != 4 && argc != 5) {
    fprintf(stderr, "USAGE : ./wrfpp {DOMAIN} {RUN} {FRAME} [{LASTFRAME}]\n");
  }
  
  open_wrfout(argc, argv);
  
  load_LATLON();
  load_TOPO();
//  load_UV10();
  
  write_LATLON();
  write_TOPO();
//  write_UV10();
//  write_UV10_pol();
  
  free_LATLON();
  free_TOPO();
//  free_UV10();
  
  close_wrfout();
  
}
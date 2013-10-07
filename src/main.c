#include <stdio.h>

int main(int argc, char *argv[]) {

  if (argc != 4 && argc != 5) {
    fprintf(stderr, "USAGE : ./wrfpp {DOMAIN} {RUN} {FRAME} [{LASTFRAME}]\n");
  }
  
  open_wrfout(argc, argv);
  
  load_LATLON();
  load_TOPO();
  load_PBLH();
  load_TC2();
//  load_UV10();
  
  write_LATLON();
  write_TOPO();
  write_PBLH();
  write_TC2();
//  write_UV10();
//  write_UV10_pol();
  
  free_LATLON();
  free_TOPO();
  free_PBLH();
  free_TC2();
//  free_UV10();
  
  close_wrfout();
  
}
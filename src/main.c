#include <stdio.h>

int main(int argc, char *argv[]) {

  if (argc != 4 && argc != 5) {
    fprintf(stderr, "USAGE : ./wrfpp {DOMAIN} {RUN} {FRAME} [{LASTFRAME}]\n");
  }
  
  wrfout_open(argc, argv);
  
  load_LATLON();
  load_TOPO();
  load_PBLH();
  load_TC2();
  load_PRESS();
  load_GEOPOTENTIAL();
//  load_UV10();
  
  
  ncout_open();
  
  
  set_meta_LATLON ();
  set_meta_TOPO ();
  set_meta_PBLH ();
  set_meta_TC2 ();
  set_meta_PRESS ();
  set_meta_GEOPOTENTIAL ();
  
  
  ncout_enddef();
  
  write_LATLON();
  write_TOPO();
  write_PBLH();
  write_TC2();
  write_PRESS();
  write_GEOPOTENTIAL();
//  write_UV10();
//  write_UV10_pol();
  
  
  free_LATLON();
  free_TOPO();
  free_PBLH();
  free_TC2();
  free_PRESS();
  free_GEOPOTENTIAL();
//  free_UV10();
  
  ncout_close();
  wrfout_close();

}
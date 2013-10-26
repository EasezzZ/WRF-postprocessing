#include <stdio.h>

int main(int argc, char *argv[]) {

  if (argc != 4 && argc != 5) {
    fprintf(stderr, "USAGE : ./wrfpp {DOMAIN} {RUN} {FRAME} [{LASTFRAME}]\n");
  }
  
  fprintf(stdout, "== Opening input files ==\n");
  wrfout_open(argc, argv);
  
  fprintf(stdout, "== Loading data ==\n");
  load_LATLON();
  load_MODEL_LEVEL();
  load_TOPO();
  load_PBLH();
  load_TC2();
  load_PRESS();
  load_GEOPOTENTIAL();
  load_TEMP();
  load_RAIN();
  load_RH();
  load_WIND();
  load_WIND10M();
  load_CLOUD();
  
//  load_UV10();
  
  fprintf(stdout, "== Opening output file ==\n");
  ncout_open();
  
  fprintf(stdout, "== Setting metadata ==\n");
  set_meta_LATLON ();
  set_meta_LAMBERT();
  set_meta_MODEL_LEVEL ();
  set_meta_ip_levels();
  set_meta_TOPO ();
  set_meta_PBLH ();
  set_meta_TC2 ();
  set_meta_PRESS ();
  set_meta_GEOPOTENTIAL ();
  set_meta_TEMP ();
  set_meta_RAIN ();
  set_meta_RH ();
  set_meta_WIND ();
  set_meta_WIND10M ();
  set_meta_CLOUD ();
  
  
  ncout_enddef();
  
  fprintf(stdout, "== Writing data ==\n");
  write_LATLON();
  write_MODEL_LEVEL();
  write_ip_levels();
  write_TOPO();
  write_PBLH();
  write_TC2();
  write_PRESS();
  write_GEOPOTENTIAL();
  write_TEMP();
  write_RAIN();
  write_RH();
  write_WIND();
  write_WIND10M();
  write_CLOUD();
  
//  write_UV10();
//  write_UV10_pol();
  
  fprintf(stdout, "== Releasing memory ==\n");
  free_LATLON();
  free_MODEL_LEVEL();
  free_TOPO();
  free_PBLH();
  free_TC2();
  free_PRESS();
  free_GEOPOTENTIAL();
  free_TEMP();
  free_RAIN();
  free_RH();
  free_WIND();
  free_WIND10M();
  free_CLOUD();
//  free_UV10();
  
  fprintf(stdout, "== Closing files ==\n");
  ncout_close();
  wrfout_close();

  fprintf(stdout, "== WRF-PP SUCCESS COMPLETE ==\n");

}
#include "io/wrfout.h"

#include "fields/xlatlong.h"
#include "fields/wind/uv10.h"

int main(int argc, char *argv[]) {
  
  open_wrfout("wrfout-test.nc");
  
  load_XLATLONG();
  load_UV10();
  
  write_XLATLONG();
  
  free_UV10();
  free_XLATLONG();
  
  close_wrfout();
  
}
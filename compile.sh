#!/bin/bash

rm *.o

gcc -c src/main.c || exit
gcc -c src/io/wrfout.c || exit
gcc -c src/io/nc_error.c || exit
gcc -c src/io/ncout.c || exit
gcc -c src/fields/grid/latlon.c || exit
gcc -c src/fields/grid/topo.c || exit
gcc -c src/fields/grid/model_level.c || exit
gcc -c src/fields/pbl/pblh.c || exit
gcc -c src/fields/press/press.c || exit
gcc -c src/fields/geopotential/geopotential.c || exit
gcc -c src/func/interpolation.c || exit
gcc -c src/func/calc_uvmet.c || exit
gcc -c src/fields/temp/temp.c || exit
gcc -c src/fields/temp/tc2.c || exit
gcc -c src/fields/rain/rain.c || exit
gcc -c src/fields/humidity/rh.c || exit
gcc -c src/fields/wind/wind.c || exit


gcc *.o -lnetcdf -o wrfpp  || exit

echo --- run wrfpp --------
./wrfpp test 2013-10-07_12 2013-10-09_06h00 2013-10-09_05h00
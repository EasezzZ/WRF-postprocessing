#!/bin/bash

gcc -c src/main.c || exit
gcc -c src/io/wrfout.c || exit
gcc -c src/io/nc_error.c || exit
gcc -c src/io/ncout.c || exit
gcc -c src/fields/grid/latlon.c || exit
gcc -c src/fields/grid/topo.c || exit
gcc -c src/func/interpolation.c || exit

gcc *.o -lnetcdf -o wrfpp  || exit

echo --- run wrfpp --------
./wrfpp
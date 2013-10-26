#!/bin/bash

OPT="-fopenmp"

if [ "$1" == "prod" ]; then
  OPT="$OPT -O3 -march=native"
fi

rm *.o

echo "static const char *git_commit=\"$(git rev-parse HEAD)\";" > gitversion.h
echo "static const char *git_status=\"$(echo $(git status -s))\";" >> gitversion.h

gcc $OPT -c src/main.c || exit
gcc $OPT -c src/io/wrfout.c || exit
gcc $OPT -c src/io/nc_error.c || exit
gcc $OPT -c src/io/ncout.c || exit
gcc $OPT -c src/fields/grid/latlon.c || exit
gcc $OPT -c src/fields/grid/topo.c || exit
gcc $OPT -c src/fields/grid/model_level.c || exit
gcc $OPT -c src/fields/grid/lambert.c || exit
gcc $OPT -c src/fields/pbl/pblh.c || exit
gcc $OPT -c src/fields/press/press.c || exit
gcc $OPT -c src/fields/geopotential/geopotential.c || exit
gcc $OPT -c src/func/interpolation.c || exit
gcc $OPT -c src/func/calc_uvmet.c || exit
gcc $OPT -c src/fields/temp/temp.c || exit
gcc $OPT -c src/fields/temp/temp2m.c || exit
gcc $OPT -c src/fields/rain/rain.c || exit
gcc $OPT -c src/fields/humidity/rh.c || exit
gcc $OPT -c src/fields/wind/wind.c || exit
gcc $OPT -c src/fields/wind/wind10m.c || exit
gcc $OPT -c src/fields/cloud/cloud.c || exit


gcc *.o -fopenmp -lnetcdf -o wrfpp  || exit
rm *.o

if [ "$1" != "prod" ]; then
  echo --- run wrfpp --------
  
  ./wrfpp eu1 2013100712 2013-10-07_13 1
fi

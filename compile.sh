#!/bin/bash

gcc src/main.c src/io/wrfout.c src/io/nc_error.c src/fields/wind/uv10.c src/fields/wind/calc_uvmet.c src/fields/xlatlong.c -lnetcdf -o wrfpp && ./wrfpp

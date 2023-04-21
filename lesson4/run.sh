#!/bin/bash
make clean
make
mpirun -np 3 ./main
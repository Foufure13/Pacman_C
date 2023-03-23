#!/bin/bash
rm ./V3/build/pacmanV3
mkdir -p ./V3/build
gcc -o ./V3/build/pacmanV3 ./V3/pacmanV3.c -lncurses

./V3/build/pacmanV3

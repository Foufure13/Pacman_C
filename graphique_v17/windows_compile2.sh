#!/bin/bash

x86_64-w64-mingw32-gcc main.c keybinding_action.c map.c affichage.c -o Pacman_Ultimate.exe -Wall -Wextra -g3 -I/usr/include/SDL2 -D_REENTRANT   -L/usr/lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf


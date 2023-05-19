#!/bin/bash

gcc main.c keybinding_action.c map.c affichage.c -o main -Wall -Wextra -g3 -lSDL2 -lSDL2_ttf
./main

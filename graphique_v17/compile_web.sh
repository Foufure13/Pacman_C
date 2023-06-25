#!/bin/bash

emcc main.c keybinding_action.c map.c affichage.c -o pacman.js -Wall -Wextra -g3 -lSDL2 -lSDL2_ttf


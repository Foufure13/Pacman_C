#!/bin/bash

gcc main.c keybinding_action.c map.c -o main -Wall -Wextra -g3 -lSDL2
./main

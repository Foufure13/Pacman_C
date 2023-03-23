# #!/bin/bash
# gcc -o /home/foufure/github/Pacman_C/V2/build/pacmanV2 /home/foufure/github/Pacman_C/V2/pacmanV2.c -lncurses
# /home/foufure/github/Pacman_C/V2/build/pacmanV2

#!/bin/bash
mkdir -p ./build
gcc -o ./build/pacmanV2 ./pacmanV2.c -lncurses

./build/pacmanV2

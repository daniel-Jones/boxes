# boxes
C application using ncurses. Mainly a test, allows x number of squares (configurable), each square has their own x, y, speed, direction, width and height, again, all configurable.

speed, direction, color (R, G, B) are random.

compile with:
gcc main.c -o boxes -lncurses

change "#define TS 15" to modify the number of boxes.

example: https://asciinema.org/a/hzHc0HGezxkgnqgOkMwrlFqQd

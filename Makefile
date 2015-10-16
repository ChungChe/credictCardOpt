CFLAGS = -Wall -O2


all:
	g++ $(CFLAGS) main.cpp -D_GPLUSPLUS_

emcripten:
	em++ --bind -o output.js *.cpp

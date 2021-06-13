CC = g++
CFLAGS = -Wall -g

ludo-game: _main.o -lsfml-graphics -lsfml-window -lsfml-system
	$(CC) $(CFLAGS) -o ludo-game _main.o -lsfml-graphics -lsfml-window -lsfml-system

_main.o: _main.cpp
	$(CC) $(CFLAGS) -c _main.cpp
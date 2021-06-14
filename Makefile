CC = g++
CFLAGS = -Wall -g

ludo-game: _main.o App.o -lsfml-graphics -lsfml-window -lsfml-system
	$(CC) $(CFLAGS) -o ludo-game _main.o App.o -lsfml-graphics -lsfml-window -lsfml-system

_main.o: _main.cpp App.cpp
	$(CC) $(CFLAGS) -c _main.cpp App.cpp

App.o: App.cpp
	$(CC) $(CFLAGS) -c App.cpp
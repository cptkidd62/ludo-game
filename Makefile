CC = g++
CFLAGS = -Wall -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SRCS = _main.cpp App.cpp Match.cpp Player.cpp HumanPlayer.cpp
OBJS = $(SRCS:.c=.o)
MAIN = ludo-game.exe

all: $(MAIN)

$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:	$(CC) $(CFLAGS) -c $<  -o $@

clean:	$(RM) *.o *~ $(MAIN)

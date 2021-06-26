CC = g++
CFLAGS = -Wall -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SRCS = _main.cpp App.cpp Match.cpp Player.cpp HumanPlayer.cpp NormalAI.cpp SimpleAI.cpp UsersList.cpp UserData.cpp Stats.cpp StatsView.cpp
OBJS = $(SRCS:.c=.o)
MAIN = ludo-game

all: $(MAIN)

$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:	$(CC) $(CFLAGS) -c $<  -o $@

clean:	$(RM) *.o *~ $(MAIN)

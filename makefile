#Makefile for "MathChallange" C++ application
#Created by Ulf Hillbom

BINDIR = bin
OBJSDIR = obj
SRCDIR = src
PROG = MatchChallange
PROGDIR = $(BINDIR)/$(PROG)

CC = g++
CPPFLAGS = -Wall -I./include
OBJS = $(OBJSDIR)/main.o $(OBJSDIR)/player.o $(OBJSDIR)/gamedesign.o $(OBJSDIR)/game.o $(OBJSDIR)/gamefunctions.o

$(PROG) : $(OBJS)
	@echo "Linking."
	$(CC) -o $(PROGDIR) $(OBJS)
$(OBJSDIR)/main.o : ./src/main.cpp
	@echo "Compiling main.cpp"
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/main.cpp -o $(OBJSDIR)/main.o
$(OBJSDIR)/player.o : ./include/player.h ./src/player.cpp
	@echo "Compiling player.cpp"
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/player.cpp -o $(OBJSDIR)/player.o
$(OBJSDIR)/gamedesign.o : ./include/gamedesign.h ./src/gamedesign.cpp
	@echo "Compiling gamedesign.cpp"
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/gamedesign.cpp -o $(OBJSDIR)/gamedesign.o
$(OBJSDIR)/game.o : ./include/game.h ./src/game.cpp
	@echo "Compiling game.cpp"
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/game.cpp -o $(OBJSDIR)/game.o
$(OBJSDIR)/gamefunctions.o : ./include/gamefunctions.h ./src/gamefunctions.cpp
	@echo "Compiling gamefunctions.cpp"
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/gamefunctions.cpp -o $(OBJSDIR)/gamefunctions.o

clean:
	rm -f core $(BINDIR)/$(PROG) $(OBJS)
#Makefile for "TovasMathChallange" C++ application
#Created by Ulf Hillbom

BINDIR = bin
OBJSDIR = obj
SRCDIR = src
PROG = TovasMathChallange
PROGDIR = $(BINDIR)/$(PROG)

CC = g++
CPPFLAGS = -Wall -I./include
OBJS = $(OBJSDIR)/main.o $(OBJSDIR)/player.o

$(PROG) : $(OBJS)
	@echo "Linking."
	$(CC) -o $(PROGDIR) $(OBJS)
$(OBJSDIR)/main.o : ./src/main.cpp
	@echo "Compiling main.cpp"
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/main.cpp -o $(OBJSDIR)/main.o
$(OBJSDIR)/player.o : ./include/player.h ./src/player.cpp
	@echo "Compiling player.cpp"
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/player.cpp -o $(OBJSDIR)/player.o

clean:
	rm -f core $(BINDIR)/$(PROG) $(OBJS)
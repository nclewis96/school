# Makefile for maze program
C++  = c++
CFLAGS = -g -Wall -Werror
LD = c++
LDFLAGS = 
LIBS = 
OBJS = driver.o maze.o creature.o
EXEC = maze

$(EXEC):	$(OBJS)
		$(LD) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

maze.o:	        maze.h maze.cpp
		$(C++) $(CFLAGS) -c maze.cpp

creature.o:	creature.h creature.cpp 
		$(C++) $(CFLAGS) -c creature.cpp

driver.o:	driver.cpp 
		$(C++) $(CFLAGS) -c driver.cpp

clean:
		rm $(OBJS) $(EXEC)

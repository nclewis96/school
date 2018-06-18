#
# Makefile for Generating C++ executables
#
# S16 CSCI 332 - Design and Analysis of Algorithms
# Phillip J. Curtiss, Associate Professor
# Computer Science Department, Montana Tech
# Museum Buildings, Room 105
#
# Project-1: Weighted Directed Graph
# Date Assigned: 2016-01-22
# Date Due: 2016-02-05 by Midnight

# Define Macros related to printing and submitting project
a2ps	= a2ps -T 2
mail	= mail
addr	= pcurtiss@mtech.edu #rmoon@mtech.edu
tar		= tar -cvzf

# Define Macros related to object code and program generation
DIA = dia2code
C++  = g++ -std=c++11
CFLAGS = -g -Wall -Werror
LD = g++
LDFLAGS =
LIBS =
SRCS = Driver.cpp WDiGraph.cpp WDiGraph.h \
	   VertexOutOfRangeException.h NotFoundException.cpp NotFoundException.h \
	   Graph.h GraphInterface.h \
	   io_functions.cpp io_functions.h
OBJS = Driver.o WDiGraph.o io_functions.o
EXEC = Driver

# Provide Make with additionally known suffixes
.SUFFIXES:	.dia

# Default rule to make if now target specified on command line
all:		$(EXEC)

# Dependency Rules
io_functions.o:	io_functions.h io_functions.cpp
WDiGraph.o:	VertexOutOfRangeException.h WDiGraph.h WDiGraph.cpp
Driver.o:	Driver.cpp WDiGraph.h

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
# Target Rules for Make
$(EXEC):	$(OBJS)
		$(LD) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

clean:
		rm -f $(OBJS) $(EXEC) 
		
subj = 	"CSCI332 DAA - Proj1"
msg = 	"Please review and grade my Project-1 Submission"
submit:	$(SRCS)
	$(tar) $(USER)-proj1.tgz $?
	echo $(msg) | $(mail) -s $(subj) -a $(USER)-proj1.tgz $(addr)
	
print:	$(SRCS)
	$(a2ps) $?

# Implcit Rules based on file extension dependencies
.cpp.o:
	$(C++) $(CFLAGS) -c $<
	
.dia.h: 
	$(DIA) -t cpp $<
	
.dia.cpp:
	$(DIA) -t cpp $<


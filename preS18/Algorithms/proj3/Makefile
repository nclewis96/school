#
# Makefile for Generating C++ executables
#
# S16 CSCI 332 - Design and Analysis of Algorithms
# Phillip J. Curtiss, Associate Professor
# Computer Science Department, Montana Tech
# Museum Buildings, Room 105
#
# Project-2: Numerical Integration
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
CFLAGS = -g -Wall -Werror -fopenmp 
LD = g++
LDFLAGS = -fopenmp
LIBS =
SRCS = Point.cpp Point.h PointSet.cpp PointSet.h Driver.cpp ExCredit.txt
OBJS = Driver.o Point.o PointSet.o
EXEC = hull

# Provide Make with additionally known suffixes
.SUFFIXES:	.dia

# Default rule to make if now target specified on command line
all:		$(EXEC)


#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
# Target Rules for Make
$(EXEC):	$(OBJS)
		$(LD) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

Point.o: Point.cpp Point.h
	$(C++) $(CFLAGS) -c Point.cpp

PointSet.o: PointSet.cpp PointSet.h
	$(C++) $(CFLAGS) -c PointSet.cpp
	
Driver.o: Driver.cpp
	$(C++) $(CFLAGS) -c Driver.cpp
	
clean:
		rm -f $(OBJS) $(EXEC) 
		
subj = 	"CSCI332 DAA - Proj3"
msg = 	"Sorry for the Spam, was editing the wrong Makefile...."
submit:	*.cpp *.txt
	$(tar) $(USER)-proj3.tgz $?
	echo $(msg) | $(mail) -s $(subj) -a $(USER)-proj3.tgz $(addr)
	
print:	$(SRCS)
	$(a2ps) $?

# Implcit Rules based on file extension dependencies
.cpp.o:
	$(C++) $(CFLAGS) -c $<
	
.dia.h: 
	$(DIA) -t cpp $<
	
.dia.cpp:
	$(DIA) -t cpp $<


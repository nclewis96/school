#
# Makefile for Generating C++ executables
#
# S16 CSCI 446 - AI
# Michele Van Dyne,  Professor
# Computer Science Department, Montana Tech
# Museum Buildings
#
# Project-2: Search
# Date Assigned: 2017-08-07
# Date Due: 2017-08-21 by Midnight

# Define Macros related to printing and submitting project
a2ps	= a2ps -T 2
mail	= mail
addr	= mvandyne@mtech.edu 
tar		= tar -cvzf

# Define Macros related to object code and program generation
DIA = dia2code
C++  = g++ -std=c++11
CFLAGS = -g -Wall -Werror -fopenmp 
LD = g++
LDFLAGS = -fopenmp
LIBS = 
SRCS = AStar.cpp DepthFirst.cpp GenericSearch.cpp Town.cpp driver.cpp
OBJS = AStar.o DepthFirst.o GenericSearch.o Town.o driver.o
EXEC = pathSearch

# Provide Make with additionally known suffixes
.SUFFIXES:	.dia

# Default rule to make if now target specified on command line
all:		$(EXEC)


#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
# Target Rules for Make
$(EXEC):	$(OBJS)
		$(LD) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

#$(EXEC): Roads.txt SLD.txt
	#$(EXEC) $@

AStar.o: AStar.cpp
	$(C++) $(CFLAGS) -c AStar.cpp
	
DepthFirst.o: DepthFirst.cpp
	$(C++) $(CFLAGS) -c DepthFirst.cpp
	
GenericSearch.o: GenericSearch.cpp
	$(C++) $(CFLAGS) -c GenericSearch.cpp
	
Town.o: Town.cpp
	$(C++) $(CFLAGS) -c Town.cpp
	
driver.o: driver.cpp
	$(C++) $(CFLAGS) -c driver.cpp
	
clean:
		rm -f $(OBJS) $(EXEC) 
		
subj = 	"CSCI446 Pathfinder"
msg = 	" To compile, use command make, then ./pathSearch I apologize for not sending this earlier"
submit:	*.cpp *.txt *.h Makefile
	$(tar) $(USER)-proj2.tgz $?
	echo $(msg) | $(mail) -s $(subj) -a $(USER)-proj2.tgz $(addr)
	
print:	$(SRCS)
	$(a2ps) $?

# Implcit Rules based on file extension dependencies
.cpp.o:
	$(C++) $(CFLAGS) -c $<
	
.dia.h: 
	$(DIA) -t cpp $<
	
.dia.cpp:
	$(DIA) -t cpp $<


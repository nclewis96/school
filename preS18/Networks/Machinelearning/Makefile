#
# Makefile for Generating C++ executables
#
# S16 CSCI 446 - AI
# Michele Van Dyne,  Professor
# Computer Science Department, Montana Tech
# Museum Buildings
#
# Project-5: Machine Learning
# Date Assigned: 2017-08-07
# Date Due: 2017-11-06 by Midnight

# Define Macros related to printing and submitting project
a2ps	= a2ps -T 2
mail	= mail
addr	= mvandyne@mtech.edu
tar		= tar -cvzf

# Define Macros related to object code and program generation
DIA = dia2code
C++  = g++ -std=c++11
CFLAGS = -g -Wall -Werror 
LD = g++
LDFLAGS = 
LIBS =
SRCS = dataPoint.cpp Centroid.cpp Cluster.cpp NomCluster.cpp NumCluster.cpp driver.cpp
OBJS = dataPoint.o Centroid.o Cluster.o NomCluster.o NumCluster.o driver.o
EXEC = machine

# Provide Make with additionally known suffixes
.SUFFIXES:	.dia

# Default rule to make if now target specified on command line
all:		$(EXEC)
dataPoint.o: dataPoint.cpp  dataPoint.h Centroid.o
Centroid.o: Centroid.cpp Centroid.h
Cluster.o: Cluster.cpp Cluster.h
NomCluster.o: NomCluster.cpp NomCluster.h Cluster.o
NumCluster.o: NumCluster.cpp NumCluster.h Cluster.o
driver.o: driver.cpp dataPoint.o Centroid.o Cluster.o NomCluster.o NumCluster.o

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
# Target Rules for Make
$(EXEC):	$(OBJS)
		$(LD) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

clean:
		rm -f $(OBJS) $(EXEC)

subj = 	"CSCI446 Machine Learning - unfinshisedv4"
msg = 	"Compiles. To do so, in containing folder use cmd <make> then <./machine> Seg faults though :( Really sorry this is so late."
submit:	*.cpp *.txt *.h Makefile
	$(tar) $(USER)-proj5.tgz $?
	echo $(msg) | $(mail) -s $(subj) -a $(USER)-proj5.tgz $(addr)

print:	$(SRCS)
	$(a2ps) $?

# Implcit Rules based on file extension dependencies
.cpp.o:
	$(C++) $(CFLAGS) -c $<

.dia.h:
	$(DIA) -t cpp $<

.dia.cpp:
	$(DIA) -t cpp $<

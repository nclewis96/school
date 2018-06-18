#
# Makefile for Generating C++ executables for Lab
# Sessions and Projects in CSC232 F15
#
# Phil Curtiss, CS Dept - 2015-08-26

# Define Macros related to printing and submitting programs
a2ps	= a2ps -T 2
mail	= mail 
addr	= pcurtiss@mtech.edu rmoon@mtech.edu

# Define Macros to help generate the program file required
C++	= g++ -std=c++11
CFLAGS	= -Wall -Werror
LD	= g++
LDFLAGS	= 
LIBS	= 
OBJS	= listing-A1.o listing-A2.o
EXEC	= listing-A2

# Rule to Generate the Executable we wish from the source files
all:		$(EXEC)

# Rules Used to Generate Object Code and Executable from 
# Linking Object Code with Libraries
$(EXEC):	$(OBJS)
		$(LD) $(LDFLAGS) -o $@ $? $(LIBS)

# Template for Object File Generation
# foo.o:	foo.h foo.cpp
#		$(C++) $(CFLAGS) -c $?
listing-A1.o:	listing-A1.cpp
		$(C++) $(CFLAGS) -c $?

listing-A2.o:	listing-A2.cpp
		$(C++) $(CFLAGS) -c $?

# Rule to Clean up (i.e. delete) all of the object and execuable
# code files to force make to rebuild a clearn executable only 
# from the source files
clean:
		rm -f $(OBJS) $(EXEC)

# Rule to submit programming assignments to graders
# Make sure you modify the $(subj) $(msg) above and the list of attachment
# files in the following rule - each file needs to be preceeded with an
# -a flag as shown
subj	= "Lab Listing A1"
msg	= "Please review"
submit:		listing-A1.cpp listing-A2.cpp
		echo $(msg) | $(mail) -s $(subj) $(addprefix -a , $?) $(addr)

print:		listing-A1.cpp listing-A2.cpp
		$(a2ps) $?



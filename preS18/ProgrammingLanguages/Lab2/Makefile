# Makefile for Generating lex and yacc executables
#
# F16 CSCI 305 - Concepts of Programming Languages
# Nathaniel Lewis
#
# Project-2: Context Free Grammars, Syntactic Analysis and YACC
# Date Assigned: September 2, 2016
# Date Due: September 9, 2016 @midnight

# Define Macros related to submitting programs
mail = mail 
addr = pcurtiss@mtech.edu
tar = tar -cvzf

# Define Macros to help generate the program file required
YFLAGS = -d
EXEC = calc
EXEC2 = therm
SRCS = lex.yy.c y.tab.c
LEX = lex
YACC = bison -y
CC = cc 

################################################################
# Provide dependency lists here, one on each line
all: $(EXEC)
	y.tab.c: calc.y
	$(YACC) $(YFLAGS) calc.y
	lex.yy.c: calc.l
	$(LEX) calc.lex

################################################################
# Rules Used to Generate executable from object
$(EXEC): $(SRCS)
	$(CC) $(SRCS)  -o $@ 
################################################################
# Provide dependency lists here, one on each line
clean:; rm -f $(SRCS) $(EXEC) y.* lex.yy.* y.tab.*

################################################################
# Rule to submit programming assignments 
subj = "CSCI305 Concepts of Programming Languages - Lab2"
msg = "Please review and grade my lab2 Submission"
submit: therm.l thermostat.y Makefile
	$(tar) $(USER)-proj2.tgz $?
	echo $(msg) | $(mail) -s $(subj) -a $(USER)-proj2.tgz $(addr)
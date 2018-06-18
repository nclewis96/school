
ASSN = 1
CLASS= CSCI305
CLASSDIR= /opt/cool/F16CSCI305
SRC= stack.cl README 
LSRC= Makefile atoi.cl stack.test

CC=gcc
CFLAGS=-g

.c.o:
	${CC} ${CFLAGS} -c $<

source :	lsource
	${CLASSDIR}/etc/copy-skel ${ASSN} ${SRC}

lsource:
	${CLASSDIR}/etc/link-shared ${ASSN} ${LSRC}

compile: stack.s

stack.s: stack.cl atoi.cl
	${CLASSDIR}/bin/coolc stack.cl atoi.cl 

test:	compile
	@echo stack.test
	${CLASSDIR}/bin/spim -file stack.s < stack.test

clean :
	rm -f *.s core *~

subj = "F16 CSCI 305 Proj-1"
msg = "Please review and grade Proj-1"
proj = $(USER)-proj1.tgz
subfiles = README stack.cl
#
include /opt/cool/F16CSCI305/assignments/Makefile.submit


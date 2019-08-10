# CFLAGS = -c -Wall
# CC = gcc
# LIBS = -lm

# all: run

# run: main.o dllist.o fields.o jrb.o jval.o
# 	${CC} main.o dllist.o fields.o jrb.o jval.o -o run

# main.o: main.c
# 	${CC} ${CFLAGS} main.c

# dllist.o: dllist.c
# 	${CC} ${CFLAGS} dllist.c

# fields.o: fields.c
# 	${CC} ${CFLAGS} fields.c

# jrb.o: jrb.c
# 	${CC} ${CFLAGS} jrb.c

# jval.o: jval.c
# 	${CC} ${CFLAGS} jval.c

# clean:
# 	rm -f *.o *~


# # all: run

# # run: dllist.o fields.o jrb.o jval.o main.o
# # 	gcc dllist.o fields.o jrb.o jval.o main.o -o run

# # dllist.o: dllist.c
# # 	gcc -c dllist.c

# # fields.o: fields.c
# # 	gcc -c fields.c

# # jrb.o: jrb.c
# # 	gcc -c jrb.c

# # jval.o: jval.c
# # 	gcc -c jval.c

# # main.o:	main.c
# # 	gcc -c main.c

# # clean: 
# # 	rm -f *.o *~

ARCH_MACH = $(shell uname -m)
OS_TYPE   = $(shell uname -s)

############### name of target
#
TARGET		= ./chay

########################################################################
##########        Linux Cluster Environment                   ##########
########################################################################

CPPFLAGS := $(CPPFLAGS) -D__LINUX__ -DEBUG

############### C++ compiler commands
#
CCC		= /usr/bin/g++ 
CC		= /usr/bin/gcc

############### Other Packages
#

############### libraries needed to generate program
#
LDLIBS		:=  -lm

############### objects needed to generate target
#
OBJS = 	main.o jval.o jrb.o fields.o dllist.o\


PURIFY	= purify $(PFLAGS)

CCFLAGS		=  $(CPPFLAGS)
COMPILE.cc	=  $(CCC) $(CCFLAGS) $(CPPFLAGS)  -c -w
LINK.cc		=  $(CCC) $(CCFLAGS) $(CPPFLAGS)  $(LDFLAGS)



############### options for preprocessor (include directories)
#
CPPFLAGS	:=\
		$(CPPFLAGS)  			\
		-Wall 				\
		-I.


############### options for compiler
#

CCFLAGS:= -g -Wall -O3 

CXXFLAGS:=$(CXXFLAGS) $(CFLAGS)


############### options for linker
#

LDFLAGS		:= $(LDFLAGS) 			\

###############	make targets
#
all:		$(TARGET) $(INCLUDE)


.c:
		$(LINK.c) -o $@ $< $(LDLIBS)
.c.o:
		$(COMPILE.c) -o $@ $<
.cpp:
		$(LINK.cc) -o $@ $< $(LDLIBS)
.cpp.o:
		$(COMPILE.cc) -o $@ $<
.f:
		$(LINK.f) -o $@ $< $(LDLIBS)
.f.o:
		$(COMPILE.f) -o $@ $<
		
############### suffixes list
#
.SUFFIXES:	.o .so .a .c .cpp .h

.PHONY:		all clean depend

############### make shared object (dynamic link library)
#
$(TARGET):	$(OBJS)
		$(LINK.cc) -o $@ $(OBJS) $(LDLIBS)

###############	clean up
#
clean:
		-$(RM) $(OBJS)


###############	update dependencies
#
depend:
		makedepend -Y -- $(CPPFLAGS) *.c *.cc *.cpp 2> /dev/null

cleandepend:
		makedepend

# DO NOT DELETE

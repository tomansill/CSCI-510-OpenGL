#
# Created by makemake (Darwin Oct 17 2014) on Sun Dec  7 23:53:54 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb -Wall -ansi -pedantic
CFLAGS =	-ggdb -Wall -ansi -pedantic
BINDIR =./bin
CLIBFLAGS =	-lm
CCLIBFLAGS =	
########## End of default flags

########## Flags from header.mak

#
# This header.mak file will set up all necessary options for compiling
# and linking C and C++ programs which use OpenGL and/or GLUT on the
# Ubuntu systems.
#
# To use it, place it in the same directory as your source code, and
# run the command
#
#       gmakemake > Makefile
#
# To compile and link your program, just run "make".
#
# If you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
INCLUDE =
LIBDIRS =

LDLIBS = -lglut -lGL -lm -lGLEW -lSOIL

CFLAGS = -g $(INCLUDE) -DGL_GLEXT_PROTOTYPES
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

########## End of flags from header.mak


CPP_FILES =	cgShape.cpp finalMain.cpp lightingParams.cpp shaderSetup.cpp simpleShape.cpp viewParams.cpp
C_FILES =	
S_FILES =	
H_FILES =	cgShape.h lightingParams.h shaderSetup.h simpleShape.h viewParams.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	cgShape.o lightingParams.o shaderSetup.o simpleShape.o viewParams.o 

#
# Main targets
#

all:	${BINDIR}/finalMain 

${BINDIR}/finalMain:	finalMain.o $(OBJFILES)
	@mkdir -p ${BINDIR}/
	$(CXX) $(CXXFLAGS) -o ${BINDIR}/finalMain finalMain.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

cgShape.o:	simpleShape.h
finalMain.o:	cgShape.h lightingParams.h shaderSetup.h simpleShape.h viewParams.h
lightingParams.o:	lightingParams.h
shaderSetup.o:	shaderSetup.h
simpleShape.o:	simpleShape.h
viewParams.o:	viewParams.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) finalMain.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf ${BINDIR}/finalMain 

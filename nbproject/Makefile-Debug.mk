#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Board.o \
	${OBJECTDIR}/Figure.o \
	${OBJECTDIR}/Main.o \
	${OBJECTDIR}/TestMieszko.o \
	${OBJECTDIR}/TestRafal.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs sfml-graphics` `pkg-config --libs sfml-system` `pkg-config --libs sfml-window` -lopencv_core -lopencv_highgui -lopencv_imgproc  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chessboard

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chessboard: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chessboard ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Board.o: Board.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `pkg-config --cflags sfml-graphics` `pkg-config --cflags sfml-system` `pkg-config --cflags sfml-window`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Board.o Board.cpp

${OBJECTDIR}/Figure.o: Figure.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `pkg-config --cflags sfml-graphics` `pkg-config --cflags sfml-system` `pkg-config --cflags sfml-window`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Figure.o Figure.cpp

${OBJECTDIR}/Main.o: Main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `pkg-config --cflags sfml-graphics` `pkg-config --cflags sfml-system` `pkg-config --cflags sfml-window`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/Main.o Main.cpp

${OBJECTDIR}/TestMieszko.o: TestMieszko.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `pkg-config --cflags sfml-graphics` `pkg-config --cflags sfml-system` `pkg-config --cflags sfml-window`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/TestMieszko.o TestMieszko.cpp

${OBJECTDIR}/TestRafal.o: TestRafal.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `pkg-config --cflags sfml-graphics` `pkg-config --cflags sfml-system` `pkg-config --cflags sfml-window`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/TestRafal.o TestRafal.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chessboard

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

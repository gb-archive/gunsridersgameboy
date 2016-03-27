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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/e1eeb976/K.o \
	${OBJECTDIR}/_ext/e1eeb976/gfx.o \
	${OBJECTDIR}/_ext/e1eeb976/music.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-L/C/gbdk/lib/medium/asxxxx/gb -lgb

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mirom.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mirom.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mirom ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/e1eeb976/K.o: /C/C++/GameBoy/K.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/e1eeb976
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/gbdk/include -include /C/gbdk/include/gb -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e1eeb976/K.o /C/C++/GameBoy/K.c

${OBJECTDIR}/_ext/e1eeb976/gfx.o: /C/C++/GameBoy/gfx.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/e1eeb976
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/gbdk/include -include /C/gbdk/include/gb -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e1eeb976/gfx.o /C/C++/GameBoy/gfx.c

${OBJECTDIR}/_ext/e1eeb976/music.o: /C/C++/GameBoy/music.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/e1eeb976
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/gbdk/include -include /C/gbdk/include/gb -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e1eeb976/music.o /C/C++/GameBoy/music.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/gbdk/include -include /C/gbdk/include/gb -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mirom.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

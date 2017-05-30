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
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1569865365/DOMPrintFilter.o \
	${OBJECTDIR}/_ext/1569865365/DOMPrintErrorHandler.o \
	${OBJECTDIR}/_ext/1569865365/DOMTreeErrorReporter.o \
	${OBJECTDIR}/createDomDocument.o


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
LDLIBSOPTIONS=/usr/local/Cellar/xerces-c/3.1.1/lib/libxerces-c.dylib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/createdomdocument

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/createdomdocument: /usr/local/Cellar/xerces-c/3.1.1/lib/libxerces-c.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/createdomdocument: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/createdomdocument ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1569865365/DOMPrintFilter.o: /Users/brian/Code/xerces/DOMPrint/DOMPrintFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1569865365
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1569865365/DOMPrintFilter.o /Users/brian/Code/xerces/DOMPrint/DOMPrintFilter.cpp

${OBJECTDIR}/_ext/1569865365/DOMPrintErrorHandler.o: /Users/brian/Code/xerces/DOMPrint/DOMPrintErrorHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1569865365
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1569865365/DOMPrintErrorHandler.o /Users/brian/Code/xerces/DOMPrint/DOMPrintErrorHandler.cpp

${OBJECTDIR}/_ext/1569865365/DOMTreeErrorReporter.o: /Users/brian/Code/xerces/DOMPrint/DOMTreeErrorReporter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1569865365
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1569865365/DOMTreeErrorReporter.o /Users/brian/Code/xerces/DOMPrint/DOMTreeErrorReporter.cpp

${OBJECTDIR}/createDomDocument.o: createDomDocument.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/createDomDocument.o createDomDocument.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/createdomdocument

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

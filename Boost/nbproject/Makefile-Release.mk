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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1322698509/DOMPrintErrorHandler.o \
	${OBJECTDIR}/_ext/1322698509/createDomDocument.o \
	${OBJECTDIR}/_ext/1322698509/DOMTreeErrorReporter.o \
	${OBJECTDIR}/BuildTree.o \
	${OBJECTDIR}/_ext/1322698509/DOMPrintFilter.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1322698509/DOMPrintErrorHandler.o: /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMPrintErrorHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1322698509
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1322698509/DOMPrintErrorHandler.o /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMPrintErrorHandler.cpp

${OBJECTDIR}/_ext/1322698509/createDomDocument.o: /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/createDomDocument.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1322698509
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1322698509/createDomDocument.o /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/createDomDocument.cpp

${OBJECTDIR}/_ext/1322698509/DOMTreeErrorReporter.o: /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMTreeErrorReporter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1322698509
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1322698509/DOMTreeErrorReporter.o /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMTreeErrorReporter.cpp

${OBJECTDIR}/BuildTree.o: BuildTree.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BuildTree.o BuildTree.cpp

${OBJECTDIR}/_ext/1322698509/DOMPrintFilter.o: /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMPrintFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1322698509
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1322698509/DOMPrintFilter.o /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMPrintFilter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

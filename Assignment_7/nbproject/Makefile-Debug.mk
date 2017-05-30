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
	${OBJECTDIR}/_ext/1569865365/DOMPrintErrorHandler.o \
	${OBJECTDIR}/_ext/1569865365/DOMPrintFilter.o \
	${OBJECTDIR}/_ext/1569865365/DOMTreeErrorReporter.o \
	${OBJECTDIR}/createDomDoc.o


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
LDLIBSOPTIONS=/usr/local/Cellar/xerces-c/3.1.1/lib/libxerces-c.dylib -lboost_atomic-mt -lboost_chrono-mt -lboost_chrono -lboost_context-mt -lboost_context -lboost_coroutine-mt -lboost_coroutine -lboost_date_time-mt -lboost_date_time -lboost_filesystem-mt -lboost_filesystem -lboost_graph-mt -lboost_graph -lboost_iostreams-mt -lboost_iostreams -lboost_locale-mt -lboost_log-mt -lboost_log -lboost_log_setup-mt -lboost_log_setup -lboost_math_c99-mt -lboost_math_c99 -lboost_math_c99f-mt -lboost_math_c99f -lboost_math_c99l-mt -lboost_math_c99l -lboost_math_tr1-mt -lboost_math_tr1 -lboost_math_tr1f-mt -lboost_math_tr1f -lboost_math_tr1l-mt -lboost_math_tr1l -lboost_prg_exec_monitor-mt -lboost_prg_exec_monitor -lboost_program_options-mt -lboost_program_options -lboost_python-mt -lboost_python -lboost_random-mt -lboost_random -lboost_regex-mt -lboost_regex -lboost_serialization-mt -lboost_serialization -lboost_signals-mt -lboost_signals -lboost_system-mt -lboost_system -lboost_thread-mt -lboost_timer-mt -lboost_timer -lboost_unit_test_framework-mt -lboost_unit_test_framework -lboost_wave-mt -lboost_wave -lboost_wserialization-mt -lboost_wserialization

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/assignment_7

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/assignment_7: /usr/local/Cellar/xerces-c/3.1.1/lib/libxerces-c.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/assignment_7: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/assignment_7 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1569865365/DOMPrintErrorHandler.o: /Users/brian/Code/xerces/DOMPrint/DOMPrintErrorHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1569865365
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1569865365/DOMPrintErrorHandler.o /Users/brian/Code/xerces/DOMPrint/DOMPrintErrorHandler.cpp

${OBJECTDIR}/_ext/1569865365/DOMPrintFilter.o: /Users/brian/Code/xerces/DOMPrint/DOMPrintFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1569865365
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1569865365/DOMPrintFilter.o /Users/brian/Code/xerces/DOMPrint/DOMPrintFilter.cpp

${OBJECTDIR}/_ext/1569865365/DOMTreeErrorReporter.o: /Users/brian/Code/xerces/DOMPrint/DOMTreeErrorReporter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1569865365
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1569865365/DOMTreeErrorReporter.o /Users/brian/Code/xerces/DOMPrint/DOMTreeErrorReporter.cpp

${OBJECTDIR}/createDomDoc.o: createDomDoc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/createDomDoc.o createDomDoc.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/assignment_7

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

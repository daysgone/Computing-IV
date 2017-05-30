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
LDLIBSOPTIONS=/usr/local/Cellar/boost/1.55.0/lib/libboost_atomic-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_chrono-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_chrono.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_context-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_context.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_coroutine-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_coroutine.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_date_time-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_date_time.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_filesystem-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_filesystem.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_graph-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_graph.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_iostreams-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_iostreams.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_locale-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_log-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_log.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_log_setup-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_log_setup.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99f-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99f.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99l-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99l.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1f-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1f.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1l-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1l.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_prg_exec_monitor-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_prg_exec_monitor.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_program_options-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_program_options.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_python-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_python.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_random-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_random.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_regex-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_regex.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_serialization-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_serialization.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_signals-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_signals.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_system-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_system.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_thread-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_timer-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_timer.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_unit_test_framework-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_unit_test_framework.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_wave-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_wave.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_wserialization-mt.dylib /usr/local/Cellar/boost/1.55.0/lib/libboost_wserialization.dylib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_atomic-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_chrono-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_chrono.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_context-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_context.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_coroutine-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_coroutine.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_date_time-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_date_time.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_filesystem-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_filesystem.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_graph-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_graph.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_iostreams-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_iostreams.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_locale-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_log-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_log.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_log_setup-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_log_setup.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99f-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99f.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99l-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_c99l.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1f-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1f.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1l-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_math_tr1l.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_prg_exec_monitor-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_prg_exec_monitor.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_program_options-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_program_options.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_python-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_python.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_random-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_random.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_regex-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_regex.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_serialization-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_serialization.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_signals-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_signals.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_system-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_system.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_thread-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_timer-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_timer.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_unit_test_framework-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_unit_test_framework.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_wave-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_wave.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_wserialization-mt.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: /usr/local/Cellar/boost/1.55.0/lib/libboost_wserialization.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boost ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1322698509/DOMPrintErrorHandler.o: /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMPrintErrorHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1322698509
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1322698509/DOMPrintErrorHandler.o /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMPrintErrorHandler.cpp

${OBJECTDIR}/_ext/1322698509/createDomDocument.o: /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/createDomDocument.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1322698509
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1322698509/createDomDocument.o /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/createDomDocument.cpp

${OBJECTDIR}/_ext/1322698509/DOMTreeErrorReporter.o: /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMTreeErrorReporter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1322698509
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1322698509/DOMTreeErrorReporter.o /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMTreeErrorReporter.cpp

${OBJECTDIR}/BuildTree.o: BuildTree.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/BuildTree.o BuildTree.cpp

${OBJECTDIR}/_ext/1322698509/DOMPrintFilter.o: /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMPrintFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1322698509
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1322698509/DOMPrintFilter.o /Users/brian/Documents/Dropbox/Computing\ IV/Boost/createDOM/DOMPrintFilter.cpp

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

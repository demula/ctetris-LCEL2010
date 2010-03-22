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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/tests/prueba_pieza.o \
	${OBJECTDIR}/src/hardware.o \
	${OBJECTDIR}/src/m5272lib.o \
	${OBJECTDIR}/tests/prueba_puerto.o \
	${OBJECTDIR}/tests/prueba_leds.o \
	${OBJECTDIR}/tests/prueba_juego.o \
	${OBJECTDIR}/src/sonido.o \
	${OBJECTDIR}/src/m5272gpio.o \
	${OBJECTDIR}/src/m5272lcd.o \
	${OBJECTDIR}/src/control.o \
	${OBJECTDIR}/src/ctetris.o \
	${OBJECTDIR}/src/m5272adc-dac.o \
	${OBJECTDIR}/src/juego.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/ctetris

dist/Debug/GNU-Linux-x86/ctetris: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ctetris ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/tests/prueba_pieza.o: nbproject/Makefile-${CND_CONF}.mk tests/prueba_pieza.c 
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/tests/prueba_pieza.o tests/prueba_pieza.c

${OBJECTDIR}/src/hardware.o: nbproject/Makefile-${CND_CONF}.mk src/hardware.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/hardware.o src/hardware.c

${OBJECTDIR}/src/m5272lib.o: nbproject/Makefile-${CND_CONF}.mk src/m5272lib.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/m5272lib.o src/m5272lib.c

${OBJECTDIR}/tests/prueba_puerto.o: nbproject/Makefile-${CND_CONF}.mk tests/prueba_puerto.c 
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/tests/prueba_puerto.o tests/prueba_puerto.c

${OBJECTDIR}/tests/prueba_leds.o: nbproject/Makefile-${CND_CONF}.mk tests/prueba_leds.c 
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/tests/prueba_leds.o tests/prueba_leds.c

${OBJECTDIR}/tests/prueba_juego.o: nbproject/Makefile-${CND_CONF}.mk tests/prueba_juego.c 
	${MKDIR} -p ${OBJECTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/tests/prueba_juego.o tests/prueba_juego.c

${OBJECTDIR}/src/sonido.o: nbproject/Makefile-${CND_CONF}.mk src/sonido.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sonido.o src/sonido.c

${OBJECTDIR}/src/m5272gpio.o: nbproject/Makefile-${CND_CONF}.mk src/m5272gpio.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/m5272gpio.o src/m5272gpio.c

${OBJECTDIR}/src/m5272lcd.o: nbproject/Makefile-${CND_CONF}.mk src/m5272lcd.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/m5272lcd.o src/m5272lcd.c

${OBJECTDIR}/src/control.o: nbproject/Makefile-${CND_CONF}.mk src/control.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/control.o src/control.c

${OBJECTDIR}/src/ctetris.o: nbproject/Makefile-${CND_CONF}.mk src/ctetris.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ctetris.o src/ctetris.c

${OBJECTDIR}/src/m5272adc-dac.o: nbproject/Makefile-${CND_CONF}.mk src/m5272adc-dac.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/m5272adc-dac.o src/m5272adc-dac.c

${OBJECTDIR}/src/juego.o: nbproject/Makefile-${CND_CONF}.mk src/juego.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/juego.o src/juego.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/ctetris

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

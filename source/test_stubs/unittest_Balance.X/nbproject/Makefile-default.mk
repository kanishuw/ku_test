#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/unittest_Balance.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/unittest_Balance.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../unitest_gui_data.c ../unittest_bms_coreprocessing.c ../unittest_hw_gpio.c ../unittest_hw_timers.c ../unittest_utilities.c unittest_bms_app_balance_start_calculate.c main.c ../../bms_app_balance.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/unitest_gui_data.o ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o ${OBJECTDIR}/_ext/1472/unittest_utilities.o ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o ${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/43898991/bms_app_balance.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/unitest_gui_data.o.d ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o.d ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o.d ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o.d ${OBJECTDIR}/_ext/1472/unittest_utilities.o.d ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/_ext/43898991/bms_app_balance.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/unitest_gui_data.o ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o ${OBJECTDIR}/_ext/1472/unittest_utilities.o ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o ${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/43898991/bms_app_balance.o

# Source Files
SOURCEFILES=../unitest_gui_data.c ../unittest_bms_coreprocessing.c ../unittest_hw_gpio.c ../unittest_hw_timers.c ../unittest_utilities.c unittest_bms_app_balance_start_calculate.c main.c ../../bms_app_balance.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/unittest_Balance.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP64MC206
MP_LINKER_FILE_OPTION=,--script=p33EP64MC206.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/unitest_gui_data.o: ../unitest_gui_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unitest_gui_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unitest_gui_data.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unitest_gui_data.c  -o ${OBJECTDIR}/_ext/1472/unitest_gui_data.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unitest_gui_data.o.d"      -g -D__DEBUG   -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unitest_gui_data.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o: ../unittest_bms_coreprocessing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unittest_bms_coreprocessing.c  -o ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o.d"      -g -D__DEBUG   -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o: ../unittest_hw_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unittest_hw_gpio.c  -o ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o.d"      -g -D__DEBUG   -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/unittest_hw_timers.o: ../unittest_hw_timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unittest_hw_timers.c  -o ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unittest_hw_timers.o.d"      -g -D__DEBUG   -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unittest_hw_timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/unittest_utilities.o: ../unittest_utilities.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_utilities.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unittest_utilities.c  -o ${OBJECTDIR}/_ext/1472/unittest_utilities.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unittest_utilities.o.d"      -g -D__DEBUG   -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unittest_utilities.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o: unittest_bms_app_balance_start_calculate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o.d 
	@${RM} ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  unittest_bms_app_balance_start_calculate.c  -o ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o.d"      -g -D__DEBUG   -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/43898991/bms_app_balance.o: ../../bms_app_balance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/bms_app_balance.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/bms_app_balance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bms_app_balance.c  -o ${OBJECTDIR}/_ext/43898991/bms_app_balance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/43898991/bms_app_balance.o.d"      -g -D__DEBUG   -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/bms_app_balance.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1472/unitest_gui_data.o: ../unitest_gui_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unitest_gui_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unitest_gui_data.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unitest_gui_data.c  -o ${OBJECTDIR}/_ext/1472/unitest_gui_data.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unitest_gui_data.o.d"      -g -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unitest_gui_data.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o: ../unittest_bms_coreprocessing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unittest_bms_coreprocessing.c  -o ${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o.d"      -g -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unittest_bms_coreprocessing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o: ../unittest_hw_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unittest_hw_gpio.c  -o ${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o.d"      -g -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unittest_hw_gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/unittest_hw_timers.o: ../unittest_hw_timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unittest_hw_timers.c  -o ${OBJECTDIR}/_ext/1472/unittest_hw_timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unittest_hw_timers.o.d"      -g -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unittest_hw_timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/unittest_utilities.o: ../unittest_utilities.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/unittest_utilities.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../unittest_utilities.c  -o ${OBJECTDIR}/_ext/1472/unittest_utilities.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/unittest_utilities.o.d"      -g -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/unittest_utilities.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o: unittest_bms_app_balance_start_calculate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o.d 
	@${RM} ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  unittest_bms_app_balance_start_calculate.c  -o ${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o.d"      -g -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/unittest_bms_app_balance_start_calculate.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/43898991/bms_app_balance.o: ../../bms_app_balance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/bms_app_balance.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/bms_app_balance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bms_app_balance.c  -o ${OBJECTDIR}/_ext/43898991/bms_app_balance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/43898991/bms_app_balance.o.d"      -g -omf=elf -O0 -I"../../" -DUNIT_TESTING -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/bms_app_balance.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/unittest_Balance.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/unittest_Balance.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG   -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/unittest_Balance.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/unittest_Balance.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/unittest_Balance.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

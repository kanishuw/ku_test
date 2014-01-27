/* 
 * File:   main.c
 * Author: kevin
 *
 * Created on October 11, 2013, 6:16 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "bms_defs.h"

CoreDataType gCoreData[ MAX_NUM_CORES ];
CoreDataType gCoreDataSlow[ MAX_NUM_CORES ];

BMSBatterySummaryType gBatterySummary;
BMSSystemStatusType gBatteryStatus;

CBITFlagsType gCBITFlags;
PBITFlagsType gPBITFlags;
WarrentyViolationsType gWarrantyViolations;

float gElapsed;

/*
 * 
 */
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}


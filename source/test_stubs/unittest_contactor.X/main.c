/* 
 * File:   main.c
 * Author: kevin
 *
 * Created on October 23, 2013, 7:08 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../../bms_defs.h"

CoreDataType gCoreData[ MAX_NUM_CORES ];
CoreDataType gCoreDataSlow[ MAX_NUM_CORES ];

BMSBatterySummaryType gBatterySummary;
BMSSystemStatusType gBatteryStatus;

CBITFlagsType gCBITFlags;
PBITFlagsType gPBITFlags;
WarrentyViolationsType gWarrantyViolations;

void run_bms_app_process_contactor();


/*
 * 
 */
int main(int argc, char** argv)
{

    run_bms_app_process_contactor();

    return (EXIT_SUCCESS);
}


/* 
 * File:   main.c
 * Author: kevin
 *
 * Created on October 11, 2013, 5:33 AM
 */

#if defined(__dsPIC33E__)
#include "p33exxxx.h"
#elif defined(__PIC24E__)
#include "p24exxxx.h"
#endif

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


// Select Internal FRC at POR
// PWM registers may be written without key sequence
// Start up with user-selected oscillator source
_FOSCSEL(FNOSC_FRC & PWMLOCK_OFF & IESO_OFF);

// Clock Switching is Enabled and Fail Safe Clock Monitor is disabled
// OSC2 Pin Function: OSC2 is Digital I/O
// Primary Oscillator Mode: Disabled
//_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);

// Watchdog Timer Enabled/disabled by user software
//Set prescaler = 32000(CLK)/128 & postscaler = prescaler/32768 & window=PLL=OFF
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS32768 & PLLKEN_OFF);
// FWDT
//#pragma config WDTPOST = PS512          // Watchdog Timer Postscaler bits (1:512)
//#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
//#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch will not wait for the PLL lock signal.)
//#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
//#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

//Set ICS JTAG Debugger bits to PGEC1 & PGED1; Disable PGEC2 & PGED2
_FICD(ICS_PGD1 & JTAGEN_OFF);

//Change ASCL2 to SCL2 for I2C2 module
_FPOR(ALTI2C2_OFF);


/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.
 *
 * Note:            None
 *******************************************************************/
static void initialize_system(void) {
    // To execute instruction at 60 MHz, ensure that the
    // system clock frequency is: FOSC = 2 x FCY = 120 MHz
    // To set up the PLL and meet the requirements of the PLL
    // Select the PLL postscaler to meet VCO output frequency
    // requirement (120 MHz < FSYS < 340 MHz).
    //     ? Select a PLL postscaler ratio of N2 = 2
    //     ? Ensure that FSYS = (FOSC x N2) = 240 MHz
    // Select the PLL prescaler to meet PFD input frequency
    // requirement (0.8 MHz < FPLLI < 8.0 MHz).
    //     ? Select a PLL prescaler ratio of N1 = 2
    //     ? Ensure that FPLLI = (FIN  N1) = 3.68 MHz
    // Select the PLL feedback divisor to generate required
    // VCO output frequency based on the PFD input frequency.
    //     ? FSYS = FPLLI x M
    //     ? M  =  FSYS  FPLLI = 65
    PLLFBD = 63; /* M  = 65	*/
    CLKDIVbits.PLLPOST = 0; /* N2 = 2	*/
    // N1 = 3 for 40MHz
    CLKDIVbits.PLLPRE = 1; /* N1 = 3	*/

    OSCTUN = 0;

    // Initiate Clock Switch to FRC oscillator
    // with PLL (NOSC= 0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);

    // Wait for clock switch to occur
    while (OSCCONbits.COSC != 0b001) {
    };

    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1) {
    };

}

void run_bms_app_balance_calculate_unit_test();
void run_bms_app_balance_get_group_mask_uint_test();
void run_bms_app_balance_calculate_unit_test();
void run_bms_app_balance_get_group_mask_uint_test();
void run_bms_app_balance_update_times_unit_test();
void run_bms_app_balance_start_test();
void run_bms_app_balance_stop_test();
void run_bms_app_balance_check_progress_test();
void run_bms_app_balance_is_okay_to_balance_test();

void run_unit_tests()
{
    run_bms_app_balance_calculate_unit_test();
    run_bms_app_balance_get_group_mask_uint_test();
    run_bms_app_balance_update_times_unit_test();
    run_bms_app_balance_start_test();
    run_bms_app_balance_stop_test();
    run_bms_app_balance_check_progress_test();
    run_bms_app_balance_is_okay_to_balance_test();
}

void run_functional_tests()
{
}

/*
 * 
 */
int main(int argc, char** argv)
{
    initialize_system();

    run_unit_tests();

    run_functional_tests();

    return (EXIT_SUCCESS);
}



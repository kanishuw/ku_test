/*****************************************************************************
 * REVISION HISTORY:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author           Date        Comments on this revision
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Udai Kumar       11/25/2012  First release of source file
 * Udai Kumar       12/05/2012  Removed all references to USB
 * Udai Kumar       12/05/2012  Changed to internal FRC
 * Nicolas Avlas    01/25/2013  Many Changes including Added Functions & Main Loop
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ADDITIONAL NOTES: This implements a basic driver for UART transmission and
 * reception.
 *****************************************************************************/

#if defined(__dsPIC33E__)
#include "p33exxxx.h"
#elif defined(__PIC24E__)
#include "p24exxxx.h"
#endif

//TODO:  Get rid of anything associated with "15 board build"
//TODO:  Keep final board

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "bms_defs.h"
#include "bms_app_cutback.h"
#include "cutback_test_data.h"
#include "utilities.h"

#include "DEE Emulation 16-bit.h"

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

/*******************************************************************************
 * Set UserID:
 * FUID0 = Part Revision Number(2-bits)(MSB)
 * FUID1 = BMS Serial Number (MSB-SN)
 * FUID2 = BMS Serial Number (LSB-SN)
 * FUID3 = Manufacturing Lot Number
 ******************************************************************************/
/*Used only when NOT using Automatic Serialization with Production Programmer */
//_FUID0(0x00);    //Part Revision Number (MSB)
//_FUID1(0x00);    //Serial Number (MSB-SN)
//_FUID2(0x00);    //Serial Number (LSB-SN)
//_FUID3(0x0F);    //Lot Number (LSB)
/******************************************************************************/
#pragma udata


long MemRead(unsigned int page, unsigned int offset);

// Address of Samsung Warranty information in emulated EEPROM in Program Memory
#define SAMSUNG_WARRANTY_ADDRESS    (2)
#define BQ77_I2C_BUS_SPEED          (20000)

// Timer1 interrupt count for 10msec interrupt
#define TIMER_100_MSEC              (10)


CoreDataType gCoreData[ MAX_NUM_CORES ];
BMSBatterySummaryType gBatterySummary;
BMSSystemStatusType gBatteryStatus;

CBITFlagsType gCBITFlags;
PBITFlagsType gPBITFlags;
WarrentyViolationsType gWarrentyViolations;

unsigned int sNeedCalibration = 0;

#pragma code

/********************************************************************
 * Function:        void InitBmsInfo(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is initializes core information and status
 *                  packets and other variables.
 *
 * Note:            None
 *******************************************************************/
void init_bms_application() {
    BMS_eds_memset(&gCoreData, 0, sizeof ( gCoreData));
    memset(&gBatterySummary, 0, sizeof ( gBatterySummary));
    memset(&gBatteryStatus, 0, sizeof ( gBatteryStatus));
    memset(&gCBITFlags, 0, sizeof ( gCBITFlags));
    memset(&gPBITFlags, 0, sizeof ( gPBITFlags));
    memset(&gWarrentyViolations, 0, sizeof ( gWarrentyViolations));

    gBatteryStatus.bits.sleep_mode_active = 0;
    gBatteryStatus.bits.key_input_state = BMS_KEY_STATE_OFF;
    gBatteryStatus.bits.charger_connected = CHARGER_NOT_CONNECTED;
    gBatteryStatus.bits.charging_mode = CHARGING_MODE_IDLE;
    gBatteryStatus.bits.storage_mode = STORAGE_MODE_DISABLED;
    gBatteryStatus.bits.forever_power_mode = 0;
    gBatteryStatus.bits.economy_mode = ECONOMY_MODE_DISABLED;
    gBatteryStatus.bits.balancing_mode = 0;
    gBatteryStatus.bits.contactor_closed = 0;
    gBatteryStatus.bits.discharge_enable = 0;
    gBatteryStatus.bits.controller_voltage_cutback = 0;
    gBatteryStatus.bits.controller_temp_cutback = 0;
    gBatteryStatus.bits.storage_mode = 0;

    gBatterySummary.deviceId = MemRead(0xFF, 0x0000);
    gBatterySummary.deviceRev = MemRead(0xFF, 0x0002);
}

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

unsigned char   gTraceArray[25];

void tra_initialize( unsigned char *c, unsigned char len )
{
    memset( c, 0, len );
}

void tra_toggle( unsigned char *c, unsigned int idx )
{
    c[ idx ] = c[ idx ] ? 0 : 1;
}

void load_test_data()
{
}
/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *****************************************************************************/
int main(void) {
    initialize_system(); //Implements Master counter, Chipset_init, Data_setup, Memory_state_setup

    bms_app_cutback_initialize();

//    load_low_to_high_temperature_test( 3.70, 3.90, 5.0 );
//
//    while( prepare_test_data() )
//    {
//        bms_app_cutback_process();
//    }
//
//    examine_results();

//    load_high_to_low_temperature_test( 3.70, 3.90, 5.0 );
//
//    while( prepare_test_data() )
//    {
//        bms_app_cutback_process();
//    }

//    examine_results();

    load_discharge_test( 25.0, 28.0, 0.100 );
    while( prepare_test_data() )
    {
        bms_app_cutback_process();
    }

    examine_results();

//    load_discharge_test_vmax( 25.0, 28.0, 0.100 );
//    while( prepare_test_data() )
//    {
//        bms_app_cutback_process();
//    }
//
//    examine_results();

//    load_discharge_test_economy( 25.0, 28.0, 0.100 );
//    while( prepare_test_data() )
//    {
//        bms_app_cutback_process();
//    }
//
//    examine_results();


//    load_charge_test( 25.0, 28.0, 0.100, 0 );
//
//    while( prepare_test_data() )
//    {
//        bms_app_cutback_process();
//    }
//
//    examine_results();
//
//    load_regen_test( 25.0, 28.0, 0.100, 0 );
//
//    while( prepare_test_data() )
//    {
//        bms_app_cutback_process();
//    }
//
//    examine_results();

    return 0;
}


/** EOF main.c *************************************************/

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
    int i = 0;
    ANSELC = 0x0000;    // a 0 causes the pin to be set to digital
    TRISC = 0xDFFF;     // A 0 causes the pin to be an output  RC13
    CNPUC = 0x00FF;     // Enable weak pull up
    CNPDC = 0x0000;     // Disable weak pull down

	
    while (1) {
		i+=3;
    }

    return 0;
}


/** EOF main.c *************************************************/

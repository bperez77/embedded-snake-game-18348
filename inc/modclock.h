/*
Clock Modification Library
Chris Szilagyi
9-21-2009
modclock.h

This library is designed to modify the bus clock speed of 
the APS12C128 development module to 8 MHz from its original
speed of 2 MHz.

*/
#include <hidef.h>      /* common defines and macros */
#include <MC9S12C128.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12c128"


/* Initialize the PLL clk and modify oscillator clk speed */
void clockSetup(void);

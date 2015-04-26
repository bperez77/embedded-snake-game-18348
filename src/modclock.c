/*
Clock Modification Library
Chris Szilagyi
9-21-2009
modclock.c

This library is designed to modify the bus clock speed of 
the APS12C128 development module to 8 MHz from its original
speed of 2 MHz.

*/
#include "modclock.h"

void clockSetup() {
  
  int i = 0;
  
  //These two lines are for debug purposes only,
  //PEAR.NECLK = 0, PortE.ECLK pin shows bus clock  
  //PEAR = PEAR & 0xEF;
  //MODE.IVIS = 1, Internal bus operations visible on external pins
  //MODE = MODE | 0x08; 
  
  //Setup Bus clock to run from PLL clock
  
  //PLLCTL.PLLON = 1, Turn on PLL circuitry
  PLLCTL = PLLCTL | 0x40;
  
  //Wait
  for (i = 0; i < 10000; i++) {
    
  }
  
  //According to Data sheet:
  //PLLCLK = 2 x OSCCLK x (SYNR+1)/(REFDV+1)
  //If CLKSEL.PLLSEL = 1, then Bus clock = PLLCLK/2
  //                      else Bus clock = OSCCLK/2
  //SYNR = 1 gives us a speedup of 4x (Since OSCCLK = 4 MHz)
  //REFDV = 0

  SYNR = 0x01;
  REFDV = 0x00;
  
  //Wait
  for (i = 0; i < 10000; i++) {
    
  }
  
  //CLKSEL.PLLSEL = 1, to derive system clocks from PLL clock
  CLKSEL = CLKSEL | 0x80;
  
}
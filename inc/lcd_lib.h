/*
  LCD Library verison 1.2
  Justin Ray
  9-20-2006
  lcd_lib.h
  
  This library is designed to give easy access to the
  LCD display on the MCUSLK project board using the
  CMS12C32 development module.

  Include this file in your project to use the functions
  described below to access the LCD.
  
  Version 1.1 adds the lcdWriteLine() function for writing
  individual lines of the display and exposes the sleepMS()
  function which may be useful to insert NOP delays
  
  Verison 1.2 fixed a bug in sleepMS so that it will work for
  large values of the argument ms.
  

*/

/*

  lcdSetup initilizes the SPI port and the LCD panel.

*/
void lcdSetup( void );


/*
  lcdSimpleWrite - writes the first 16 characters
  of the null-terminated string str to the LCD 
  display.  Spaces are used to fill the display if
  the string is to short.  Any characters beyond
  the first 16 are ignored.
*/
void lcdSimpleWrite(char *str);



/*
  lcdSimpleWrite - writes the first 8 characters
  of the null-terminated string str to the LCD 
  display.  Spaces are used to fill the display if
  the string is too short.  Any characters beyond
  the first 8 are ignored.
  
  The line written to is determined by the line
  argument.  If the argument is not in the range [1,2],
  nothing is written to the display
*/
void lcdWriteLine(int line, char *str);



/*
  Call to enter a NOP loop that lasts approximately
  <ms> milliseconds.
*/
void sleepMS(unsigned long ms);
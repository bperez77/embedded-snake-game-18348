/*
  LCD Library Version 1.2
  Justin Ray
  9-20-2006
  lcd_lib.c
  
  This library is designed to give easy access to the
  LCD display on the MCUSLK project board using the
  CMS12C32 development module.

  This file contains the implementation and supporting
  functions.
  
  Version 1.1 adds the lcdWriteLine() function for writing
  individual lines of the display and exposes the sleepMS()
  function which may be useful to insert NOP delays
  
  Verison 1.2 fixed a bug in sleepMS so that it will work for
  large values of the argument ms.
  
*/

#include <hidef.h>      /* common defines and macros */
#include <mc9s12c128.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12c128"

#include "lcd_lib.h"


/********************

  DECLARATIONS PRIVATE TO LCD_LIB

*********************/

//function prototypes for local functions
void spiSetup( void );
void spiWrite(volatile unsigned char data);
void lcdNibbleWrite(volatile unsigned char data);
void sleepMSTenth(unsigned long msTenths);
void lcdCommand(volatile unsigned char data);
void lcdSetDataAddr(unsigned char addr);
void lcdWriteData(unsigned char addr);


/*
 *     LCD address defines
 */
 
#define ADDR_ROW_1 0x00
#define ADDR_ROW_2 0x40



/*
 *     LCD command defines
 */
//nibble-mode
//N=1 (two line display)
//F=0 (5x7 characters)
#define LCD_FUNCTION_SET 0x28

//turn off display
#define LCD_DISPLAY_OFF 0x08

//turn on display
#define LCD_DISPLAY_ON 0x0C
//flags for display
#define LCD_FL_CURSOR 0x02 //cursor visible if set
#define LCD_FL_BLINK 0x01  //cursor blinks if set

//clear display
#define LCD_CLEAR 0x01

//entry mode
#define LCD_ENTRY_MODE 0x04
//flags for entry mode
#define LCD_FL_INCREMENT 0x02 //cursor increments with data write if set
#define LCD_FL_SHIFT    0x01 

//set data ram address
#define LCD_DATARAM_ADDRESS 0x80

//set cg ram address
#define LCD_CGRAM_ADDRESS 0x40

//cursore or display shift
#define LCD_CURSOR_SHIFT 0x10
#define LCD_DISPLAY_SHIFT 0x18
//cursor/display flags
#define LCD_FL_SHIFT_RIGHT 0x04



/*
 *     SPI constant defines
 */
//defines that are local to the library go here
#define EN_BIT 0x80
#define RS_BIT 0x40

//globals
//none





/********************

  PUBLIC FUNCTIONS

*********************/


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
void lcdWriteLine(int line, char *str) {
  char writeStr=1;
  char i;
  
  //set address
  switch(line){
    case 1:
      lcdSetDataAddr(ADDR_ROW_1);
      break;
    case 2:
      lcdSetDataAddr(ADDR_ROW_2);
      break;
    default:
      return;
  }
  //if we didn't return, then write the data
  for (i=0;i<8;i++) {
    if (writeStr) {
      if (str[i] == 0) {
        writeStr=0;                    
        lcdWriteData(' ');
      } else {
        lcdWriteData(str[i]);
      }
    } else {
      lcdWriteData(' '); 
    }
  }
  
  
}

/*
  lcdSimpleWrite - writes the first 16 characters
  of the null-terminated string str to the LCD 
  display.  Spaces are used to fill the display if
  the string is to short.  Any characters beyond
  the first 16 are ignored.
*/
void lcdSimpleWrite(char *str) {
  char writeStr=1;
  char i;

  //write first line
  lcdSetDataAddr(ADDR_ROW_1);
  for (i=0;i<8;i++) {
    if (writeStr) {
      if (str[i] == 0) {
        writeStr=0;                    
        lcdWriteData(' ');
      } else {
        lcdWriteData(str[i]);
      }
    } else {
      lcdWriteData(' '); 
    }
  }
  lcdSetDataAddr(ADDR_ROW_2);
  for (i=8;i<16;i++) {
    if (writeStr) {
      if (str[i] == 0) {
        writeStr=0;                    
        lcdWriteData(' ');
      } else {
        lcdWriteData(str[i]);
      }
    } else {
      lcdWriteData(' '); 
    }
  }
  
}

/*

  lcdSetup initilizes the SPI port and the LCD panel.

*/
void lcdSetup( void ) {

  //configure SPI
  spiSetup();

  //set 8 bit mode
  lcdNibbleWrite(0x03);
  sleepMS(5);
  //set 8 bit mode
  lcdNibbleWrite(0x03);
  sleepMS(1);
  //set 4 bit mode
  lcdNibbleWrite(0x02);
  //set 4 bit mode again
  //(both nibbles will be seen this time)
  //set N and F
  lcdCommand(LCD_FUNCTION_SET);
  sleepMSTenth(1);
  //set Display OFF
  lcdCommand(LCD_DISPLAY_OFF);
  sleepMSTenth(1);
  //set clear display
  lcdCommand(LCD_CLEAR);
  sleepMS(16);
  //set entry mode
  //increment but no shift
  lcdCommand(LCD_ENTRY_MODE | LCD_FL_INCREMENT);
  sleepMSTenth(1);
  //set display on (w / cursor, no blink)
  //lcdCommand(LCD_DISPLAY_ON | LCD_FL_CURSOR | LCD_FL_BLINK);
  lcdCommand(LCD_DISPLAY_ON);
  sleepMSTenth(1);
}


/********************

  PRIVATE FUNCTIONS

*********************/

void lcdSetDataAddr(unsigned char addr) {
  lcdCommand(LCD_DATARAM_ADDRESS | addr);
  sleepMSTenth(1);
}

void lcdWriteData(unsigned char addr) {
  unsigned char temp;


  //for each nibble written,
  //three writes to the HC595 are required to create
  //an EN pulse

  //write once to set the RS bit high
  spiWrite(RS_BIT);
  sleepMSTenth(1);

  //get upper nibble
  temp = (addr >> 4) & 0x0F;
  //set the RS bit
  temp = temp | RS_BIT;
  //write the data with the EN bit disabled
  spiWrite(temp & ~EN_BIT);
  sleepMSTenth(1);
  //write the data with the EN bit enabled
  spiWrite(temp | EN_BIT); //set en and data
  sleepMSTenth(1);
  //write the data with the EN bit disabled
  spiWrite(temp & ~EN_BIT);
  sleepMSTenth(1);


  //get lower nibble
  temp = (addr) & 0x0F;
  //set the RS_BIT
  temp = temp | RS_BIT;
  //write the data with the EN bit disabled
  spiWrite(temp & ~EN_BIT);
  sleepMSTenth(1);
  //write the data with the EN bit enabled
  spiWrite(temp | EN_BIT); //set en and data
  sleepMSTenth(1);
  //write the data with the EN bit disabled
  spiWrite(temp & ~EN_BIT);
  sleepMSTenth(1);  
  
  //set the RS bit low at the end
  spiWrite(0x00);
  sleepMSTenth(1);
  
}



/*
  lcdCommand - write the data to the LCD vis the 
  SPI port and HC595 shift register.  Because the LCD
  is in four-bit mode, this is done as two nibble-writes.
*/
void lcdCommand(volatile unsigned char data) {
  unsigned char temp;

  //for each nibble written,
  //three writes to the HC595 are required to create
  //an EN pulse

  //get upper nibble
  temp = (data >> 4) & 0x0F;
  //write the data with the EN bit disabled
  spiWrite(temp & ~EN_BIT);
  sleepMSTenth(1);
  //write the data with the EN bit enabled
  spiWrite(temp | EN_BIT); //set en and data
  sleepMSTenth(1);
  //write the data with the EN bit disabled
  spiWrite(temp & ~EN_BIT);
  sleepMSTenth(1);


  //get lower nibble
  temp = (data) & 0x0F;
  //write the data with the EN bit disabled
  spiWrite(temp & ~EN_BIT);
  sleepMSTenth(1);
  //write the data with the EN bit enabled
  spiWrite(temp | EN_BIT); //set en and data
  sleepMSTenth(1);
  //write the data with the EN bit disabled
  spiWrite(temp & ~EN_BIT);
  sleepMSTenth(1);
  
}

/*
  lcdNibbleWrite - write the lower four bits of data to
  the LCD vis the SPI port and HC595 shift register
*/
void lcdNibbleWrite(volatile unsigned char data) {
  //three writes to the HC595 are required to create
  //an EN pulse

  //write the data with the EN bit disabled
  spiWrite(data & ~EN_BIT);
  sleepMSTenth(1);
  //write the data with the EN bit enabled
  spiWrite(data | EN_BIT); //set en and data
  sleepMSTenth(1);
  //write the data with the EN bit disabled
  spiWrite(data & ~EN_BIT);
  sleepMSTenth(1);
  
}

/*
    spiWrite - wait until the SPI transmitter is free
    and transmit the byte in data
*/
void spiWrite(volatile unsigned char data) {
  //  unsigned char readval;
  
  while (!(SPISR & 0x20)) { } //wait for SPTEF = 1
  SPIDR = data; //write value to data reg
  
  //to receive
  //while (!(SPISR & 0x80)) { } //wait for SPIF = 1
  //readval = SPIDR; // read value 

}


/*
    spiSetup - configure the SPI registers
*/
void spiSetup( void ) {
  
  //enable SPI as master, using the SS* output
  //to enable a single device.
  //clock polarity is active low
  //clock phase is sampling on even edges
  //interrupts are disabled  
  SPICR1 = 0x5E;
  //set MODFEN to enable SS*
  //no bidirectional behavior
  SPICR2 = 0x10;
  //BR preselect = 7
  //BR  select = 0
  //divisor = (7+1)*(2^0) = 8
  //baud rate  = 8 MHz / 8 = 1 MHz 
  SPIBR = 0x70;
   
}

/* 
  sleepMS - sleep for ms milliseconds
  (note that time is approximate)
*/
void sleepMS(unsigned long ms) {
  unsigned long i;
  
  for (i=0;i<ms;i++) {
    asm {
      PSHX
      LDX #$640
    sleepLoop:
      NOP
      NOP
      DBNE X, sleepLoop
      PULX
    } 
  }
  
}
/* 
  sleepMSTenth - sleep for msTenths * 0.1 milliseconds
  (note that time is approximate)
*/
void sleepMSTenth(unsigned long msTenths) {
  char i;
  
  for (i=0;i<msTenths;i++) {
    asm {
      PSHX
      LDX #$A0
    sleepLoop:
      NOP
      NOP
      DBNE X, sleepLoop
      PULX
    } 
  }
  
}



/* setup.h
 *
 * ECE348, Spring 2015
 * Group C4
 * Brandon Perez bmperez
 * Rohit Banerjee rohitban
 *
 * Target: MC9S12C128
 * CodeWarrior Version: 5.1
 *
 * Created: Sat 25 Apr 2015 07:20:43 PM EDT
 * Last Modified: Thu 07 May 2015 08:42:22 PM EDT
 *
 * This file is the interface for the setup module, which is responsible
 * for initializing all of the components on the MC9S12C128 module and project
 * board correctly.
 */

#ifndef SETUP_H_
#define SETUP_H_

#include "stdint.h"

// The PWM period and initial duty cycle (80%)
#define PWM_PERIOD      0xFF
#define PWM_INIT_DUTY   0xCC

/* setup_ports
 *
 * Configures the ports on the MCU appropiately for this project. See
 * the comments below for the specific configurations.
 *
 * Port T[7:5] drives the column of the LED matrix, T[4:2] the row. Port P[0]
 * outputs the PWM signal that drives the LED's. Port AD[7] is the analog input
 * of the measured ambient brightness of the room. Port B[0] is the pause button
 * input, and Port B[1] is the restart button input.
 */
void setup_ports(void);

/* setup_serial
 *
 * Configures the serial module on the board to properly communicate
 * with the desktop computer.
 *
 * The serial communication is only one-way, the computer transmitting to the
 * board, so only the receiver is enabled. The receiver module generates an
 * interrupt upon receiving a new message. The message format is an 8-bit UART
 * format. The baud rate is 9600.
 */
void setup_serial(void);

/* setup_pwm
 *
 * Configures the PWM module on the board appropiately for this project.
 *
 * The PWM is setup to output over channel 0 (Port P[0]). The PWM signal is
 * positive polarity, with a frequency of 0.5 Mhz (divided from the onboard
 * clock). The PWM is left-aligned, and we don't concatenate it with channel 1.
 * Thus the PWM duty cycle has 8-bit resolution.
 */
void setup_pwm(void);

/* setup_atd
 *
 * Configures the A/D converter on the module appropiately for the project.
 *
 * The A/D converter generates interrupts upon completion. The FIFO feature is
 * disabled, so there is simply a 1-register buffer. There is only one A/D
 * converter used, so we setup a sequence of length 1.
 */
void setup_atd(void);

/* setup_timer
 *
 * Configures the timer on the module appropiately for this project.
 *
 * The timer is configured to genreate an update every 15 ms. This is slightly
 * above what a person's persistance of vision (POV) is for light. Every timer
 * interrupt, the next LED on the matrix is driven, and is held for the timer's
 * period. Timer channel 7 is used to compare the value corresponding to 15 ms,
 * and the timer is reset whenever it reaches the specified value.
 */
void setup_timer(void);

/* setup_watchdog
 *
 * Configures the watchdog timer for this project.
 *
 * The watchdog timer is kicked in the mainloop if all of the watch_flags
 * are set by the timer interrupt, atd interrupt, main loop and sci interrupt.
 * The watchdog timer operates in a non windowed mode
 * and takes 1 second to time out
 */
void setup_watchdog(void);

#endif /* SETUP_H_ */

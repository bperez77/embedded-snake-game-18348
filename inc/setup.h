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
 * Last Modified: TODO: Update
 *
 * This file is the interface for the setup module, which is responsible
 * for initializing all of the components on the MC9S12C128 module and project
 * board correctly.
 */

#ifndef SETUP_H_
#define SETUP_H_

void setup_ports();
void setup_serial();
void setup_pwm();
void setup_atd();
void setup_timer();

#endif /* SETUP_H_ */

/* stdbool.h
 *
 * ECE348, Spring 2015
 * Group C4
 * Brandon Perez bmperez
 * Rohit Banerjee rohitban
 *
 * Target: MC9S12C128
 * CodeWarrior Version: 5.1
 *
 * Created: Fri 24 Apr 2015 04:58:04 PM EDT
 * Last Modified: TODO: Update
 *
 * This file contains the equivalent version of the C standard library's
 * header file stdbool.h. Contains the definition of the boolean type, and
 * the constants true and false.
 */

#ifndef STDBOOL_H_
#define STDBOOL_H_

// Boolean is the smallest possible size
typedef char bool;

// Values of true and false
#define true        ((bool)1)
#define false       ((bool)0)

#endif /* STDBOOL_H_ */

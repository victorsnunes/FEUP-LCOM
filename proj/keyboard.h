#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"


/**
 * @file keyboard.h
 * @brief definition of the functions used to interact with the Keyboard
*/


/**
 * @brief Subscribes keyboard interrupts 
 * @param bit_no number with Keyboard's IRQ line
 * @return 0 on success, 1 otherwise
*/
int keyboard_subscribe_int(uint8_t *bit_no);

/** 
 * @brief Unsubscribes keyboard interrupts 
 * @returns 0 on success, 1 otherwise
 */
int keyboard_unsubscribe_int();

/** 
 * @brief Handles Keyboard interrupts
 */
void keyboard_ih();

/** @brief Reenables the keyboard interrupts 
 * @returns 0 upon success, 1 otherwise
 */
int set_keyboard_default();

#endif

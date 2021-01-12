#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <lcom/lcf.h>


/** @defgroup utils utils
 * @file utils.h
 * @brief definition of helpful functions
 */


/** 
 * @brief Get the least significant bits in a value
 * @param val input 2 byte integer
 * @param lsb Address of memory location to be update with val's LSB
 * @returns 0 upon success, 1 otherwise 
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb);

/** 
 * @brief get the most significant bits in a value
 * @param val input 2 byte integer
 * @param msb Address of memory location to be update with val's MSB
 * @returns 0 upon success, 1 otherwise 
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb);

/** 
 * @brief Invokes sys_inb() system call but reads the value into a uint8_t variable. 
 * @param port The port that is to be read
 * @param value Address of the 8-bit variable to be update with the value read
 * @returns 0 upon success, 1 otherwise 
 */
int (util_sys_inb)(int port, uint8_t *value);

/**
 * @brief Converts a number to binary version in char
 * @param size Size of the number
 * @param n Number to be converted
 */
char * (to_binary)(uint32_t size,uint32_t n);

#endif

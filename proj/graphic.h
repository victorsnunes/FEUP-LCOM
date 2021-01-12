#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <lcom/lcf.h>
#include <stdio.h>
#include <stdbool.h>

#include <minix/driver.h>
#include <sys/mman.h>
#include <machine/int86.h>
#include <math.h>


/** @defgroup graphics graphics
 * @file graphic.h
 * @brief definition of the code used to interact with the video card 
 */


/**
 * @brief initialize mode
 * @param mode 
 */
int init_mode(uint16_t mode);

/**
 * @brief get information about the mode
 * @param mode 
 * @param mode_info information about the mode
 */
int my_get_mode_info(uint16_t mode, vbe_mode_info_t *mode_info);  

/**
 * @brief draw pixels
 * @param x_pos position in the x-axis to draw
 * @param y_pos position in the y-axis to draw
 * @param color color used to draw the pixel 
 */
int drawPixel(uint16_t x_pos, uint16_t y_pos, uint32_t color);

void write_buffer_to_videomem();

#endif

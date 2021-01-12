#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <minix/driver.h>
#include <lcom/lcf.h>
#include <sys/mman.h>
#include <stdio.h>
#include "graphic.h"

/** @defgroup sprite Sprite
 * @file sprite.h
 * @brief Code used to define the implementations of the sprites
 */


/**
 * @brief struct of a sprite
 */
typedef struct {
  int x,y;             /**<@brief current sprite position */
  int width, height;   /**<@brief sprite dimensions */
  int xspeed, yspeed;  /**<@brief current speeds in the x and y direction */
  uint8_t *map;        /**<@brief the sprite pixmap (use read_xpm()) */
} Sprite;


/**
 * @brief creates a new sprite 
 * @param xpm
 * @param x position in the x-axis
 * @param y  position in the y-axis
 * @param xspeed speed in the x-axis
 * @param yspeed speed in the y-axis
 * @return  a pointer to an object of struct Sprite
 */
Sprite *create_sprite(xpm_map_t xpm, int x, int y,int xspeed, int yspeed);

/**
 * @brief  destroy a sprite
 * @param sp sprite to be destroyed
 */
void destroy_sprite(Sprite *sp);

/**
 * @brief draw sprite
 * @param sp sprite to be drawn
 */
void draw_sprite(Sprite* sp);

/**
 * @brief draw sprite and the background
 * @param sp sprite to be drawn
 */
void draw_sprite_and_background(Sprite* sp);

/**
 * @brief draw sprite in such way that it does not appear in the other side next
 * @param sp sprite to be drawn
 */
void draw_sprite_no_packman_effect(Sprite* sp);


/**
 * @brief erase a sprite
 * @param sp sprite to be erased
 */
void erase_sprite(Sprite* sp);

/**
 * @brief move the sprite
 * @param sp sprite to be moved
 */
void move_sprite(Sprite *sp);

/**
 * @brief move the cursor sprite
 * @param sp cursor sprite to be moved
 */
void move_cursor_sprite(Sprite* sp);

/**
 * @brief checks if there was a collision between sp1 and sp2
 * @param sp1 first sprite
 * @param sp2 second sprite 
 * @returns if there was a collision between sp1 and sp2 returns true, false otherwise
 */
bool collition_detection(Sprite *sp1, Sprite *sp2);

/**
 * @brief responsable to set the background
 * @param xpm
 */
void set_background(xpm_map_t xpm);


#endif

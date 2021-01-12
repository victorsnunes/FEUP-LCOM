#ifndef __MUSHROOM_H
#define __MUSHROOM_H

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include <stdlib.h>
#include <time.h>

/** @defgroup mushroom Mushroom
 * @file mushroom.h
 * @brief Code used to define the implementations of the mushrooms
 */

#include "sprite.h"
#include "character.h"

#include "Assets/Mushrooms/brown_mushroom1.xpm"
#include "Assets/Mushrooms/brown_mushroom2.xpm"
#include "Assets/Mushrooms/red_mushroom1.xpm"
#include "Assets/Mushrooms/red_mushroom2.xpm"



/**
 * @brief struct defining the Mushrooms
 */
typedef struct {
  Sprite sprite;   /** <@brief sprite of the mushrooms*/
  bool in_game; /**<@brief return if the mushroom is in the game*/
} Mushroom;

static Sprite* mushroom_sprites[4];  /**<@brief contains the sprite of the mushroom */

#define MAX_MUSHROOMS 5 /**<@brief defines the max number of mushrooms on the screen */

static Mushroom* mushrooms[MAX_MUSHROOMS]; /**<@brief pointer to the array of mushrooms on the game */
 

 /**
 * @brief Initializes the mushroom in the array
 * 
 */
void initialize_mushrooms();

/**
 * @brief Initializes the sprites of the mushrooms
 * 
 */
void initialize_mushroom_sprites();

/**
 * @brief returns if the mushroom is out of range 
 * @param  m is an object of of struct Mushroom 
 * @return true if it is out of range, false otherwise
 */
bool mushroom_out_of_range(Mushroom* m);

/**
 * @brief creates a new mushroom 
 * @return  a pointer to an object of struct Mushroom
 */
Mushroom* create_mushroom();

/**
 * @brief generate a new mushroom, having 3 diferents modes, easy, medium and hard
 * we can't generate it if: The mushroom will take a place where is almost impossible for the 
 * player not to loose OR will be really close to the previous one, causing a bad visual effect
 * @param player_points used to distinguish te level of difficulty the player is.
 */
void mushroom_generator(int player_points);

/**
 * @brief draw mushrooms
 * @param move true if it is moving, false otherwise
 */
void draw_mushrooms(bool move);


/**
 * @brief detects if there was a collision of the character with a mushroom, true if it happened, 1 * otherwise
 * @param character a pointer to an object character from the struct Character
  */
bool mushrooms_collision_detection(Character* character);

/**
 * @brief  take the mushrooms out of the array
 */
void destroy_mushrooms();

/**
 * @brief  destroy the sprites of the mushroom
 */
void destroy_mushroom_sprites();

#endif

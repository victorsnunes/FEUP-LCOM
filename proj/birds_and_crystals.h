#ifndef __BIRDS_AND_CRYSTALS_H
#define __BIRDS_AND_CRYSTALS_H

/**
 * @file birds_and_crystals.h
 * @brief This file contains the definition of the functions to implement the birds flying with crystals that gives the player extra points 
 */

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include <stdlib.h>
#include <time.h>

#include "sprite.h"

#include "Assets/Birds/Regular_Bird/regular_bird_frame1.xpm"
#include "Assets/Birds/Regular_Bird/regular_bird_frame2.xpm"

#include "Assets/Birds/Special_Bird/special_bird_frame1.xpm"
#include "Assets/Birds/Special_Bird/special_bird_frame2.xpm"
#include "Assets/Birds/Special_Bird/special_bird_frame3.xpm"
#include "Assets/Birds/Special_Bird/special_bird_frame4.xpm"

#include "Assets/Crystals/green_crystal.xpm"
#include "Assets/Crystals/red_crystal.xpm"

#include "Assets/Effects/effect1.xpm"
#include "Assets/Effects/effect2.xpm"
#include "Assets/Effects/effect3.xpm"
#include "Assets/Effects/effect4.xpm"
#include "Assets/Effects/effect5.xpm"
#include "Assets/Effects/effect6.xpm"
#include "Assets/Effects/effect7.xpm"
#include "Assets/Effects/effect8.xpm"
#include "Assets/Effects/effect9.xpm"
#include "Assets/Effects/effect10.xpm"
#include "Assets/Effects/effect11.xpm"
#include "Assets/Effects/effect12.xpm"
#include "Assets/Effects/effect13.xpm"
#include "Assets/Effects/effect14.xpm"
#include "Assets/Effects/effect15.xpm"
#include "Assets/Effects/effect16.xpm"
#include "Assets/Effects/effect17.xpm"
#include "Assets/Effects/effect18.xpm"
#include "Assets/Effects/effect19.xpm"
#include "Assets/Effects/effect20.xpm"
#include "Assets/Effects/effect21.xpm"
#include "Assets/Effects/effect22.xpm"
#include "Assets/Effects/effect23.xpm"
#include "Assets/Effects/effect24.xpm"
#include "Assets/Effects/effect25.xpm"
#include "Assets/Effects/effect26.xpm"
#include "Assets/Effects/effect27.xpm"
#include "Assets/Effects/effect28.xpm"
#include "Assets/Effects/effect29.xpm"
#include "Assets/Effects/effect30.xpm"


/**
 * @brief struct defining the Birds
 */
typedef struct {
  Sprite sprite; /**<@brief sprite of the bird*/
  bool in_game; /**<@brief return if the bird is in the game*/
  bool special; /**<@brief return if the bird is special*/
  int frame;    /**<@brief which frame should draw the bird*/
} Bird;


/**
 * @brief struct defining the Crystals
 */
typedef struct {
  Sprite sprite; /**<@brief sprite of the crystals*/
  bool in_game;  /**<@brief return if the crystal is in the game*/
  bool special; /**<@brief return if the crystal is special*/
} Crystal;


/**
 * @brief struct defining the effects
 */
typedef struct {
  Sprite sprite; /**<@brief sprite of the effect*/
  int frame; /**<@brief which frame should draw the effect*/
} Shine_Effect;

static Sprite* regular_bird_sprites[2];    /**<@brief contains the sprite of the regular bird */
static Sprite* special_bird_sprites[4];    /**<@brief contains the the sprite of the special bird*/

static Sprite* greenCrystal;  /**<@brief contains the sprite of the green crystal */
static Sprite* redCrystal;  /**<@brief contains the sprite of the red crystal */

static Sprite* effects_sprites[30];  /**<@brief contains the sprite of the effects */

#define MAX_BIRDS_AND_CRYSTALS 2 /**<@brief defines the max number of birds and crystals on the screen */

static Bird* birds[MAX_BIRDS_AND_CRYSTALS];  /**<@brief pointer to the array of birds of the game */
Crystal* crystals[MAX_BIRDS_AND_CRYSTALS];   /**<@brief pointer to the array of crystals of the game*/
static Shine_Effect* effects[MAX_BIRDS_AND_CRYSTALS]; /**<@brief pointer to the array of effects of the game*/


/**
 * @brief Initializes the birds and the crystals
 * 
 */
void initialize_birds_and_crystals();

/**
 * @brief Initializes the sprites of the birds and the crystals
 * 
 */
void initialize_birds_and_crystals_sprites();

/**
 * @brief returns if the bird is out of range 
 * @param  b is an object of of struct Bird
 * @return true if it is out of range, false otherwise
 */
bool bird_out_of_range(Bird* b);

/**
 * @brief returns if the crystal is out of range 
 * @param  c is an object of struct Crystal 
 * @return true if it is out of range, false otherwise
 */
bool crystal_out_of_range(Crystal* c);

/**
 * @brief creates a new bird 
 * @param  special represents if the bird to be created should be normal or special
 * @return  a pointer to an object of struct Bird
 */
Bird* create_bird(bool special);

/**
 * @brief creates a new crystal 
 * @param  special represents if the crystal to be created should be normal or special
 * @return  a pointer to an object of struct Crystal
 */
Crystal* create_crystal(bool special);

/**
 * @brief generate a new bird with a crystal
 * 
 */
void bird_and_crystal_generator();


/**
 * @brief draw a new bird, called by draw_birds_and_crystals 
 * @param b is a object ofstruct Bird
 * @param move true if it is moving, false otherwise
 */
void draw_bird(Bird* b, bool move);

/**
 * @brief draw bird, crystal and the effects
 * @param move true if it is moving, false otherwise
 */
void draw_birds_and_crystals(bool move);

/**
 * @brief check if the cursor is over the crystal
 * @param x Actual location of the mouse on x-axis
 * @param y Actual location of the mouse on y-axis
 * @param move true if it is moving, false otherwise
 * @return true if the cursor is over the crystal, false otherwise
 */
bool cursor_over_crystal(int x, int y, Crystal* c);

/**
 * @brief  take the crystal of the screen and displays the effects after clicking in the crystal
 * @param c is a object of struct Crystal
 */
void click_on_crystal(Crystal* c);


/**
 * @brief  take the birds and the crystals of the arrays
 */
void destroy_birds_and_crystals();

/**
 * @brief  destroy the sprites of the birds and the crystals
 */
void destroy_birds_and_crystals_sprites();

#endif

#ifndef __SCENARIO_H
#define __SCENARIO_H

// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>


/** @defgroup scenario Scenario
 * @file scenario.h
 * @brief This file contains the definition of implementation of the scenario
 * 
 */

#include "Assets/Scenario/game_background.xpm"
#include "Assets/Scenario/far_trees.xpm"
#include "Assets/Scenario/near_trees.xpm"
#include "Assets/Scenario/ground.xpm"

#include "sprite.h"

Sprite* ground; /**<@brief sprite of the ground*/
Sprite* nearTrees; /**<@brief sprite of the trees near to the character*/
Sprite* farTrees; /**<@brief sprite of  the trees far from the character*/
Sprite* gameBackground; /**<@brief sprite of the game background*/


 /**
 * @brief Initializes the sprites from the scenario
 * 
 */
void initialize_scenario_sprites();

 /**
 * @brief draw the scenario background, calling the draw_sprite() function
 * 
 */
void draw_scenario_background();

/**
 * @brief draw the scenario, if the variable move is true, calls the move_sprite() function, 
 * otherwise it will just draw it normally
 * @param move true if it is moving, false otherwise
 */
void draw_moving_scenario(bool move);


/**
 * @brief  destroy the sprites of the scenario
 */
void destroy_scenario_sprites();

#endif

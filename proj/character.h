#ifndef __CHARACTER_H
#define __CHARACTER_H

/**
 * @file character.h
 * @brief This file contains the definitions of the functions to implement the character  
 */

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "sprite.h"

#include "Assets/Character/Running/run1.xpm"
#include "Assets/Character/Running/run2.xpm"
#include "Assets/Character/Running/run3.xpm"
#include "Assets/Character/Running/run4.xpm"
#include "Assets/Character/Running/run5.xpm"
#include "Assets/Character/Running/run6.xpm"
#include "Assets/Character/Running/run7.xpm"
#include "Assets/Character/Running/run8.xpm"
#include "Assets/Character/Running/run9.xpm"
#include "Assets/Character/Running/run10.xpm"

#include "Assets/Character/Jumping/jump1.xpm"
#include "Assets/Character/Jumping/jump2.xpm"
#include "Assets/Character/Jumping/jump3.xpm"
#include "Assets/Character/Jumping/jump4.xpm"
#include "Assets/Character/Jumping/jump5.xpm"
#include "Assets/Character/Jumping/jump6.xpm"
#include "Assets/Character/Jumping/jump7.xpm"
#include "Assets/Character/Jumping/jump8.xpm"
#include "Assets/Character/Jumping/jump9.xpm"

#include "Assets/Character/Dying/die1.xpm"
#include "Assets/Character/Dying/die2.xpm"
#include "Assets/Character/Dying/die3.xpm"
#include "Assets/Character/Dying/die4.xpm"
#include "Assets/Character/Dying/die5.xpm"
#include "Assets/Character/Dying/die6.xpm"

static Sprite* characterRunning[10]; /**<@brief sprites of the character running*/
static Sprite* characterJumping[30]; /**<@brief sprites of the character jumping*/
static Sprite* characterDying[6];  /**<@brief sprites of the character dying*/


/**
 * @brief enum defining the status of the character
 */
typedef enum {
  RUNNING,
  JUMPING,
  DYING
} CharacterStatus;


/**
 * @brief struct defining the character
 */
typedef struct {
  CharacterStatus status; /**<@brief status of the character*/
  int frame; /**<@brief which frame the character is*/
  Sprite* sprite; /**<@brief sprite of the character*/
} Character;



/**
 * @brief function that initizalizes the sprites of the character
 */
void initialize_character_sprites();

/**
 * @brief function that creates the character
 * @return a pointer to an object of struct Character
 */
Character* create_character();

/**
 * @brief function that initizalizes the sprites of the character running
 * @param character a pointer to an object of Character 
 * @param move if the character will be moving when drawn
 */
void draw_character_running(Character* character, bool move);

/**
 * @brief function that initizalizes the sprites of the character jumping
 * @param character a pointer to an object of Character 
 * @param move if the character will be moving when drawn
 */
void draw_character_jumping(Character* character, bool move);

/**
 * @brief function that initizalizes the sprites of the character dying
 * @param character a pointer to an object of Character 
 */
void draw_character_dying(Character* character);

/**
 * @brief function that initizalizes the sprites of the character 
 * @param character a pointer to an object of Character 
 * @param move if the character will be moving when drawn
 */
void draw_character(Character* character, bool move);

/**
 * @brief  destroy the object character
 * @param character a pointer to an object of Character
 */
void destroy_character(Character* character);

/**
 * @brief  destroy the sprites of the character
 */
void destroy_character_sprites();

#endif

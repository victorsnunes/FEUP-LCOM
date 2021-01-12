#ifndef __EVENTS_H
#define __EVENTS_H

/**
 * @file events.h
 * @brief This file contains the definitions of the functions to implement the event handler
 */


#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "sprite.h"
#include "menu.h"
#include "scenario.h"
#include "character.h"
#include "mouse.h"
#include "mushroom.h"
#include "birds_and_crystals.h"
#include "letters_and_numbers.h"
#include "scoreboard.h"
#include "rtc.h"



/**
 * @brief enum defining the games mode
 */
typedef enum {
  MENU_SCREEN,
  SCOREBOARD_SCREEN,
  INSTRUCTIONS_SCREEN,
  EXIT_SCREEN,
  PLAYING_SCREEN,
  PAUSE_SCREEN,
  QUIT_SCREEN,
  GAMEOVER_SCREEN,
  CLOSE_GAME
} GameModes;  //These are the game states



/**
 * @brief handler of the events, such as the ones from the keyboard, the mouse and the timer for each game modes
 */
void event_handler();

#endif

#ifndef __GAME_H
#define __GAME_H


/**
 * @file game.h
 * @brief This file contains the declarations for the implementations to start the game, containing * the main loop
 */



// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you
#include "i8042.h"
#include "graphic.h"
#include "sprite.h"
#include "timer.h"
#include "keyboard.h"
#include "mouse.h"
#include "scenario.h"
#include "character.h"
#include "mushroom.h"
#include "birds_and_crystals.h"
#include "letters_and_numbers.h"
#include "scoreboard.h"
#include "rtc.h"
#include "menu.h"
#include "events.h"



/**
 * @brief function that initializes all of the sprites and calls the main loop function game_main_loop()
 */
void start_dave_the_jumper();



/**
 * @brief main loop of the game, using the driver receive funtion. 
 * Does the interruptions of the timer, keyboard and mouse. After the interruptions, calls the 
 * event_handler() function if any event happened
 * In the end of the loop, calls all of the 'destroy' functions.
 */
void game_main_loop();

#endif

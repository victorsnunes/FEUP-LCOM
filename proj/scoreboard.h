#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include <string.h>
#include "letters_and_numbers.h"

/** @defgroup scoreboard Scoreboard
 * @file scoreboard.h
 * @brief Code used to define the implementations of the scoreboard
 */


 /**
 * @brief if the points of the player is higher than one from de record_score array, it will be 
 * registered in the array 
 * @param points points made by the player
 * @param name name of the player
 * @param day day of the play
 * @param month month of the play
 * @param year year of the play
 * @param hour hour of the play
 * @param minutes minute of the play
 */
void register_score(int points, char *name, int day, int month, int year, int hours, int minutes);


/**
 * @brief write the top 5 scores in the screen 
 */
void write_top5_in_the_screen();

/**
 * @brief write the scores to a file
 */
void write_scores_to_file();

/**
 * @brief read the scores from a file
 */
void read_scores_from_file();

#endif

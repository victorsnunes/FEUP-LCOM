#ifndef __MENU_H
#define __MENU_H

// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

/**
 * @file menu.h
 * @brief This file contains the definitions of the functions to implement the menus
 */


#include "sprite.h"

#include "Assets/Menu_Screens/start_menu.xpm"
#include "Assets/Menu_Screens/start_menu_singleplayer.xpm"
#include "Assets/Menu_Screens/exit_menu_no.xpm"
#include "Assets/Menu_Screens/instructions_menu.xpm"
#include "Assets/Menu_Screens/exit_window.xpm"
#include "Assets/Menu_Screens/instructions_window.xpm"
#include "Assets/Menu_Screens/scoreboard_window.xpm"
#include "Assets/Menu_Screens/title.xpm"

#include "Assets/Menu_Buttons/blue_button_exit.xpm"
#include "Assets/Menu_Buttons/blue_button_instructions.xpm"
#include "Assets/Menu_Buttons/blue_button_scoreboard.xpm"
#include "Assets/Menu_Buttons/blue_button_multiplayer.xpm"
#include "Assets/Menu_Buttons/blue_button_singleplayer.xpm"
#include "Assets/Menu_Buttons/blue_button_resume.xpm"
#include "Assets/Menu_Buttons/blue_button_quit.xpm"
#include "Assets/Menu_Buttons/blue_small_no.xpm"
#include "Assets/Menu_Buttons/blue_small_yes.xpm"

#include "Assets/Menu_Buttons/orange_button_exit.xpm"
#include "Assets/Menu_Buttons/orange_button_instructions.xpm"
#include "Assets/Menu_Buttons/orange_button_scoreboard.xpm"
#include "Assets/Menu_Buttons/orange_button_multiplayer.xpm"
#include "Assets/Menu_Buttons/orange_button_singleplayer.xpm"
#include "Assets/Menu_Buttons/orange_button_resume.xpm"
#include "Assets/Menu_Buttons/orange_button_quit.xpm"
#include "Assets/Menu_Buttons/orange_small_no.xpm"
#include "Assets/Menu_Buttons/orange_small_yes.xpm"

#include "Assets/Menu_Screens/pause_window.xpm"
#include "Assets/Menu_Screens/quit_window.xpm"
#include "Assets/Menu_Screens/game_over_window.xpm"

#include "Assets/Highscore/highscore.xpm"

static Sprite* menuBackground; /** <@brief sprite of the menu background*/
static Sprite* title; /** <@brief sprite of the title*/
static Sprite* exitWindow; /** <@brief sprite of the exit window*/
static Sprite* instructionsWindow; /** <@brief sprite of the instructions window*/
static Sprite* scoreboardWindow; /** <@brief sprite of the score board window*/

static Sprite* singleplayerBlueButton;   /** <@brief sprite of the singleplayer button in blue*/
static Sprite* scoreboardBlueButton;  /** <@brief sprite of the score board button in blue*/
static Sprite* instructionsBlueButton;  /** <@brief sprite of the instruction board button in blue*/
static Sprite* exitBlueButton;  /** <@brief sprite of the exit button in blue*/
static Sprite* resumeBlueButton;  /** <@brief sprite of the resume button in blue*/
static Sprite* quitBlueButton;  /** <@brief sprite of the quit button in blue*/
static Sprite* yesBlueButton; /** <@brief sprite of the yes button in blue*/
static Sprite* noBlueButton; /** <@brief sprite of the no button in blue*/

static Sprite* singleplayerOrangeButton;   /** <@brief sprite of the singleplayer button in orange*/
static Sprite* scoreboardOrangeButton;  /** <@brief sprite of the score board button in orange*/
static Sprite* instructionsOrangeButton;/** <@brief sprite of the instruction board button in orange*/
static Sprite* exitOrangeButton; /** <@brief sprite of the exit button in orange*/
static Sprite* resumeOrangeButton;   /** <@brief sprite of the resume button in orange*/
static Sprite* quitOrangeButton;  /** <@brief sprite of the quit button in orange*/
static Sprite* yesOrangeButton;  /** <@brief sprite of the yes button in orange*/
static Sprite* noOrangeButton; /** <@brief sprite of the no button in orange*/


static Sprite* pauseWindow; /** <@brief sprite of the pause window*/
static Sprite* quitWindow;  /** <@brief sprite of the quit window*/
static Sprite* gameoverWindow; /**<@brief sprite of the game over window*/

static Sprite* resumeBlueButton;  /** <@brief sprite of the resume button in blue*/
static Sprite* resumeOrangeButton;  /** <@brief sprite of the resume button in orange*/
static Sprite* quitBlueButton;   /** <@brief sprite of the quit button in blue*/
static Sprite* quitOrangeButton; /** <@brief sprite of the quit button in orange*/

static Sprite* highscoreMedal; /** <@brief sprite of the medal of high score*/



/**
 * @brief enum defining the menu options
 */
typedef enum {
	PLAY,
	SCOREBOARD,
	INSTRUCTIONS,
	EXIT
} MenuOptions;



/**
 * @brief enum defining the yes or no options
 */
typedef enum {
	YES,
	NO
} YesNoOptions;



/**
 * @brief enum defining the pause options, such as resume and quit
 */
typedef enum {
	RESUME,
	QUIT
} PauseOptions;

/**
 * @brief initialize the sprites from the menu
 */
void initialize_menu_sprites();

/**
 * @brief draw the menu background
 */
void draw_menu_background();

/**
 * @brief draw the menu buttons
 * @param menu_option object from the struct MenuOptions
 */
void draw_menu_buttons(MenuOptions menu_option);

/**
 * @brief draw the menu title
 */
void draw_menu_title();

/**
 * @brief draw the score board window
 */
void draw_scoreboard_window();

/**
 * @brief draw the instructions window
 */
void draw_instructions_window();

/**
 * @brief draw the exit window
 */
void draw_exit_window();

/**
 * @brief draw the yes and no buttons
 * @param exit_option object from the struct YesNoOptions
 */
void draw_yes_no_buttons(YesNoOptions exit_option);

/**
 * @brief draw the pause window
 */
void draw_pause_window();

/**
 * @brief draw the pause button
 * @param pause_option object from the struct PauseOptions
 */
void draw_pause_buttons(PauseOptions pause_option);

/**
 * @brief draw the quit window
 */
void draw_quit_window();

/**
 * @brief draw the game over window
 */
void draw_gameover_window();

/**
 * @brief draw the highscore medal if the variable points is bigger than the one in the first 
 * position on the record_points array
 * @param points contains the points made by the player
 */
void draw_highscore_medal(int points);


/**
 * @brief erase the scoreboard menu
 */
void erase_scoreboard_menu();

/**
 * @brief erase the instructions menu
 */
void erase_instructions_menu();

/**
 * @brief erase the exit menu
 */
void erase_exit_menu();

/**
 * @brief erase the pause window
 */
void erase_pause_window();

/**
 * @brief erase the quit window
 */
void erase_quit_window();

/**
 * @brief erase the game over window
 */
void erase_gameover_window();

/**
 * @brief destroy the menu sprites
 */
void destroy_menu_sprites();

#endif

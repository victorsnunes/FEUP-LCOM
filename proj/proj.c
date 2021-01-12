// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you
#include "game.h"


/**
 * @file proj.c
 * @brief This file contains the main loop of the game
 */


//Interruptions masks
uint8_t timer_mask_int = 0;    /**<@brief mask to the timer interrupt*/
uint8_t keyboard_mask_int = 1; /**<@brief  mask to the keyboard interrupt*/
uint8_t mouse_mask_int = 2;   /**<@brief  mask to the mouse interrupt*/

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

/**
 * @brief This function is responsible to call the function that starts the game, 
 * start_dave_the_jumper(). 
 * Is also responsable to subscribe and unsubscribe the timer, keyboard and mouse.
 */
int(proj_main_loop)(int argc, char *argv[]) {

  vg_init(0x115);

  //Subscring the needed devices
  if (timer_subscribe_int(&timer_mask_int) != OK) return 1;
  if (keyboard_subscribe_int(&keyboard_mask_int) != OK) return 2;
  if (mouse_subscribe_int(&mouse_mask_int) != OK) return 3;

  if (mouse_write(ENABLE_DATA_REPORT) != OK) return 5;


  //Starts the game and only close when the player quit the game
  start_dave_the_jumper();

  //Unsubscribing all the devices
  if (timer_unsubscribe_int() != OK) return 1;
  if (keyboard_unsubscribe_int() != OK) return 2;
  if (mouse_unsubscribe_int() != OK) return 3;

  if (mouse_write(DISABLE_DATA_REPORT) != OK) return 4;

  if (vg_exit() != OK) return 3;

  return 0;
}

#include "game.h"

/**
 * @file game.c
 * @brief This file contains the implementation to start the game, containing the main loop
 */


//Global variable for the Timer
extern int timer_counter;

//Global variables for the Keyboard
extern uint8_t keyScanned;

//Global variables for events
bool timer_event_occurred = false;
bool keyboard_event_occurred = false; 
bool mouse_event_occurred = false; 

uint8_t key_pressed;

//Global variables for interruption masks
extern uint8_t timer_mask_int;     /**<@brief mask to the timer interrupt*/
extern uint8_t keyboard_mask_int; /**<@brief  mask to the keyboard interrupt*/
extern uint8_t mouse_mask_int;    /**<@brief  mask to the mouse interrupt*/

extern GameModes game_mode;  /**<@brief contain the game mode*/


Character* dave = NULL;

Cursor* cursor;

void start_dave_the_jumper() {

  initialize_menu_sprites();
  initialize_mouse_sprites();
  initialize_scenario_sprites();
  initialize_character_sprites();
  initialize_mushroom_sprites();
  initialize_birds_and_crystals_sprites();
  initialize_letters_and_numbers_sprites();

  read_scores_from_file();

  cursor = create_cursor();

  game_main_loop();

}

void game_main_loop() {

  int ipc_status;
  int r;
  message msg;

  keyScanned = 0x00;
  bool twoBytesScancode = false;

  printf("\n\nChoose your game mode ?\n\n");

  while(game_mode != CLOSE_GAME) { 
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) 
    { 
      switch (_ENDPOINT_P(msg.m_source)) 
      {
        case HARDWARE: 

          //TIMER INTERRUPTIONS
          if (msg.m_notify.interrupts & timer_mask_int)
          {
            timer_int_handler();
            if (timer_counter % 2 == 0) {
              timer_event_occurred = true;
              timer_counter = 0;
            }
          }

          //MOUSE INTERRUPTIONS
          if (msg.m_notify.interrupts & mouse_mask_int)
          {
            mouse_ih();

            if (mouse_bytes_loaded()) {
              update_cursor(cursor);
              mouse_event_occurred = true;
            }
          }

          //KEYBOARD INTERRUPTIONS
          if (msg.m_notify.interrupts & keyboard_mask_int) 
          {
            keyboard_ih();

            if (twoBytesScancode) {
              key_pressed = keyScanned;
              keyboard_event_occurred = true;

              twoBytesScancode = false;
            }

            else if (keyScanned == TWO_BYTES_SCANCODE) {
              twoBytesScancode = true;
            }
            
            else if (keyScanned != TWO_BYTES_SCANCODE)
            {
              key_pressed = keyScanned;
              keyboard_event_occurred = true;
            }
          }
          
          break;

        default:
          break;
      }
    } 
    else {}

    if (timer_event_occurred || keyboard_event_occurred || mouse_event_occurred)
      event_handler();
  }

  destroy_mushrooms();
  destroy_mushroom_sprites();
  destroy_birds_and_crystals();
  destroy_birds_and_crystals_sprites();
  destroy_letters_and_numbers_sprites();
  destroy_character(dave);
  destroy_cursor(cursor);
  destroy_mouse_sprites();
  destroy_character_sprites();
  destroy_scenario_sprites();
  destroy_menu_sprites();

}

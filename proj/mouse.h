#ifndef __MOUSE_H
#define __MOUSE_H

#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "Assets/Mouse_Cursor/cursor.xpm"
#include "Assets/Mouse_Cursor/hand_cursor.xpm"

#include "i8042.h"
#include "sprite.h"



/** @defgroup mouse Mouse
 * @file mouse.h
 * @brief Code used to interact with the Mouse 
 */

static Sprite* regular_cursor;  /** <@brief sprite of the regular moving cursor*/
static Sprite* hand_cursor;  /** <@brief sprite of the hand selection cursor*/



/**
 * @brief struct defining the Cursor
 */
typedef struct {
  Sprite* sprite;   /** <@brief sprite of the cursor*/

  bool hand_mode;    /** <@brief true if it is in hand mode, false if it is in regular mode*/

  bool lb;   /** <@brief contains the information about the left button*/
  bool rb;  /** <@brief contains the information about the right button*/
  bool mb;   /** <@brief contains the information about the middle button*/

  bool x_ov;  /** <@brief contains the information if the x-axis overflowed*/
  bool y_ov;  /** <@brief contains the information if the y-axis overflowed*/
} Cursor;


/** 
 * @brief Susbcribes mouse interrupts 
 * @param bit_no Mask with Mouse's IRQ line
 * @returns 0 on success, 1 otherwise
 */
int mouse_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubcribes mouse interrupts
 * @returns 0 on success, 1 otherwise
 */
int mouse_unsubscribe_int();

/** 
 * @brief Handles mouse interrutps.
 */
void(mouse_ih)();

/**
 * @brief returns true if the bytes were loaded, false otherwise
 * @returns if the bytes were loaded
 */
bool mouse_bytes_loaded();

/** 
 * @brief issue a command to the mouse
 * @param cmd command to be sent
 * @returns 0 on success, non-zero otherwise
 */
int mouse_write(uint8_t cmd);

/**
 * @brief issues a command to the kbc
 * @param port address where the command will be written
 * @param cmd command to be sent
 * @returns 0 on success, 1 otherwise
 */
int kbc_write(int port, uint8_t cmd);

/** 
 * @brief initializes the mouse's sprites
 */
void initialize_mouse_sprites();

/** 
 * @brief create the cursor
 * @returns a pointer to an object from the struct Cursor
 */
Cursor* create_cursor();

/** 
 * @brief update the cursor
 * @param c is an object from the struct Cursor
 */
void update_cursor(Cursor* c);

/** 
 * @brief draw the cursor
 * @param c is an object from the struct Cursor
 */
void draw_cursor(Cursor* c);

/** 
 * @brief change the cursor to hand mode
 * @param c is an object from the struct Cursor
 */
void become_hand_cursor(Cursor* c);

/** 
 * @brief change the cursor to regular mode
 * @param c is an object from the struct Cursor
 */
void become_regular_cursor(Cursor* c);

/** 
 * @brief destroy the sprite from the cursor given
 * @param c is an object from the struct Cursor
 */
void destroy_cursor(Cursor* c);

/** 
 * @brief destroy the sprite from the mouse
 */
void destroy_mouse_sprites();



#endif

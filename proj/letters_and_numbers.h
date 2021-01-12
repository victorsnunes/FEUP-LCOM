#ifndef __LETTERS_AND_NUMBERS_H
#define __LETTERS_AND_NUMBERS_H


/**
 * @file letters_and_numbers.h
 * @brief This file contains the definition of implementation for the letters and numbers used
 */



#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "sprite.h"
#include "i8042.h"

#include "Assets/Numbers/0.xpm"
#include "Assets/Numbers/1.xpm"
#include "Assets/Numbers/2.xpm"
#include "Assets/Numbers/3.xpm"
#include "Assets/Numbers/4.xpm"
#include "Assets/Numbers/5.xpm"
#include "Assets/Numbers/6.xpm"
#include "Assets/Numbers/7.xpm"
#include "Assets/Numbers/8.xpm"
#include "Assets/Numbers/9.xpm"
#include "Assets/Numbers/points.xpm"

#include "Assets/Alphabet/a.xpm"
#include "Assets/Alphabet/b.xpm"
#include "Assets/Alphabet/c.xpm"
#include "Assets/Alphabet/d.xpm"
#include "Assets/Alphabet/e.xpm"
#include "Assets/Alphabet/f.xpm"
#include "Assets/Alphabet/g.xpm"
#include "Assets/Alphabet/h.xpm"
#include "Assets/Alphabet/i.xpm"
#include "Assets/Alphabet/j.xpm"
#include "Assets/Alphabet/k.xpm"
#include "Assets/Alphabet/l.xpm"
#include "Assets/Alphabet/m.xpm"
#include "Assets/Alphabet/n.xpm"
#include "Assets/Alphabet/o.xpm"
#include "Assets/Alphabet/p.xpm"
#include "Assets/Alphabet/q.xpm"
#include "Assets/Alphabet/r.xpm"
#include "Assets/Alphabet/s.xpm"
#include "Assets/Alphabet/t.xpm"
#include "Assets/Alphabet/u.xpm"
#include "Assets/Alphabet/v.xpm"
#include "Assets/Alphabet/w.xpm"
#include "Assets/Alphabet/x.xpm"
#include "Assets/Alphabet/y.xpm"
#include "Assets/Alphabet/z.xpm"
#include "Assets/Alphabet/spacebar.xpm"
#include "Assets/Alphabet/colon.xpm"
#include "Assets/Alphabet/slash.xpm"
#include "Assets/Alphabet/hyphen.xpm"


static Sprite* points;  /** <@brief sprite of the points*/
static Sprite* points_cleaner;
static Sprite* numbers[10];    /** <@brief sprite of the number*/

static Sprite* letters[26];   /** <@brief sprite of the letters*/
static Sprite* special_chars[4];  /** <@brief sprite of the special chars*/


/**
 * @brief function that initializes the sprites for the letters and numbers
 */
void initialize_letters_and_numbers_sprites();

/**
 * @brief function that erase the points displayed
 */
void erase_points_word();

/**
 * @brief function that draw the points 
 */
void draw_points_word();

/**
 * @brief function that draw the points 
 * @param number_points total points the player made
 * @param x_initial initial position of the number
 * @param x_final centralized position 
 * @param y position on the y-axis
 */
void draw_number_centralized(int number_points, int x_initial, int x_final, int y);

/**
 * @brief function that draw the points 
 * @param word word to be written 
 * @param x_initial  initial position of the word
 * @param x_final centralized position 
 * @param y position on the y-axis
 */
void draw_word_centralized(char* word, int x_initial, int x_final, int y);


/**
 * @brief function that writes a letter
 * @param letter letter to be written 
 */
void name_write_char(char letter);


/**
 * @brief function that delete letters
 */
void name_delete_char();

/**
 * @brief function that destroy the letters and numbers sprites
 */
void destroy_letters_and_numbers_sprites();

#endif

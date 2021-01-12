#include "letters_and_numbers.h"


/**
 * @file letters_and_numbers.c
 * @brief This file contains the implementation of the letters and numbers used
 */



extern char player_name[11]; /** <@brief contains the name of the playes, with a maximun of 11 letters*/

void initialize_letters_and_numbers_sprites() {
  
  points = create_sprite(points_xpm, 696, 12, 0, 0);
  points_cleaner = create_sprite(points_xpm, 696, 45, 0, 0);

  numbers[0] = create_sprite(zero_xpm, 0, 0, 0, 0);
  numbers[1] = create_sprite(one_xpm, 0, 0, 0, 0);
  numbers[2] = create_sprite(two_xpm, 0, 0, 0, 0);
  numbers[3] = create_sprite(three_xpm, 0, 0, 0, 0);
  numbers[4] = create_sprite(four_xpm, 0, 0, 0, 0);
  numbers[5] = create_sprite(five_xpm, 0, 0, 0, 0);
  numbers[6] = create_sprite(six_xpm, 0, 0, 0, 0);
  numbers[7] = create_sprite(seven_xpm, 0, 0, 0, 0);
  numbers[8] = create_sprite(eight_xpm, 0, 0, 0, 0);
  numbers[9] = create_sprite(nine_xpm, 0, 0, 0, 0);

  letters[0] = create_sprite(a_xpm, 0, 0, 0, 0);
  letters[1] = create_sprite(b_xpm, 0, 0, 0, 0);
  letters[2] = create_sprite(c_xpm, 0, 0, 0, 0);
  letters[3] = create_sprite(d_xpm, 0, 0, 0, 0);
  letters[4] = create_sprite(e_xpm, 0, 0, 0, 0);
  letters[5] = create_sprite(f_xpm, 0, 0, 0, 0);
  letters[6] = create_sprite(g_xpm, 0, 0, 0, 0);
  letters[7] = create_sprite(h_xpm, 0, 0, 0, 0);
  letters[8] = create_sprite(i_xpm, 0, 0, 0, 0);
  letters[9] = create_sprite(j_xpm, 0, 0, 0, 0);
  letters[10] = create_sprite(k_xpm, 0, 0, 0, 0);
  letters[11] = create_sprite(l_xpm, 0, 0, 0, 0);
  letters[12] = create_sprite(m_xpm, 0, 0, 0, 0);
  letters[13] = create_sprite(n_xpm, 0, 0, 0, 0);
  letters[14] = create_sprite(o_xpm, 0, 0, 0, 0);
  letters[15] = create_sprite(p_xpm, 0, 0, 0, 0);
  letters[16] = create_sprite(q_xpm, 0, 0, 0, 0);
  letters[17] = create_sprite(r_xpm, 0, 0, 0, 0);
  letters[18] = create_sprite(s_xpm, 0, 0, 0, 0);
  letters[19] = create_sprite(t_xpm, 0, 0, 0, 0);
  letters[20] = create_sprite(u_xpm, 0, 0, 0, 0);
  letters[21] = create_sprite(v_xpm, 0, 0, 0, 0);
  letters[22] = create_sprite(w_xpm, 0, 0, 0, 0);
  letters[23] = create_sprite(x_xpm, 0, 0, 0, 0);
  letters[24] = create_sprite(y_xpm, 0, 0, 0, 0);
  letters[25] = create_sprite(z_xpm, 0, 0, 0, 0);

  special_chars[0] = create_sprite(spacebar_xpm, 0, 0, 0, 0);
  special_chars[1] = create_sprite(colon_xpm, 0, 0, 0, 0);
  special_chars[2] = create_sprite(slash_xpm, 0, 0, 0, 0);
  special_chars[3] = create_sprite(hyphen_xpm, 0, 0, 0, 0);

}


void erase_points_word() {
  erase_sprite(points_cleaner);
}

void draw_points_word() {
  draw_sprite(points);
}

void draw_number_centralized(int number_points, int x_initial, int x_final, int y) {

  //Sprite of the digits: thousands, hundreds, tens, untis
  Sprite number_to_print[4];

  //Overflow (rare to get so many points)
  if (number_points > 9999) number_points = 9999;

  int numberLength = 4;
  int numberWidth = 0;
  int tmp = 1000;
  for (int i = 0; i < 4; i++) {

    int digit = number_points / tmp;
    number_points %= tmp;
    tmp /= 10;

    number_to_print[i] = *numbers[digit];

    //Zero digit at the most significant position, we don't count it
    if ((digit == 0) && (i + numberLength == 4) && (i != 3) ) {
      numberLength--;
    }
    //Otherwise, we count it
    else {
      numberWidth += number_to_print[i].width;
    }
  }

  int x = (x_initial + x_final - numberWidth) / 2;

  for (int i = 4 - numberLength; i < 4; i++) {
    number_to_print[i].y = y;
    number_to_print[i].x = x;
    draw_sprite(&number_to_print[i]);
    x += number_to_print[i].width;
  }

}

void draw_word_centralized(char* word, int x_initial, int x_final, int y) {

  //Sprites of the letters of the word (16 is the max string length we'll need in this game)
  Sprite word_to_print[16];

  int wordLength = 0;
  int wordWidth = 0;
  for (int i = 0; word[i] != '\0'; i++) {

    int char_ascii = word[i];

    //Char is a regular lowercase letter
    if (char_ascii > 96 && char_ascii < 123)
      word_to_print[i] = *letters[char_ascii - 97];

    //Char is a number
    if (char_ascii > 47 && char_ascii < 58)
      word_to_print[i] = *numbers[char_ascii - 48];

    //Char is a spacebar
    if (char_ascii == 32)
      word_to_print[i] = *special_chars[0];

    //Char is a colon
    if (char_ascii == 58)
      word_to_print[i] = *special_chars[1];

    //Char is a forward slash
    if (char_ascii == 47)
      word_to_print[i] = *special_chars[2];

    //Char is a hyphen
    if (char_ascii == 45)
      word_to_print[i] = *special_chars[3];

    
    wordWidth += word_to_print[i].width;
    wordLength++;
  }

  int x = (x_initial + x_final - wordWidth) / 2;

  for (int i = 0; i < wordLength; i++) {
    word_to_print[i].y = y;
    word_to_print[i].x = x;
    draw_sprite(&word_to_print[i]);
    x += word_to_print[i].width;
  }

}

void name_write_char(char letter) {

  int i;
  for(i = 0; player_name[i] != '\0'; i++);

  //Don't write if string name is full
  if (i < 10) {
    player_name[i] = letter;
    player_name[i + 1] = '\0';
  }

}

void name_delete_char() {

  int i;
  for(i = 0; player_name[i] != '\0'; i++);

  //Don't delete nothing if string name is empty
  if (i != 0) {
    player_name[i - 1] = '\0';
  }
}

void destroy_letters_and_numbers_sprites() {

  destroy_sprite(points);
  destroy_sprite(points_cleaner);

  for (int i = 0; i < 26; i++) {

    destroy_sprite(letters[i]);
    if (i < 10)
      destroy_sprite(numbers[i]);
    if (i < 4)
      destroy_sprite(special_chars[i]);

  }
}

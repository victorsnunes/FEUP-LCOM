#include "menu.h"
/**
 * @file menu.c
 * @brief This file contains the implementaion of the menus
 */


extern int record_points[5];  /**<@brief global variable that keep the 5 record scores*/

void initialize_menu_sprites() {
  
  menuBackground = create_sprite(start_menu_xpm, 0, 0, 0, 0);
  title = create_sprite(title_xpm, 259, 20, 0, 0);
  exitWindow = create_sprite(exit_window_xpm, 301, 197, 0, 0);
  instructionsWindow = create_sprite(instructions_window_xpm, 75, 40, 0, 0);
  scoreboardWindow = create_sprite(scoreboard_window_xpm, 87, 103, 0, 0);

  singleplayerBlueButton = create_sprite(blue_button_singleplayer_xpm, 296, 243, 0, 0);
  scoreboardBlueButton = create_sprite(blue_button_scoreboard_xpm, 296, 305, 0, 0);
  instructionsBlueButton = create_sprite(blue_button_instructions_xpm, 296, 366, 0, 0);
  exitBlueButton = create_sprite(blue_button_exit_xpm, 296, 541, 0, 0);
  resumeBlueButton = create_sprite(blue_button_resume_xpm, 337, 292, 0, 0);
  quitBlueButton = create_sprite(blue_button_quit_xpm, 337, 333, 0, 0);
  yesBlueButton = create_sprite(blue_small_yes_xpm, 333, 250, 0, 0);
  noBlueButton = create_sprite(blue_small_no_xpm, 333, 286, 0, 0);
  
  singleplayerOrangeButton = create_sprite(orange_button_singleplayer_xpm, 296, 243, 0, 0);
  scoreboardOrangeButton = create_sprite(orange_button_scoreboard_xpm, 296, 305, 0, 0);
  instructionsOrangeButton = create_sprite(orange_button_instructions_xpm, 296, 366, 0, 0);
  exitOrangeButton = create_sprite(orange_button_exit_xpm, 296, 541, 0, 0);
  resumeOrangeButton = create_sprite(orange_button_resume_xpm, 337, 292, 0, 0);
  quitOrangeButton = create_sprite(orange_button_quit_xpm, 337, 333, 0, 0);
  yesOrangeButton = create_sprite(orange_small_yes_xpm, 333, 250, 0, 0);
  noOrangeButton = create_sprite(orange_small_no_xpm, 333, 286, 0, 0);

  pauseWindow = create_sprite(pause_window_xpm, 268, 216, 0, 0);
  quitWindow = create_sprite(quit_window_xpm, 301, 197, 0, 0);

  gameoverWindow = create_sprite(game_over_window_xpm, 225, 125, 0, 0);
  highscoreMedal = create_sprite(highscore_xpm, 501, 108, 0, 0);

}

void draw_menu_background() {
  
  draw_sprite(menuBackground);

}

void draw_menu_buttons(MenuOptions menu_option) {

  draw_sprite(singleplayerBlueButton);
  draw_sprite(scoreboardBlueButton);
  draw_sprite(instructionsBlueButton);
  draw_sprite(exitBlueButton);

  switch (menu_option)
  {
    case PLAY:
      draw_sprite(singleplayerOrangeButton);
      break;

    case SCOREBOARD:
      draw_sprite(scoreboardOrangeButton);
      break;

    case INSTRUCTIONS:
      draw_sprite(instructionsOrangeButton);
      break;

    case EXIT:
      draw_sprite(exitOrangeButton);
      break;

    default:
      break;
  }
}

void draw_menu_title() {
  draw_sprite(title);
}

void draw_scoreboard_window() {

  erase_sprite(title);
  erase_sprite(instructionsBlueButton);
  erase_sprite(exitBlueButton);
  draw_sprite(scoreboardWindow);

}

void draw_instructions_window() {

  erase_sprite(title);
  erase_sprite(instructionsBlueButton);
  erase_sprite(exitBlueButton);
  erase_sprite(exitBlueButton);
  draw_sprite(instructionsWindow);

}

void draw_exit_window() {

  erase_sprite(title);
  erase_sprite(singleplayerBlueButton);
  erase_sprite(scoreboardBlueButton);
  erase_sprite(instructionsBlueButton);
  erase_sprite(exitBlueButton);
  draw_sprite(exitWindow);

}

void draw_yes_no_buttons(YesNoOptions exit_option) {

  switch(exit_option)
  {
    case YES:
      draw_sprite(yesOrangeButton);
      draw_sprite(noBlueButton);
      break;

    case NO:
      draw_sprite(yesBlueButton);
      draw_sprite(noOrangeButton);
      break;

    default:
      break;
  }
}


void draw_pause_window() {
  draw_sprite(pauseWindow);
}

void draw_pause_buttons(PauseOptions pause_option) {

  switch(pause_option)
  {
    case RESUME:
      draw_sprite(resumeOrangeButton);
      draw_sprite(quitBlueButton);
      break;

    case QUIT:
      draw_sprite(resumeBlueButton);
      draw_sprite(quitOrangeButton);
      break;

    default:
      break;
  }
}

void draw_quit_window() {
  draw_sprite(quitWindow);
}

void draw_gameover_window() {
  draw_sprite(gameoverWindow);
}

void draw_highscore_medal(int points) {

  if (points > record_points[0])
    draw_sprite(highscoreMedal);
}


void erase_scoreboard_menu() {
  erase_sprite(scoreboardWindow);
  draw_sprite(title);
}

void erase_instructions_menu() {
  erase_sprite(instructionsWindow);
  draw_sprite(title);
}

void erase_exit_menu() {
  erase_sprite(exitWindow);
  draw_sprite(title);
}

void erase_pause_window() {
  erase_sprite(pauseWindow);
}

void erase_quit_window() {
  erase_sprite(quitWindow);
}

void erase_gameover_window() {
  erase_sprite(gameoverWindow);
  erase_sprite(highscoreMedal);
}

void destroy_menu_sprites() {

  destroy_sprite(menuBackground);
  destroy_sprite(title);
  destroy_sprite(exitWindow);
  destroy_sprite(instructionsWindow);
  destroy_sprite(scoreboardWindow);

  destroy_sprite(singleplayerBlueButton);
  destroy_sprite(scoreboardBlueButton);
  destroy_sprite(instructionsBlueButton);
  destroy_sprite(exitBlueButton);
  destroy_sprite(resumeBlueButton);
  destroy_sprite(quitBlueButton);
  destroy_sprite(yesBlueButton);
  destroy_sprite(noBlueButton);

  destroy_sprite(singleplayerOrangeButton);
  destroy_sprite(scoreboardOrangeButton);
  destroy_sprite(instructionsOrangeButton);
  destroy_sprite(exitOrangeButton);
  destroy_sprite(resumeOrangeButton);
  destroy_sprite(quitOrangeButton);
  destroy_sprite(yesOrangeButton);
  destroy_sprite(noOrangeButton);

  destroy_sprite(pauseWindow);
  destroy_sprite(quitWindow);
  destroy_sprite(gameoverWindow);
  destroy_sprite(highscoreMedal);

}

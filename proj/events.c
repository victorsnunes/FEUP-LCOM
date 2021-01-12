#include "events.h"

/**
 * @file events.c
 * @brief This file contains the implementaion of the events handler
 */


//Variables from game.c
extern bool timer_event_occurred; /**<@brief says if an event from the timer happened*/
extern bool keyboard_event_occurred; /**<@brief says if an event from the keyboard happened*/
extern bool mouse_event_occurred; /**<@brief says if an event from the mouse happened*/

//Variables from rtc.c
extern uint8_t player_day; /**<@brief represents the day, given by the rtc*/
extern uint8_t player_month; /**<@brief represents the month, given by the rtc*/
extern uint8_t player_year; /**<@brief represents the year, given by the rtc*/
extern uint8_t player_hour; /**<@brief represents the hour, given by the rtc*/
extern uint8_t player_minute; /**<@brief represents the minutes, given by the rtc*/

extern uint8_t key_pressed;
extern struct packet mouse_packet;

static bool base_background_loaded = false;

GameModes game_mode = MENU_SCREEN; /**<@brief initiates the game mode with the main menu screen*/
static MenuOptions menu_option = PLAY;
static PauseOptions pause_option = RESUME;
static YesNoOptions yes_no_option = NO;

extern Character* dave;

extern Cursor* cursor;

extern Crystal* crystals[MAX_BIRDS_AND_CRYSTALS]; //Crystals of the game (extern from birds_and_crystals.h)

//In game variables
unsigned int p_counter = 0;
unsigned int player_points = 0; /**<@brief contains the points of the player */
char player_name[11] = ""; /**<@brief contains the name of the player*/

unsigned int dead_timer = 0; //Counting before the loose window appears

void event_handler() {

  //KEYBOARD EVENTS
  if (keyboard_event_occurred)
  {
    switch (game_mode)
    {

      case MENU_SCREEN:

        switch(key_pressed)
        {
          case UP_ARROW:
          case W:

            if (menu_option == PLAY) menu_option = EXIT;
            else menu_option = (menu_option - 1) % 4;
            break;

          case DOWN_ARROW:
          case S:
          
            menu_option = (menu_option + 1) % 4;
            break;

          case ENTER:
            switch (menu_option)
            {
              case PLAY:
                dave = create_character();
                game_mode = PLAYING_SCREEN;
                player_points = 0;
                p_counter = 0;
                player_name[0] = '\0';
                base_background_loaded = false;
                break;
              
              case SCOREBOARD:
                game_mode = SCOREBOARD_SCREEN;
                break;

              case INSTRUCTIONS:
                game_mode = INSTRUCTIONS_SCREEN;
                break;

              case EXIT:
                game_mode = EXIT_SCREEN;
                break;

              default:
                break;
            }
            break;

          default:
            break;
        }

        break;

      case SCOREBOARD_SCREEN:

        if (key_pressed == ESC)
        {
          erase_scoreboard_menu();
          game_mode = MENU_SCREEN;
        }

        break;

      case INSTRUCTIONS_SCREEN:

        if (key_pressed == ESC)
        {
          erase_instructions_menu();
          game_mode = MENU_SCREEN;
        }

        break;

      case EXIT_SCREEN:

        if (key_pressed == UP_ARROW || key_pressed == W || key_pressed == DOWN_ARROW || key_pressed == S)
        {
          if (yes_no_option == YES) yes_no_option = NO;
          else yes_no_option = YES;
        }

        if (key_pressed == ENTER)
        {
          if (yes_no_option == YES){
            game_mode = CLOSE_GAME;
          }

          if (yes_no_option == NO)
          {
            erase_exit_menu();
            game_mode = MENU_SCREEN;
          }
        }

        break;

      case PLAYING_SCREEN:

        if (dave->status == RUNNING)
        {
          if (key_pressed == SPACEBAR)
          {
            dave->status = JUMPING;
            dave->frame = 0;
          }
        }

        if (dave->status != DYING)
        {
          if (key_pressed == ESC)
          {
            game_mode = PAUSE_SCREEN;
          }
        }

        break;

      case PAUSE_SCREEN:

        if (key_pressed == UP_ARROW || key_pressed == W || key_pressed == DOWN_ARROW || key_pressed == S)
        {
          if (pause_option == RESUME) pause_option = QUIT;
          else pause_option = RESUME;
        }

        if (key_pressed == ENTER)
        {
          switch(pause_option)
          {
            case RESUME:
              erase_pause_window();
              game_mode = PLAYING_SCREEN;
              break;

            case QUIT:
              erase_pause_window();
              game_mode = QUIT_SCREEN;
              break;

            default:
              break;
          }
        }

        if (key_pressed == ESC)
        {
          erase_pause_window();
          game_mode = PLAYING_SCREEN;
        }

        break;

      case QUIT_SCREEN:

        if (key_pressed == UP_ARROW || key_pressed == W || key_pressed == DOWN_ARROW || key_pressed == S)
        {
          if (yes_no_option == YES) yes_no_option = NO;
          else yes_no_option = YES;
        }

        if (key_pressed == ENTER)
        {
          if (yes_no_option == YES){

            game_mode = MENU_SCREEN;
            destroy_mushrooms();
            initialize_mushrooms();
            destroy_birds_and_crystals();
            initialize_birds_and_crystals();
            destroy_character(dave);
            player_points = 0;
            p_counter = 0;
            player_name[0] = '\0';
            base_background_loaded = false;
            
          }

          if (yes_no_option == NO)
          {
            erase_quit_window();
            game_mode = PAUSE_SCREEN;
          }
        }

        if (key_pressed == ESC)
        {
          erase_quit_window();
          game_mode = PAUSE_SCREEN;
        }

        break;

      case GAMEOVER_SCREEN:


        if (key_pressed == A) name_write_char('a');
        if (key_pressed == B) name_write_char('b');
        if (key_pressed == C) name_write_char('c');
        if (key_pressed == D) name_write_char('d');
        if (key_pressed == E) name_write_char('e');
        if (key_pressed == F) name_write_char('f');
        if (key_pressed == G) name_write_char('g');
        if (key_pressed == H) name_write_char('h');
        if (key_pressed == I) name_write_char('i');
        if (key_pressed == J) name_write_char('j');
        if (key_pressed == K) name_write_char('k');
        if (key_pressed == L) name_write_char('l');
        if (key_pressed == M) name_write_char('m');
        if (key_pressed == N) name_write_char('n');
        if (key_pressed == O) name_write_char('o');
        if (key_pressed == P) name_write_char('p');
        if (key_pressed == Q) name_write_char('q');
        if (key_pressed == R) name_write_char('r');
        if (key_pressed == S) name_write_char('s');
        if (key_pressed == T) name_write_char('t');
        if (key_pressed == U) name_write_char('u');
        if (key_pressed == V) name_write_char('v');
        if (key_pressed == W) name_write_char('w');
        if (key_pressed == X) name_write_char('x');
        if (key_pressed == Y) name_write_char('y');
        if (key_pressed == Z) name_write_char('z');

        if (key_pressed == ZERO1 || key_pressed == ZERO2) name_write_char('0');
        if (key_pressed == ONE1 || key_pressed == ONE2) name_write_char('1');
        if (key_pressed == TWO1 || key_pressed == TWO2) name_write_char('2');
        if (key_pressed == THREE1 || key_pressed == THREE2) name_write_char('3');
        if (key_pressed == FOUR1 || key_pressed == FOUR2) name_write_char('4');
        if (key_pressed == FIVE1 || key_pressed == FIVE2) name_write_char('5');
        if (key_pressed == SIX1 || key_pressed == SIX2) name_write_char('6');
        if (key_pressed == SEVEN1 || key_pressed == SEVEN2) name_write_char('7');
        if (key_pressed == EIGHT1 || key_pressed == EIGHT2) name_write_char('8');
        if (key_pressed == NINE1 || key_pressed == NINE2) name_write_char('9');

        if(key_pressed == BACKSPACE) name_delete_char();

        if(key_pressed == ENTER && player_name[0] != '\0') {
          getDate();
          getTime();
          register_score(player_points, player_name, player_day, player_month, player_year, player_hour, player_minute);
          game_mode = MENU_SCREEN;
          destroy_mushrooms();
          initialize_mushrooms();
          destroy_birds_and_crystals();
          initialize_birds_and_crystals();
          destroy_character(dave);
          player_points = 0;
          p_counter = 0;
          player_name[0] = '\0';
          base_background_loaded = false;
        }

        if (key_pressed == ESC)
        {
          game_mode = MENU_SCREEN;
          destroy_mushrooms();
          initialize_mushrooms();
          destroy_birds_and_crystals();
          initialize_birds_and_crystals();
          destroy_character(dave);
          player_points = 0;
          p_counter = 0;
          player_name[0] = '\0';
          base_background_loaded = false;

        }
        break;
      
      default:
        break;
    }
    keyboard_event_occurred = false;
  }

  //MOUSE EVENTS
  if (mouse_event_occurred)
  {
    int x = cursor->sprite->x;
    int y = cursor->sprite->y;

    switch (game_mode)
    {
      case MENU_SCREEN:

        if (x >= 296 && x <= 480)
        {

          //PLAY BUTTON
          if (y >= 243 && y <= 291)
          {
            menu_option = PLAY;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the PLAY BUTTON
            if (cursor->lb) {
              dave = create_character();
              game_mode = PLAYING_SCREEN;
              player_points = 0;
              p_counter = 0;
              player_name[0] = '\0';
              base_background_loaded = false;
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }

          }

          //SCOREBOARD BUTTON
          else if (y >= 305 && y <= 353)
          {
            menu_option = SCOREBOARD;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the SCOREBOARD BUTTON
            if (cursor->lb) {
              game_mode = SCOREBOARD_SCREEN;
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }
          }

          //INSTRUCTIONS BUTTON
          else if (y >= 366 && y <= 414)
          {
            menu_option = INSTRUCTIONS;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the INSTRUCTIONS BUTTON
            if (cursor->lb) {
              game_mode = INSTRUCTIONS_SCREEN;
              if (cursor->hand_mode)
              become_regular_cursor(cursor);
            }
          }

          //EXIT BUTTON
          else if (y >= 541 && y <= 589)
          {
            menu_option = EXIT;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the EXIT BUTTON
            if (cursor->lb) {
              game_mode = EXIT_SCREEN;
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }
          }

          else {
            if (cursor->hand_mode)
              become_regular_cursor(cursor);
          }
  
        }

        else {
          if (cursor->hand_mode)
            become_regular_cursor(cursor);
        }

        break;

      case EXIT_SCREEN:

        if (x >= 333 && x <= 441)
        {
          //YES BUTTON
          if (y >= 250 && y <= 278)
          {
            yes_no_option = YES;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the YES BUTTON
            if (cursor->lb)
            {
              game_mode = CLOSE_GAME;
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }
          }

          //NO BUTTON
          else if (y >= 286 && y <= 314)
          {
            yes_no_option = NO;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the NO BUTTON
            if (cursor->lb)
            {
              erase_exit_menu();
              game_mode = MENU_SCREEN;
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }
          }

          else
          {
            if (cursor->hand_mode)
              become_regular_cursor(cursor);
          }

        }

        else
        {
          if (cursor->hand_mode)
            become_regular_cursor(cursor);
        }

        break;
      
      case PLAYING_SCREEN:

        if (dave->status != DYING)
        {
          if (cursor->hand_mode)
            become_regular_cursor(cursor);

          for (int i = 0; i < MAX_BIRDS_AND_CRYSTALS; i++)
          {
            if (cursor_over_crystal(x, y, crystals[i]) && crystals[i]->in_game) {
              become_hand_cursor(cursor);

              if (cursor->lb) {
                click_on_crystal(crystals[i]);
                
                if (crystals[i]->special) player_points += 15;
                else player_points += 5;
              }
            }
          }
        }

        break;

      case PAUSE_SCREEN:

        if (x >= 337 && x <= 462)
        {
          //RESUME BUTTON
          if (y >= 292 && y <= 325)
          {
            pause_option = RESUME;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the RESUME BUTTON
            if (cursor->lb)
            {
              erase_pause_window();
              game_mode = PLAYING_SCREEN;
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }
          }

          //QUIT BUTTON
          else if (y >= 333 && y <= 366)
          {
            pause_option = QUIT;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the QUIT BUTTON
            if (cursor->lb)
            {
              game_mode = QUIT_SCREEN;
              erase_pause_window();
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }
          }

          else
          {
            if (cursor->hand_mode)
              become_regular_cursor(cursor);
          }

        }

        else
        {
          if (cursor->hand_mode)
            become_regular_cursor(cursor);
        }

        break;

      case QUIT_SCREEN:

        if (x >= 333 && x <= 441)
        {
          //YES BUTTON
          if (y >= 250 && y <= 278)
          {
            yes_no_option = YES;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the YES BUTTON
            if (cursor->lb)
            {
              game_mode = MENU_SCREEN;
              destroy_mushrooms();
              initialize_mushrooms();
              destroy_birds_and_crystals();
              initialize_birds_and_crystals();
              destroy_character(dave);
              player_points = 0;
              p_counter = 0;
              player_name[0] = '\0';
              base_background_loaded = false;
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }
          }

          //NO BUTTON
          else if (y >= 286 && y <= 314)
          {
            yes_no_option = NO;
            if (!cursor->hand_mode)
              become_hand_cursor(cursor);

            //Click on the NO BUTTON
            if (cursor->lb)
            {
              erase_quit_window();
              game_mode = PAUSE_SCREEN;
              if (cursor->hand_mode)
                become_regular_cursor(cursor);
            }
          }

          else
          {
            if (cursor->hand_mode)
              become_regular_cursor(cursor);
          }

        }

        else
        {
          if (cursor->hand_mode)
            become_regular_cursor(cursor);
        }

        break;

      default:
        break;
    }
    mouse_event_occurred = false;
  }

  //TIMER EVENTS
  if (timer_event_occurred)
  {
    switch (game_mode)
    {
      case MENU_SCREEN:
        if (!base_background_loaded)
        {
          draw_menu_background(menu_option);
          set_background(start_menu_xpm);
          base_background_loaded = true;
        }
        draw_menu_title();
        draw_menu_buttons(menu_option);
        draw_cursor(cursor);
        write_buffer_to_videomem();
        break;

      case SCOREBOARD_SCREEN:
        draw_scoreboard_window();
        write_top5_in_the_screen();
        draw_cursor(cursor);
        write_buffer_to_videomem();
        break;

      case INSTRUCTIONS_SCREEN:
        draw_instructions_window();
        draw_cursor(cursor);
        write_buffer_to_videomem();
        break;

      case EXIT_SCREEN:
        draw_exit_window();
        draw_yes_no_buttons(yes_no_option);
        draw_cursor(cursor);
        write_buffer_to_videomem();
        break;

      case PLAYING_SCREEN:
        if (!base_background_loaded)
        {
          draw_scenario_background();
          set_background(game_background_xpm);
          base_background_loaded = true;
        }

        //If character is not dead
        if ( !((dave->status == DYING) && (dave->frame == 17)) )
        {
          draw_moving_scenario(true);

          draw_character(dave, true);

          mushroom_generator(player_points);
          draw_mushrooms(true); //Moving mushrooms

          erase_points_word();

          bird_and_crystal_generator();
          draw_birds_and_crystals(true);

          draw_points_word();
          draw_number_centralized(player_points, 695, 785, 45);

          //If character collides with a mushroom, he dies
          if (mushrooms_collision_detection(dave)) {
            dave->status = DYING;
            dave->frame = 0;
          }

          if (++p_counter == 30 && dave->status != DYING) {
            player_points++;
            p_counter = 0;
          }
        }

        //If character is dead
        else
        {
          draw_moving_scenario(false);
          draw_character(dave, false);
          draw_mushrooms(false); //Fixed mushrooms

          erase_points_word();

          draw_birds_and_crystals(false);

          draw_points_word();
          draw_number_centralized(player_points, 695, 785, 45);

          dead_timer++;

          if (dead_timer == 60) {
            game_mode = GAMEOVER_SCREEN;
            dead_timer = 0;
          }
        }

        draw_cursor(cursor);
        write_buffer_to_videomem();
        break;

      case GAMEOVER_SCREEN:

        draw_moving_scenario(false);
        draw_character(dave, false);
        draw_mushrooms(false);

        erase_points_word();

        draw_birds_and_crystals(false);
        draw_points_word();
        draw_number_centralized(player_points, 695, 785, 45);

        draw_gameover_window();
        draw_highscore_medal(player_points);
        draw_word_centralized(player_name, 252, 554, 384);
        draw_number_centralized(player_points, 355, 445, 230);

        draw_cursor(cursor);
        write_buffer_to_videomem();
        break;

      case PAUSE_SCREEN:

        draw_moving_scenario(false);
        draw_character(dave, false);
        draw_mushrooms(false);

        erase_points_word();

        draw_birds_and_crystals(false);

        draw_points_word();
        draw_number_centralized(player_points, 695, 785, 45);

        draw_pause_window();
        draw_pause_buttons(pause_option);

        draw_cursor(cursor);
        write_buffer_to_videomem();
        break;

      case QUIT_SCREEN:

        draw_moving_scenario(false);
        draw_character(dave, false);
        draw_mushrooms(false);

        erase_points_word();

        draw_birds_and_crystals(false);

        draw_points_word();
        draw_number_centralized(player_points, 695, 785, 45);

        draw_quit_window();
        draw_yes_no_buttons(yes_no_option);

        draw_cursor(cursor);
        write_buffer_to_videomem();
        break;

      default:
        break;
    }
    timer_event_occurred = false;
  }

}

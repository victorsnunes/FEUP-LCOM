#include "mushroom.h"

/**
 * @file mushroom.c
 * @brief This file contains the implementation of the mushrooms
 */

static int last_mushroom_generated = 0; /**<@brief contains the time the last mushroom showed up */

void initialize_mushrooms() {

  for (int i = 0; i < MAX_MUSHROOMS; i++) {
    Mushroom* m = malloc(sizeof(Mushroom));
    m->sprite = *mushroom_sprites[0];
    m->in_game = false;
    mushrooms[i] = m;
  }

}

void initialize_mushroom_sprites() {

  mushroom_sprites[0] = create_sprite(red_mushroom1_xpm, 800, 432, -12, 0);
  mushroom_sprites[1] = create_sprite(red_mushroom2_xpm, 800, 432, -12, 0);
  mushroom_sprites[2] = create_sprite(brown_mushroom1_xpm, 800, 432, -12, 0);
  mushroom_sprites[3] = create_sprite(brown_mushroom2_xpm, 800, 432, -12, 0);

  initialize_mushrooms();

}

bool mushroom_out_of_range(Mushroom* m) {
  
  int x = (m->sprite).x;

  return x <= -75;
}

Mushroom* create_mushroom() {
  Mushroom* m = malloc(sizeof(Mushroom));
  m->in_game = true;

  time_t t;
  srand((unsigned) time(&t));
  int index = rand() % 4;

  m->sprite = *mushroom_sprites[index];

  return m;
}

void mushroom_generator(int player_points) {

  time_t t;
   
  /* This is useful for getting a true radom number */
  srand((unsigned) time(&t));

  int num;

  //First 2 minutes of the game, EASY MODE
  if (player_points < 120) {
    num = rand() % 125;
  }
  //After 2 minutes and before 5 minutes when the game started, MEDIUM MODE
  else if (player_points < 300) {
    num = rand() % 100;
  }
  //After 5 minutes of the game, HARD MODE
  else {
    num = rand() % 50;
  }

  last_mushroom_generated++; //Remember, this function is called 30 times per second

  //If the random number is 3, then we generate a mushroom
  if (num == 3) {

    //But we can't generate it if: The mushroom will take a place where is almost impossible for the player not to loose OR will be really close to the previous one, causing a bad visual effect
    if (!( (last_mushroom_generated > 7 && last_mushroom_generated < 25) || last_mushroom_generated < 4)) {

      for (int i = 0; i < MAX_MUSHROOMS; i++) {
        if (!mushrooms[i]->in_game) {
          free(mushrooms[i]);
          Mushroom* m = create_mushroom();
          mushrooms[i] = m;
          break;
        }
      }

      //We will not reset the this variable if the mushroom generated was a close mushroom. Because, if the mushroom generated after that is also close, this can cause a situation where it is impossible for the player not to loose
      if (last_mushroom_generated > 7)
        last_mushroom_generated = 0;

    }

  }

}

void draw_mushrooms(bool move) {

  for (int i = 0; i < MAX_MUSHROOMS; i++) {

    if (mushrooms[i]->in_game) {

      if (mushroom_out_of_range(mushrooms[i])) {
        mushrooms[i]->in_game = false;
      }
      else {
        if (move)
          (mushrooms[i]->sprite).x += (mushrooms[i]->sprite).xspeed;
        draw_sprite_no_packman_effect(&(mushrooms[i]->sprite));
      }
    }

  }

}

bool mushrooms_collision_detection(Character* character) {
  
  for (int i = 0; i < MAX_MUSHROOMS; i++) {

    if (mushrooms[i]->in_game) {
      if (collition_detection(character->sprite, &mushrooms[i]->sprite))
        return true;
    }
      
  }

  return false;

}

void destroy_mushrooms() {

  for (int i = 0; i < MAX_MUSHROOMS; i++) {
    free(mushrooms[i]);
  }

}

void destroy_mushroom_sprites() {

  destroy_sprite(mushroom_sprites[0]);
  destroy_sprite(mushroom_sprites[1]);
  destroy_sprite(mushroom_sprites[2]);
  destroy_sprite(mushroom_sprites[3]);
  
}

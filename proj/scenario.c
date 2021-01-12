#include "scenario.h"

/**
 * @file scenario.c
 * @brief This file contains the implementation of the scenario
 * 
 */


void initialize_scenario_sprites() {
  ground = create_sprite(ground_xpm, 0, 467, -12, 0);
  nearTrees = create_sprite(near_trees_xpm, 0, 272, -3, 0);
  farTrees = create_sprite(far_trees_xpm, 0, 272, -1, 0);
  gameBackground = create_sprite(game_background_xpm, 0, 0, 0, 0);
}

void draw_scenario_background() {
  draw_sprite(gameBackground);
}

void draw_moving_scenario(bool move) {

  if (move) {
  move_sprite(farTrees);
  move_sprite(nearTrees);
  move_sprite(ground);
  }

  draw_sprite_and_background(farTrees);
  draw_sprite(nearTrees);
  draw_sprite(ground);
}

void destroy_scenario_sprites() {

  destroy_sprite(ground);
  destroy_sprite(nearTrees);
  destroy_sprite(farTrees);
  destroy_sprite(gameBackground);
  
}

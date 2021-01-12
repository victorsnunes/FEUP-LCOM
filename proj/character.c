#include "character.h"


/**
 * @file character.c
 * @brief This file contains the implementation of the character  
 */


void initialize_character_sprites() {

  characterRunning[0] = create_sprite(run1_xpm, 140, 385, 0, 0);
  characterRunning[1] = create_sprite(run2_xpm, 140, 385, 0, 0);
  characterRunning[2] = create_sprite(run3_xpm, 140, 385, 0, 0);
  characterRunning[3] = create_sprite(run4_xpm, 140, 385, 0, 0);
  characterRunning[4] = create_sprite(run5_xpm, 140, 385, 0, 0);
  characterRunning[5] = create_sprite(run6_xpm, 140, 385, 0, 0);
  characterRunning[6] = create_sprite(run7_xpm, 140, 385, 0, 0);
  characterRunning[7] = create_sprite(run8_xpm, 140, 385, 0, 0);
  characterRunning[8] = create_sprite(run9_xpm, 140, 385, 0, 0);
  characterRunning[9] = create_sprite(run10_xpm, 140, 385, 0, 0);


  characterJumping[0] = create_sprite(jump1_xpm, 140, 385, 0, 0);
  characterJumping[1] = create_sprite(jump2_xpm, 140, 374, 0, 0);
  characterJumping[2] = create_sprite(jump2_xpm, 140, 364, 0, 0);
  characterJumping[3] = create_sprite(jump2_xpm, 140, 354, 0, 0);
  characterJumping[4] = create_sprite(jump2_xpm, 140, 346, 0, 0);
  characterJumping[5] = create_sprite(jump3_xpm, 140, 338, 0, 0);
  characterJumping[6] = create_sprite(jump3_xpm, 140, 330, 0, 0);
  characterJumping[7] = create_sprite(jump3_xpm, 140, 324, 0, 0);
  characterJumping[8] = create_sprite(jump3_xpm, 140, 318, 0, 0);
  characterJumping[9] = create_sprite(jump4_xpm, 140, 313, 0, 0);
  characterJumping[10] = create_sprite(jump4_xpm, 140, 309, 0, 0);
  characterJumping[11] = create_sprite(jump4_xpm, 140, 306, 0, 0);
  characterJumping[12] = create_sprite(jump4_xpm, 140, 303, 0, 0);
  characterJumping[13] = create_sprite(jump5_xpm, 140, 301, 0, 0);
  characterJumping[14] = create_sprite(jump5_xpm, 140, 300, 0, 0);
  characterJumping[15] = create_sprite(jump5_xpm, 140, 300, 0, 0);
  characterJumping[16] = create_sprite(jump5_xpm, 140, 300, 0, 0);
  characterJumping[17] = create_sprite(jump6_xpm, 140, 301, 0, 0);
  characterJumping[18] = create_sprite(jump6_xpm, 140, 303, 0, 0);
  characterJumping[19] = create_sprite(jump6_xpm, 140, 306, 0, 0);
  characterJumping[20] = create_sprite(jump6_xpm, 140, 309, 0, 0);
  characterJumping[21] = create_sprite(jump7_xpm, 140, 314, 0, 0);
  characterJumping[22] = create_sprite(jump7_xpm, 140, 319, 0, 0);
  characterJumping[23] = create_sprite(jump7_xpm, 140, 324, 0, 0);
  characterJumping[24] = create_sprite(jump8_xpm, 140, 331, 0, 0);
  characterJumping[25] = create_sprite(jump8_xpm, 140, 338, 0, 0);
  characterJumping[26] = create_sprite(jump8_xpm, 140, 346, 0, 0);
  characterJumping[27] = create_sprite(jump9_xpm, 140, 355, 0, 0);
  characterJumping[28] = create_sprite(jump9_xpm, 140, 364, 0, 0);
  characterJumping[29] = create_sprite(jump9_xpm, 140, 375, 0, 0);

  characterDying[0] = create_sprite(die1_xpm, 140, 385, 0, 0);
  characterDying[1] = create_sprite(die2_xpm, 140, 385, 0, 0);
  characterDying[2] = create_sprite(die3_xpm, 140, 385, 0, 0);
  characterDying[3] = create_sprite(die4_xpm, 140, 385, 0, 0);
  characterDying[4] = create_sprite(die5_xpm, 140, 385, 0, 0);
  characterDying[5] = create_sprite(die6_xpm, 140, 385, 0, 0);

}

Character* create_character() {
  Character* character = malloc(sizeof(Character));
  character->status = RUNNING;
  character->frame = 0;
  character->sprite = characterRunning[0];

  return character;
}

void draw_character_running(Character* character, bool move) {

  character->sprite = characterRunning[character->frame / 2];
  draw_sprite(character->sprite);

  if (move)
    character->frame = (character->frame + 1) % 20;

}

void draw_character_jumping(Character* character, bool move) {

  character->sprite = characterJumping[character->frame];
  draw_sprite(character->sprite);

  if (move)
    character->frame += 1;
}

void draw_character_dying(Character* character) {

  character->sprite = characterDying[character->frame / 3];
  draw_sprite(character->sprite);
  if (character->frame < 17)
    character->frame += 1;
  
}

void draw_character(Character* character, bool move) {

  switch (character->status)
  {
  case RUNNING:
    draw_character_running(character, move);
    break;

  case JUMPING:
    draw_character_jumping(character, move);

    //End of jump
    if (character->frame == 30) {
      character->frame = 0;
      character->status = RUNNING;
    }
    break;

  case DYING:
    draw_character_dying(character);
    break;
  
  default:
    break;
  }
}

void destroy_character(Character* character) {

  if (character != NULL) {
    free(character);
  }

}

void destroy_character_sprites() {

  for (int i = 0; i < 30; i++) {

    destroy_sprite(characterJumping[i]);
    if (i < 10)
      destroy_sprite(characterRunning[i]);
    if (i < 6)
      destroy_sprite(characterDying[i]);

  }
  
}

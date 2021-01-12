#include "birds_and_crystals.h"

static unsigned last_bird_generated = 0;  /**<@brief contains the time the last bird showed up */


/**
 * @file birds_and_crystals.c
 * @brief This file contains the functions to implement the birds flying with crystals that gives the player extra points 
 */


void initialize_birds_and_crystals() {

  for (int i = 0; i < MAX_BIRDS_AND_CRYSTALS; i++) {

    Bird* b = malloc(sizeof(Bird));
    Crystal* c = malloc(sizeof(Crystal));
    Shine_Effect* e = malloc(sizeof(Shine_Effect));

    b->sprite = *regular_bird_sprites[0];
    b->in_game = false;

    c->sprite = *greenCrystal;
    c->in_game = false;

    e->sprite = *effects_sprites[0];
    e->frame = 30;

    birds[i] = b;
    crystals[i] = c;
    effects[i] = e;
  }

}

void initialize_birds_and_crystals_sprites() {

  regular_bird_sprites[0] = create_sprite(regular_bird_frame1_xpm, 800, 60, -5, 0);
  regular_bird_sprites[1] = create_sprite(regular_bird_frame2_xpm, 800, 60, -5, 0);

  special_bird_sprites[0] = create_sprite(special_bird_frame1_xpm, 800, 60, -12, 0);
  special_bird_sprites[1] = create_sprite(special_bird_frame2_xpm, 800, 60, -12, 0);
  special_bird_sprites[2] = create_sprite(special_bird_frame3_xpm, 800, 60, -12, 0);
  special_bird_sprites[3] = create_sprite(special_bird_frame4_xpm, 800, 60, -12, 0);

  greenCrystal = create_sprite(green_crystal_xpm, 800, 60, -5, 0);
  redCrystal = create_sprite(red_crystal_xpm, 800, 60, -12, 0);

  effects_sprites[0] = create_sprite(effect1_xpm, 0, 0, 0, 0);
  effects_sprites[1] = create_sprite(effect2_xpm, 0, 0, 0, 0);
  effects_sprites[2] = create_sprite(effect3_xpm, 0, 0, 0, 0);
  effects_sprites[3] = create_sprite(effect4_xpm, 0, 0, 0, 0);
  effects_sprites[4] = create_sprite(effect5_xpm, 0, 0, 0, 0);
  effects_sprites[5] = create_sprite(effect6_xpm, 0, 0, 0, 0);
  effects_sprites[6] = create_sprite(effect7_xpm, 0, 0, 0, 0);
  effects_sprites[7] = create_sprite(effect8_xpm, 0, 0, 0, 0);
  effects_sprites[8] = create_sprite(effect9_xpm, 0, 0, 0, 0);
  effects_sprites[9] = create_sprite(effect10_xpm, 0, 0, 0, 0);
  effects_sprites[10] = create_sprite(effect11_xpm, 0, 0, 0, 0);
  effects_sprites[11] = create_sprite(effect12_xpm, 0, 0, 0, 0);
  effects_sprites[12] = create_sprite(effect13_xpm, 0, 0, 0, 0);
  effects_sprites[13] = create_sprite(effect14_xpm, 0, 0, 0, 0);
  effects_sprites[14] = create_sprite(effect15_xpm, 0, 0, 0, 0);
  effects_sprites[15] = create_sprite(effect16_xpm, 0, 0, 0, 0);
  effects_sprites[16] = create_sprite(effect17_xpm, 0, 0, 0, 0);
  effects_sprites[17] = create_sprite(effect18_xpm, 0, 0, 0, 0);
  effects_sprites[18] = create_sprite(effect19_xpm, 0, 0, 0, 0);
  effects_sprites[19] = create_sprite(effect20_xpm, 0, 0, 0, 0);
  effects_sprites[20] = create_sprite(effect21_xpm, 0, 0, 0, 0);
  effects_sprites[21] = create_sprite(effect22_xpm, 0, 0, 0, 0);
  effects_sprites[22] = create_sprite(effect23_xpm, 0, 0, 0, 0);
  effects_sprites[23] = create_sprite(effect24_xpm, 0, 0, 0, 0);
  effects_sprites[24] = create_sprite(effect25_xpm, 0, 0, 0, 0);
  effects_sprites[25] = create_sprite(effect26_xpm, 0, 0, 0, 0);
  effects_sprites[26] = create_sprite(effect27_xpm, 0, 0, 0, 0);
  effects_sprites[27] = create_sprite(effect28_xpm, 0, 0, 0, 0);
  effects_sprites[28] = create_sprite(effect29_xpm, 0, 0, 0, 0);
  effects_sprites[29] = create_sprite(effect30_xpm, 0, 0, 0, 0);

  initialize_birds_and_crystals();

}

void draw_bird(Bird* b, bool move) {

  if (b->special) {
    (b->sprite).map = special_bird_sprites[b->frame / 2]->map;
    
  }
  else {
    (b->sprite).map = regular_bird_sprites[b->frame/ 4]->map;
  }

  draw_sprite_no_packman_effect(&b->sprite);
  if (move)
    b->frame = (b->frame + 1) % 8;

}

bool bird_out_of_range(Bird* b) {

  return (b->sprite).x < -60;
  
}

bool crystal_out_of_range(Crystal* c) {

  return (c->sprite).x < -60;

}

Bird* create_bird(bool special) {

  Bird* b = malloc(sizeof(Bird));

  if (special)
    b->sprite = *special_bird_sprites[0];
  else
    b->sprite = *regular_bird_sprites[0];

  b->special = special;
  b->frame = 0;
  b->in_game = true;

  return b;

}

Crystal* create_crystal(bool special) {

  Crystal* c = malloc(sizeof(Crystal));

  if (special)
    c->sprite = *redCrystal;
  else
    c->sprite = *greenCrystal;

  c->special = special;
  c->in_game = true;

  return c;

}


void bird_and_crystal_generator() {

  last_bird_generated++;
  if (last_bird_generated < 120) return;

  time_t t;
   
  /* This is useful for getting a true radom number */
  srand((unsigned) time(&t));

  int num;

  num = rand() % 1000;

  if (num < 4) {

    for (int i = 0; i < MAX_BIRDS_AND_CRYSTALS; i++) {
      if (!birds[i]->in_game && !crystals[i]->in_game) {

        free(birds[i]); free(crystals[i]);

        bool special = false;
        if (num == 1) special = true; 

        Bird* b = create_bird(special);
        Crystal* c = create_crystal(special);

        int y = 20 + (rand() % 185);
        (b->sprite).y = y;
        (c->sprite).y = y;

        birds[i] = b;
        crystals[i] = c;

        break;
      }
    }

    last_bird_generated = 0;

  }

}

void draw_birds_and_crystals(bool move) {

  for (int i = 0; i < MAX_BIRDS_AND_CRYSTALS; i++) {

    if (effects[i]->frame < 30) erase_sprite(&effects[i]->sprite);

    if (birds[i]->in_game) {

      if (crystal_out_of_range(crystals[i])) {
        crystals[i]->in_game = false;
      }
      if (bird_out_of_range(birds[i])) {
        birds[i]->in_game = false;
      }
      else {
        erase_sprite(&(crystals[i]->sprite));
        if (move) {
          (birds[i]->sprite).x += (birds[i]->sprite).xspeed;
          (crystals[i]->sprite).x += (crystals[i]->sprite).xspeed;
        }
        if (crystals[i]->in_game)
          draw_sprite_no_packman_effect(&(crystals[i]->sprite));
        draw_bird(birds[i], move);
      }
    }

    if (effects[i]->frame != 30) {
      draw_sprite_no_packman_effect(&(effects[i]->sprite));
      if (move) {
        if (++effects[i]->frame < 30)
          (effects[i]->sprite).map = effects_sprites[effects[i]->frame]->map;
      }
    }

  }

}

bool cursor_over_crystal(int x, int y, Crystal* c) {

  Sprite sp = c->sprite;

  if ( !( x >= sp.x && x <= sp.x + sp.width && y >= sp.y && y <= sp.y + sp.height ) )
    return false;

  uint32_t color;
  uint8_t *p;
  p = sp.map;

  x -= sp.x;
  y -= sp.y;

  color = p[ (sp.height*y + x) * 3 ];

  return color != CHROMA_KEY_GREEN_888;

}

void click_on_crystal(Crystal* c) {

  for (int i = 0; i < MAX_BIRDS_AND_CRYSTALS + 1; i++){

    if (effects[i]->frame == 30) {
      effects[i]->sprite = *effects_sprites[0];
      effects[i]->frame = 0;

      if (c->special) {
        (effects[i]->sprite).x = (c->sprite).x - 5;
        (effects[i]->sprite).y = (c->sprite).y + 3;
      }
      else {
        (effects[i]->sprite).x = (c->sprite).x - 8;
        (effects[i]->sprite).y = (c->sprite).y + 4;
      }

      break;
    }

  }

  c->in_game = false;

}


void destroy_birds_and_crystals() {

  for (int i = 0; i < MAX_BIRDS_AND_CRYSTALS; i++) {
    free(birds[i]);
    free(crystals[i]);
    free(effects[i]);
  }

}

void destroy_birds_and_crystals_sprites() {

  for (int i = 0; i < 30; i++) {

    destroy_sprite(effects_sprites[i]);
    if (i < 4)
      destroy_sprite(special_bird_sprites[i]);
    if (i < 2)
      destroy_sprite(regular_bird_sprites[i]);

  }

  destroy_sprite(greenCrystal);
  destroy_sprite(redCrystal);

}

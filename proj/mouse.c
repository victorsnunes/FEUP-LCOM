#include <lcom/lcf.h>

#include "mouse.h"

#include <stdint.h>
#include <stdio.h>

/**
 * @file mouse.c
 * @brief This file contains the implementation of the code used to interact with the Mouse 
 */

/** @name Static variables */
///@{
static int hood_id_mouse;
static uint8_t bytes[3];
///@}

/** @name Global variables */
///@{
int b = 0;
bool bytes_loaded = false;
///@}

int mouse_subscribe_int(uint8_t *bit_no) {

    hood_id_mouse = *bit_no;
    *bit_no = BIT(*bit_no);

    if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hood_id_mouse) != OK)
        return 1;

    return 0;
}

int mouse_unsubscribe_int() {
    
    if (sys_irqrmpolicy(&hood_id_mouse) != OK) return 1;

    return 0;
}

int mouse_write(uint8_t cmd) {

    uint8_t status;
    uint8_t mouse_answer;
    while (1) {

        if (kbc_write(CMD_REG, WRITE_BYTE_TO_MOUSE) != OK) return 1;
        if (kbc_write(IN_BUF, cmd) != OK) return 1;

        if (util_sys_inb(STAT_REG, &status) != OK) return 3;
        if ((status & OBF) && (status & AUX)) {

            if (util_sys_inb(OUT_BUF, &mouse_answer) != OK) return 4;
            if (mouse_answer == ACK) return 0;

        }

        tickdelay(micros_to_ticks(DELAY));
    }

    return 5;

}

void(mouse_ih)() {

    uint8_t mouseData;
    uint8_t status;

    util_sys_inb(STAT_REG, &status);

    if (status & AUX) {

        util_sys_inb (OUT_BUF, &mouseData);

        if (!(status & (PARITY | TIME_OUT))) {
            
            if ( (b == 0) && !(mouseData & BIT(3)) ) return;
            bytes[b] = mouseData;
            b = (b + 1) % 3;

            if (b == 0) bytes_loaded = true;
            else bytes_loaded = false;
        }
    }
}

int kbc_write(int port, uint8_t cmd) {

  uint8_t status;

  for (int i = 0; i < ATTEMPTS; i++) {

    if (util_sys_inb(STAT_REG, &status) != OK) continue;

    if ((status & IBF) == 0)
        if (sys_outb(port, cmd) == OK) return 0;

    tickdelay(micros_to_ticks(DELAY));
  }

    return 2;
}

bool mouse_bytes_loaded() {
    return bytes_loaded;
}

void initialize_mouse_sprites() {  
    regular_cursor = create_sprite(cursor_xpm, 600, 500, 0, 0);
    hand_cursor = create_sprite(hand_cursor_xpm, 600, 500, 0, 0);
}

Cursor* create_cursor() {
    
    Cursor* c = malloc(sizeof(Cursor));
    
    c->sprite = create_sprite(cursor_xpm, 600, 500, 0, 0);
    c->hand_mode = false;

    c->lb = false;
    c->rb = false;
    c->mb = false;

    c->x_ov = false;
    c->y_ov= false;

    return c;
}

void update_cursor(Cursor* c) {

    c->lb = bytes[0] & LB;
    c->rb = bytes[0] & RB;
    c->mb = bytes[0] & MB;

    c->x_ov = bytes[0] & X_OV;
    c->y_ov = bytes[0] & Y_OV;


    (c->sprite)->xspeed = (unsigned int) bytes[1];
    if (bytes[0] & X_MSB)
        (c->sprite)->xspeed |= 0xFFFFFF00;

    (c->sprite)->yspeed = (unsigned int) bytes[2];
    if (bytes[0] & Y_MSB)
        (c->sprite)->yspeed |= 0xFFFFFF00;
    
    erase_sprite(c->sprite);
    move_cursor_sprite(c->sprite);
}

void draw_cursor(Cursor* c) {
    draw_sprite_no_packman_effect(c->sprite);
}

void become_hand_cursor(Cursor* c) {
    c->sprite->map = hand_cursor->map;
    c->sprite->width = hand_cursor->width;
    c->sprite->height = hand_cursor->height;

    c->hand_mode = true;
}

void become_regular_cursor(Cursor* c) {
    c->sprite->map = regular_cursor->map;
    c->sprite->width = regular_cursor->width;
    c->sprite->height = regular_cursor->height;

    c->hand_mode = false;
}

void destroy_cursor(Cursor* c) {
    destroy_sprite(c->sprite);
    free(c);
}

void destroy_mouse_sprites() {
    destroy_sprite(regular_cursor);
    destroy_sprite(hand_cursor);
}

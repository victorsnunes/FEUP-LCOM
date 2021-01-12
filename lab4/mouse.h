#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

int mouse_subscribe_int(uint8_t *bit_no);
int mouse_unsubscribe_int();
void(mouse_ih)();
int mouse_read();
void create_packet(struct packet *pckt, uint8_t packetBytes[]);
int set_mouse_to_minix_default();
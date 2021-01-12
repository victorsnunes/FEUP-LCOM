#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <lcom/lcf.h>
#include <stdio.h>
#include <stdbool.h>

#include <minix/driver.h>
#include <sys/mman.h>
#include <machine/int86.h>
#include <math.h>

int init_mode(uint16_t mode);

int vbeModeInfo(uint16_t mode, vbe_mode_info_t* mode_info);
void *(vg_init)(uint16_t mode);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len ,uint32_t color );
int drawPixel(uint16_t x, uint16_t y, uint32_t color);

#endif
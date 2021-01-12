#include "sprite.h"

/**
 * @file sprite.c
 * @brief This file contains the implementation of the sprites
 */


static uint8_t* current_background;
extern uint16_t hres; 
extern uint16_t vres; 
extern uint8_t bytes_per_pixel;

Sprite *create_sprite(xpm_map_t xpm, int x, int y,int xspeed, int yspeed) {
    
    Sprite *sp = (Sprite *) malloc (sizeof(Sprite));
    if(sp == NULL) return NULL;

    xpm_image_t img;
    sp->map = xpm_load(xpm, XPM_8_8_8, &img); 
    
    sp->x = x; 
    sp->y = y; 
    sp->xspeed= xspeed; 
    sp->yspeed= yspeed;

    sp->width = img.width;
    sp->height= img.height;
     

    if(sp->map == NULL) {
        free(sp);
        return NULL;
    }

    return sp;
}

void destroy_sprite(Sprite *sp) {
    if( sp == NULL )
    return;
    
    if( sp->map )
        free(sp->map);
    
    free(sp);
    sp = NULL;
}

void draw_sprite(Sprite* sp) {
    
    uint32_t color;
    uint8_t *p;
    p = sp->map;

    for (int column = sp->y; column < sp->height + sp->y; column++) {
        for (int row = sp->x; row < sp->width + sp->x; row++) {
        
            color = *p;
            p++;
            color |= *p << 8;
            p++;
            color |= *p << 16;
            p++;

            drawPixel(row, column, color);
        }
    }

}

void draw_sprite_and_background(Sprite* sp){

    uint32_t color;
    uint8_t *p;
    p = sp->map;

    uint32_t color_background;
    uint8_t *p_background = current_background;
    p_background += (sp->y * hres + sp->x) * bytes_per_pixel;


    for (int column = sp->y; column < sp->height + sp->y; column++) {
        for (int row = sp->x; row < sp->width + sp->x; row++) {

            color = *p;
            p++;
            color |= *p << 8;
            p++;
            color |= *p << 16;
            p++;

            color_background = *p_background;
            p_background++;
            color_background |= *p_background << 8;
            p_background++;
            color_background |= *p_background << 16;
            p_background++;

            if (color == CHROMA_KEY_GREEN_888) drawPixel(row, column, color_background);
            else drawPixel(row, column, color);
        }
        p_background += (hres - sp->width) * bytes_per_pixel;
    }


}

void draw_sprite_no_packman_effect(Sprite* sp) {

    uint32_t color;
    uint8_t *p;
    p = sp->map;

    for (int column = sp->y; column < sp->height + sp->y; column++) {
        for (int row = sp->x; row < sp->width + sp->x; row++) {
        
            color = *p;
            p++;
            color |= *p << 8;
            p++;
            color |= *p << 16;
            p++;
            
            if (row >= 0 && row < hres && column >= 0 && column < vres)
                drawPixel(row, column, color);
        }
    }
}

void erase_sprite(Sprite* sp) {

    uint32_t color;
    uint8_t *p = current_background;
    p += (sp->y * hres + sp->x) * bytes_per_pixel;

    for (int column = sp->y; column < sp->height + sp->y; column++) {
        for (int row = sp->x; row < sp->width + sp->x; row++) {

            color = *p;
            p++;
            color |= *p << 8;
            p++;
            color |= *p << 16;
            p++;

            if (row >= 0 && row < hres && column >= 0 && column < vres)
                drawPixel(row, column, color);
        }
        p += (hres - sp->width) * bytes_per_pixel;
    }

}

void move_sprite(Sprite *sp) {
    sp->x += sp->xspeed;
    sp->y += sp->yspeed;

    if (sp->x < 0) sp->x += hres ;
    if (sp->x > hres) sp->x -= hres;
    if (sp->y < 0) sp->y += vres;
    if (sp->y > vres) sp->y -= vres;
}

void move_cursor_sprite(Sprite* sp) {
    
    sp->x += sp->xspeed;
    sp->y -= sp->yspeed;

    if (sp->x < 0) sp->x = 0;
    if (sp->x > (hres - 5)) sp->x = (hres - 5);
    if (sp->y < 0) sp->y = 0;
    if (sp->y > (vres - 5)) sp->y = (vres - 5);
}

bool collition_detection(Sprite *sp1, Sprite *sp2) {

    int intersection_x;
    int intersection_y;
    int intersection_x_final;
    int intersection_y_final;

    if (sp1->x <= sp2->x) {
        intersection_x = (sp1->x + sp1->width > sp2->x) ? sp2->x : 0;
        intersection_x_final = sp1->x + sp1->width;
    }
    else {
        intersection_x = (sp2->x + sp2->width > sp1->x) ? sp1->x : 0;
        intersection_x_final = sp2->x + sp2->width;
    }

    if (sp1->y <= sp2->y) {
        intersection_y = (sp1->y + sp1->height > sp2->y) ? sp2->y : 0;
        intersection_y_final = sp1->y + sp1->height;
    }
    else {
        intersection_y = (sp2->y + sp2->height > sp1->y) ? sp1->y : 0;
        intersection_y_final = sp2->y + sp2->height;
    }

    if ( (intersection_x == 0) || (intersection_y == 0) )
        return false;


    uint32_t color1;
    uint32_t color2;
    uint8_t *p1;
    uint8_t *p2;
    p1 = sp1->map;
    p2 = sp2->map;

    for (int column = intersection_y; column <= intersection_y_final ; column++) {
        for (int row = intersection_x; row <= intersection_x_final; row++) {
        
            color1 = *p1;
            color2 = *p2;
            p1++; p2++;

            color1 |= *p1 << 8;
            color2 |= *p2 << 8;
            p1++; p2++;

            color1 |= *p1 << 16;
            color2 |= *p2 << 16;
            p1++; p2++;
            
            if (color1 != CHROMA_KEY_GREEN_888 && color2 != CHROMA_KEY_GREEN_888)
                return true;
        }
    }

    return false;

}

void set_background(xpm_map_t xpm) {
    xpm_image_t img;
    current_background = xpm_load(xpm, XPM_8_8_8, &img);
}

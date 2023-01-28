#ifndef SPRITE_H
#define SPRITE_H

#include "main.h"

typedef struct {
    float x;
    float y;
    float distance;
    float angle;
    short visible;
    int texture;
} sprite_t;

void render_sprite_projection(void);
void render_map_sprite(void);

#endif
#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdio.h>
#include <stdint.h>
#include "upng.h"

typedef struct {
    upng_t* upngTexture;
    int width;
    int height;
    uint32_t* texture_buffer;
} texture_t;

texture_t wall_textures[10];

typedef struct {
    upng_t* upng_texture;
    int width;
    int height;
    uint32_t* texture_buffer;
} sprite_t;

sprite_t sprite_textures[3];

void load_wall_textures();
void free_wall_textures();

void load_sprite_textures();
void free_sprite_textures();

#endif

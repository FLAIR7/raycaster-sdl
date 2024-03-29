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

texture_t wall_textures[11];

void load_wall_textures();
void free_wall_textures();

#endif

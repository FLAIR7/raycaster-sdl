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

texture_t wallTextures[12];

void loadWallTextures();
void freeWallTextures();

#endif

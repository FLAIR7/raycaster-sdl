#ifndef MAIN_H
#define MAIN_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <math.h>
#include "textures.h"

// SCREEN
#define WIDTH           800
#define HALF_WIDTH      400
#define HEIGHT          600
#define HALF_HEIGHT     300
#define PI 3.14159265359

// FPS
#define FPS 60

// CAMERA
#define DOUBLE_PI   (2 * PI)
#define FOV         (PI / 3)
#define HALF_FOV    (FOV / 2)
#define STEP_ANGLE  (FOV / WIDTH);
#define MIN(a,b) (((a)<(b))?(a):(b))

// MAP
#define MAP_SIZE    32
#define MAP_SCALE   64
#define MAP_RANGE   MAP_SCALE * MAP_SIZE
#define MAP_SPEED   (MAP_SCALE / 2) / 10

// PLAYER
typedef struct {
    float player_x;          
    float player_y;          
    float player_angle;      
    float player_move_x;      
    float player_move_y;      
    float player_move_angle;  
} Player;

#endif
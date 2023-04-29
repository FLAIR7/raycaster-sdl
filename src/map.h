#ifndef MAP_H
#define MAP_H

#include "main.h"

#define MAP_SIZE    32
#define MAP_SCALE   64
#define MAP_RANGE   MAP_SCALE * MAP_SIZE
#define MAP_SPEED   (MAP_SCALE / 2) / 10

extern int map[];
extern int map_realsize;

void show_minimap();
void setup_map();

#endif
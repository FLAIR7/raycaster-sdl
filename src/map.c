#include "map.h"

int map[1028];

int map_realsize = sizeof map / sizeof map[0];

void setup_map()
{
    FILE *file;
    file = fopen("maps/map1.map", "r");
    if(file == NULL)
    {
        fprintf(stderr, "Error opening file!\n");
        exit(1);
    }
    if (file) {
        int i = 0;
        int num;
        while(fscanf(file, "%d", &num) == 1)
        {
            map[i] = num;
            i++;
        }
        fclose(file);
    }
}

void show_minimap(){
    int map_offset_x = floor(WIDTH / 2) - HALF_WIDTH;
    int map_offset_y = floor(HEIGHT / 2) - HALF_HEIGHT;
    for(int row = 0; row < MAP_SIZE; row++){
        for(int col = 0; col < MAP_SIZE; col++){
            int square = row * MAP_SIZE + col;
            if(map[square] != 0){
                SDL_Rect square_map = {
                    map_offset_x + col * 10,
                    map_offset_y + row * 10,
                    10 - 1,
                    10 - 1
                };
                SDL_SetRenderDrawColor(renderer, 0, 102, 102, 255);
                SDL_RenderFillRect(renderer, &square_map);
            } else {
                SDL_Rect square_map = {
                    map_offset_x + col * 10,
                    map_offset_y + row * 10,
                    10,
                    10,
                };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &square_map);
            }
        }
    }
}

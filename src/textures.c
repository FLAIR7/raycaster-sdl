#include <stdio.h>
#include "textures.h"
#include "upng.h"

static const char* texture_file_names[10] = {
    "./assets/redbrick.png",
    "./assets/purplestone.png",
    "./assets/mossystone.png",
    "./assets/graystone.png",
    "./assets/colorstone.png",
    "./assets/bluestone.png",
    "./assets/wood.png",
    "./assets/eagle.png",
    "./assets/bluedoor.png",
    "./assets/door.png",
};

static const char* sprite_file_names[3] = {
    "./sprites/gun_0.png",
    "./sprites/gun_1.png",
    "./sprites/gun_2.png",
};

void load_wall_textures(void){
    for(int i = 0; i < 10; i++){
        upng_t* upng;

        upng = upng_new_from_file(texture_file_names[i]);
        if(upng != NULL){
            upng_decode(upng);
            if(upng_get_error(upng) == UPNG_EOK) {
                wall_textures[i].upngTexture = upng;
                wall_textures[i].width = upng_get_width(upng);
                wall_textures[i].height = upng_get_height(upng);
                wall_textures[i].texture_buffer = (uint32_t*)upng_get_buffer(upng);
            }
        
        }

    }
}

void free_wall_textures(void){
    for(int i = 0; i < 10; i++)
        upng_free(wall_textures[i].upngTexture);
}

void load_sprite_textures(void){
    for(int i = 0; i < 3; i++) {
        upng_t* upng;

        upng = upng_new_from_file(sprite_file_names[i]);
        if(upng != NULL) {
            upng_decode(upng);
            if(upng_get_error(upng) == UPNG_EOK) {
                sprite_textures[i].upng_texture = upng;
                sprite_textures[i].width = upng_get_width(upng);
                sprite_textures[i].height = upng_get_height(upng);
                sprite_textures[i].texture_buffer = (uint32_t*)upng_get_buffer(upng);
            }
        }
    }
}

void free_sprite_textures(void){
    for(int i = 0; i < 3; i++)
        upng_free(sprite_textures[i].upng_texture);
}

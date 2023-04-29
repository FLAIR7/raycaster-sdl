#include <stdio.h>
#include "textures.h"
#include "upng.h"

static const char* texture_file_names[11] = {
    "./assets/redbrick.png",
    "./assets/purplestone.png",
    "./assets/mossystone.png",
    "./assets/graystone.png",
    "./assets/colorstone.png",
    "./assets/bluestone.png",
    "./assets/door.png",
    "./assets/wood.png",
    "./assets/eagle.png",
    "./assets/door2.png",
    "./assets/bluedoor.png",
};

void load_wall_textures(void){
    for(int i = 0; i < 11; i++){
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
    for(int i = 0; i < 6; i++)
    {

    }
}

void free_sprite_textures(void){
    
}

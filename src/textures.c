#include <stdio.h>
#include "textures.h"
#include "upng.h"

static const char* textureFileNames[10] = {
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

void load_wall_textures(void){
    for(int i = 0; i < 10; i++){
        upng_t* upng;

        upng = upng_new_from_file(textureFileNames[i]);
        if(upng != NULL){
            upng_decode(upng);
            if(upng_get_error(upng) == UPNG_EOK) {
                wallTextures[i].upngTexture = upng;
                wallTextures[i].width = upng_get_width(upng);
                wallTextures[i].height = upng_get_height(upng);
                wallTextures[i].texture_buffer = (uint32_t*)upng_get_buffer(upng);
            }
        
        }

    }
}

void free_wall_textures(void){
    for(int i = 0; i < 10; i++)
        upng_free(wallTextures[i].upngTexture);
}

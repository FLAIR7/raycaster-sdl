#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

// CONSTANTS
SDL_Window* window;
SDL_Renderer* renderer;

int game_loop = 1;

// MAP
#define MAP_SIZE    32
#define MAP_SCALE   64
#define MAP_RANGE   MAP_SCALE * MAP_SIZE
#define MAP_SPEED   (MAP_SCALE / 2) / 10

int show_map = 0;
const int map[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    4, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 4, 15, 0, 15, 4, 9, 6, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 8, 8, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 2, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
};
int map_realsize = sizeof map / sizeof map[0]; // the lenght of the map

// PLAYER
typedef struct {
    float playerX;          
    float playerY;          
    float playerAngle;      
    float playerMoveX;      
    float playerMoveY;      
    float playerMoveAngle;  
} Player;

Player player;

// TEXTURES
uint32_t *color_buffer;
SDL_Texture *color_buffer_texture;
uint32_t *textures[10];

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

void input(void){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym){
                case SDLK_DOWN:
                case SDLK_UP:
                    player.playerMoveX = 0;
                    player.playerMoveY = 0;
                    break;
                case SDLK_RIGHT:
                case SDLK_LEFT:
                    player.playerMoveAngle = 0;
                    break;
                case SDLK_LSHIFT:
                    show_map = 0;
                    break;
            }
        }
        else if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym){
                case SDL_QUIT:
                    game_loop = 0;
                    break;
                case SDLK_ESCAPE:
                    game_loop = 0;
                    break;
                case SDLK_UP:
                    player.playerMoveX = 1;
                    player.playerMoveY = 1;
                    break;
                case SDLK_DOWN:
                    player.playerMoveX = -1;
                    player.playerMoveY = -1;
                    break;
                case SDLK_LEFT:
                    player.playerMoveAngle = 1;
                    break;
                case SDLK_RIGHT:
                    player.playerMoveAngle = -1;
                    break;
                case SDLK_LSHIFT:
                    show_map = 1;
                    break;
            }
        } else if (event.type == SDL_WINDOWEVENT) {
            switch(event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    game_loop = 0;
                    break;
            }
        }
    }
}

void setup(void){
    player.playerX = MAP_SCALE + 20;
    player.playerY = MAP_SCALE + 20;
    player.playerMoveX = 0;
    player.playerMoveY = 0;
    player.playerMoveAngle = 0;
    player.playerAngle = PI / 2;
    
    // allocate the amount of bytes in memory to hold the colorbuffer
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)WIDTH * (uint32_t)HEIGHT);

    color_buffer_texture = SDL_CreateTexture
    (
        renderer, 
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT
    );

    load_wall_textures();
}

void update(void){
    float playerOffsetX = sin(player.playerAngle) * MAP_SPEED;
    float playerOffsetY = cos(player.playerAngle) * MAP_SPEED;
    int mapTargetX = floor(player.playerY / MAP_SCALE) * MAP_SIZE + floor((player.playerX + playerOffsetX * player.playerMoveX) / MAP_SCALE);
    int mapTargetY = floor((player.playerY + playerOffsetY * player.playerMoveY) / MAP_SCALE) * MAP_SIZE + floor(player.playerX / MAP_SCALE);
    
    // collision
    if(player.playerMoveX && map[mapTargetX] == 0) player.playerX += playerOffsetX * player.playerMoveX;
    if(player.playerMoveY && map[mapTargetY] == 0) player.playerY += playerOffsetY * player.playerMoveY;
    if(player.playerMoveAngle) player.playerAngle += 0.03 * player.playerMoveAngle;
}

void render_color_buffer(void){
    SDL_UpdateTexture
    (
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)((uint32_t)WIDTH * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color){
    for(int i = 0; i < WIDTH; i++){
        for(int y = 0; y < HEIGHT; y++){
            color_buffer[(WIDTH * y) + i] = color;
        }
    }
}

void render(void){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Calculate map and player offsets
    //int mapOffsetX = floor(WIDTH / 2)- 400;
    //int mapOffsetY = 0;
    int mapOffsetX = floor(WIDTH / 2) - HALF_WIDTH;
    int mapOffsetY = floor(HEIGHT / 2) - HALF_HEIGHT;
    float playerMapX = (player.playerX / MAP_SCALE) * 10 + mapOffsetX;
    float playerMapY = (player.playerY / MAP_SCALE) * 10 + mapOffsetY;

    // raycasting
    float currentAngle = player.playerAngle + HALF_FOV;
    float rayStartX = floor(player.playerX / MAP_SCALE) * MAP_SCALE;
    float rayStartY = floor(player.playerY / MAP_SCALE) * MAP_SCALE;

    for(int ray = 0; ray < WIDTH; ray++){
        float currentSin = sin(currentAngle);
        float currentCos = cos(currentAngle);
        currentSin = currentSin ? currentSin : 0.000001;
        currentCos = currentCos ? currentCos : 0.000001;
        
        // vertical line intersection
        float rayEndX;
        float rayEndY;
        float rayDirectionX;
        float verticalDepth;
        int textureEndY;
        int textureY;
        if(currentSin > 0){
            rayEndX = rayStartX + MAP_SCALE;
            rayDirectionX = 1;
        } else {
            rayEndX = rayStartX;
            rayDirectionX = -1;
        }
        
        for(int offset = 0; offset < MAP_RANGE; offset += MAP_SCALE){
            verticalDepth = (rayEndX - player.playerX) / currentSin;
            rayEndY = player.playerY + verticalDepth * currentCos;
            float mapTargetX = floor(rayEndX / MAP_SCALE);
            float mapTargetY = floor(rayEndY / MAP_SCALE);
            if(currentSin <= 0)
                mapTargetX += rayDirectionX;
            int targetSquare = mapTargetY * MAP_SIZE + mapTargetX;
            if(targetSquare < 0 || targetSquare > map_realsize - 1) break;
            if(map[targetSquare] != 0) { 
                textureY = map[targetSquare];
                if(map[targetSquare] == 14) textureY = 4;
                if(map[targetSquare] == 15) textureY = 10;
                break; 
            }
            rayEndX += rayDirectionX * MAP_SCALE;
        } textureEndY = rayEndY;
        
        // horizontal line intersection
        rayEndY = 0;
        rayEndX = 0;
        float rayDirectionY;
        float horizontalDepth;
        int textureEndX;
        int textureX;
        if(currentCos > 0){
            rayEndY = rayStartY + MAP_SCALE;
            rayDirectionY = 1;
        } else {
            rayEndY = rayStartY;
            rayDirectionY = -1;
        }

        for(int offset = 0; offset < MAP_RANGE; offset += MAP_SCALE){
            horizontalDepth = (rayEndY - player.playerY) / currentCos;
            rayEndX = player.playerX + horizontalDepth * currentSin;
            float mapTargetX = floor(rayEndX / MAP_SCALE);
            float mapTargetY = floor(rayEndY / MAP_SCALE);
            if(currentCos <= 0)
                mapTargetY += rayDirectionY;
            int targetSquare = mapTargetY * MAP_SIZE + mapTargetX;
            if(targetSquare < 0 || targetSquare > map_realsize - 1)  break;
            if(map[targetSquare] != 0) { 
                textureX = map[targetSquare];
                if(map[targetSquare] == 14) textureX = 10;
                if(map[targetSquare] == 15) textureX = 4;
                break; 
            }
            rayEndY += rayDirectionY * MAP_SCALE;
        } textureEndX = rayEndX;
        
        // 3D Projection
        float depth = verticalDepth < horizontalDepth ? verticalDepth : horizontalDepth;
        int textureImage = verticalDepth < horizontalDepth ? textureY : textureX;
        int textureOffset = verticalDepth < horizontalDepth ? textureEndY : textureEndX;
        textureOffset = floor(textureOffset - floor(textureOffset / MAP_SCALE) * MAP_SCALE);
        depth *= cos(player.playerAngle - currentAngle);        
        float wallHeight = MIN(floor(MAP_SCALE * 480 / (depth + 0.0001)), 50000);

        int wall_top_pixel;
        int wall_bottom_pixel;
        int distance_from_top;   
        int texture_offsetX;  
        int texture_offsetY; 
        int texNum;       
        uint32_t texture_color;
        int texture_width;
        int texture_height;

        wall_top_pixel = (HEIGHT / 2) - (wallHeight / 2);
        wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
            
        wall_bottom_pixel = (HEIGHT / 2) + (wallHeight / 2);
        wall_bottom_pixel = wall_bottom_pixel > HEIGHT ? HEIGHT : wall_bottom_pixel;
           
        // set the color of the sky
        for(int y = 0; y < wall_top_pixel; y++)
            color_buffer[(WIDTH * y) + ray] = 0xFF333333;

        if(verticalDepth < horizontalDepth) {
            texture_offsetX = (int) textureEndY % 64;
        } else {
            texture_offsetX = (int) textureEndX % 64;           
        } 

        texNum = textureImage -1; // this line changes the texture in the wall
        texture_width = wallTextures[texNum].width;
        texture_height = wallTextures[texNum].height;
            
        // set the texture of the walls from top to bottom
        for(int y = wall_top_pixel; y < wall_bottom_pixel; y++){
            distance_from_top = y + (wallHeight / 2) - (HALF_HEIGHT);
            texture_offsetY = distance_from_top * ((float)texture_height / wallHeight);
                
            texture_color = wallTextures[texNum].texture_buffer[(texture_width * texture_offsetY) + texture_offsetX];
            color_buffer[(WIDTH * y) + ray] = texture_color;        
        }
            
        // set the color of the floor
        for(int y = wall_bottom_pixel; y < HEIGHT; y++){
            color_buffer[(WIDTH * y) + ray] = 0xFF777777;
        }
        
        
        currentAngle -= STEP_ANGLE;
    }
    
    render_color_buffer();
    clear_color_buffer(0xFF000000);

     if(show_map){
            for(int row = 0; row < MAP_SIZE; row++){
                for(int col = 0; col < MAP_SIZE; col++){
                    int square = row * MAP_SIZE + col;
                    if(map[square] != 0){
                        SDL_Rect squareMap = {
                            mapOffsetX + col * 10,
                            mapOffsetY + row * 10,
                            10 - 1,
                            10 - 1
                        };
                        SDL_SetRenderDrawColor(renderer, 0, 102, 102, 255);
                        SDL_RenderFillRect(renderer, &squareMap);
                    } else {
                        SDL_Rect squareMap = {
                            mapOffsetX + col * 10,
                            mapOffsetY + row * 10,
                            10,
                            10,
                        };
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_RenderFillRect(renderer, &squareMap);
                    }
                }
            }
            
            // draw the player on 2D
            SDL_Rect player2d = {
                playerMapX,
                playerMapY,
                5,
                5
            };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &player2d);
            
            // player arm
            SDL_RenderDrawLine(renderer, playerMapX, playerMapY, playerMapX + sin(player.playerAngle) * 15, playerMapY + cos((player.playerAngle)) * 15);
    }

    SDL_RenderPresent(renderer);
}

void destroy_window(void){
    free_wall_textures();
    free(color_buffer);
    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void init(void){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Raycaster-sdl", HALF_WIDTH, HALF_HEIGHT, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    
    if(!window){
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}
    
int main(void){

    init();
    setup();

    while(game_loop){
        Uint32 frame_start = SDL_GetTicks();
        input();
        update();
        render();

        Uint32 frame_time = SDL_GetTicks() - frame_start;
        
        Uint32 delay_time = 1000 / FPS - frame_time;
        if(delay_time > 1000 / FPS) delay_time = 0;
        SDL_Delay(delay_time);

    }

    destroy_window();
    
    return EXIT_SUCCESS;
}

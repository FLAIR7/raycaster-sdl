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
/*#define MIN(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})*/
#define MIN(a,b) (((a)<(b))?(a):(b))

// CONSTANTS
SDL_Window* window;
SDL_Renderer* renderer;

int gameLoop = 1;

// MAP
#define MAP_SIZE    32
#define MAP_SCALE   64
#define MAP_RANGE   MAP_SCALE * MAP_SIZE
#define MAP_SPEED   (MAP_SCALE / 2) / 10

int showMap = 0;
const int map[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    4, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
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
uint32_t *colorBuffer;
SDL_Texture *colorBufferTexture;
uint32_t *textures[] = {
    (uint32_t *) REDBRICK_TEXTURE,
	(uint32_t *) PURPLESTONE_TEXTURE,
	(uint32_t *) MOSSYSTONE_TEXTURE,
	(uint32_t *) GRAYSTONE_TEXTURE,
	(uint32_t *) COLORSTONE_TEXTURE,
	(uint32_t *) BLUESTONE_TEXTURE,
	(uint32_t *) WOOD_TEXTURE,
	(uint32_t *) EAGLE_TEXTURE,
};

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
                    showMap = 0;
                    break;
            }
        }
        else if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym){
                case SDL_QUIT:
                    gameLoop = 0;
                    break;
                case SDLK_ESCAPE:
                    gameLoop = 0;
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
                    showMap = 1;
                    break;
            }
        } else if (event.type == SDL_WINDOWEVENT) {
            switch(event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    gameLoop = 0;
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
    colorBuffer = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)WIDTH * (uint32_t)HEIGHT);

    colorBufferTexture = SDL_CreateTexture
    (
        renderer, 
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT
    );
    
    // create a texture with pattern of blue and black lines
    /*wallTexture = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)TEXTURE_WIDTH * (uint32_t)TEXTURE_HEIGHT);

    for(int x = 0; x < TEXTURE_WIDTH; x++){
        for(int y = 0; y < TEXTURE_HEIGHT; y++){
            wallTexture[(TEXTURE_WIDTH * y) + x] = (x % 8 && y % 8) ? 0xFF0000FF : 0xFF000000;
        }
    }*/
    /*
    textures[0] = (uint32_t *) REDBRICK_TEXTURE;
	textures[1] = (uint32_t *) PURPLESTONE_TEXTURE;
	textures[2] = (uint32_t *) MOSSYSTONE_TEXTURE;
	textures[3] = (uint32_t *) GRAYSTONE_TEXTURE;
	textures[4] = (uint32_t *) COLORSTONE_TEXTURE;
	textures[5] = (uint32_t *) BLUESTONE_TEXTURE;
	textures[6] = (uint32_t *) WOOD_TEXTURE;
	textures[7] = (uint32_t *) EAGLE_TEXTURE;*/
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

void draw_sky(void){
    SDL_Rect skyRect = {
        0,
        0, 
        WIDTH,
        WIDTH
    };
    SDL_SetRenderDrawColor(renderer, 139, 185, 249, 255);
    SDL_RenderFillRect(renderer, &skyRect);
}

void draw_floor(void){
    SDL_Rect floorRect = {
        0,
        HEIGHT / 2,
        WIDTH,
        HEIGHT / 2
    };
    SDL_SetRenderDrawColor(renderer, 52, 158, 0, 255);
    SDL_RenderFillRect(renderer, &floorRect);
}

void render_colorBuffer(void){
    SDL_UpdateTexture
    (
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int)((uint32_t)WIDTH * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void clear_colorBuffer(uint32_t color){
    for(int i = 0; i < WIDTH; i++){
        for(int y = 0; y < HEIGHT; y++){
            colorBuffer[(WIDTH * y) + i] = color;
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
                //if(map[targetSquare] == 2) textureY = 5;
                //if(map[targetSquare] == 3) textureY = 3;
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
                //if(map[targetSquare] == 2) textureX = 5;
                //if(map[targetSquare] == 3) textureX = 3;
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
        /*SDL_Rect wall = {
            mapOffsetX + ray,
            mapOffsetY + (HEIGHT / 2 - wallHeight / 2),
            1,
            wallHeight
        };
        SDL_RenderFillRect(renderer, &wall);
        
        if(verticalDepth < horizontalDepth)
            SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
        else
            SDL_SetRenderDrawColor(renderer, 85, 85, 85, 255);*/
            
        
//            int wallTopPixel;
//            int wallBottomPixel;
//            wallTopPixel = (HEIGHT / 2) - (wallHeight / 2);
//            wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
//            
//            wallBottomPixel = (HEIGHT / 2) + (wallHeight / 2);
//            wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;
//            
//            // set the color of the walls
//            for(int y = wallTopPixel; y < wallBottomPixel; y++){
//                colorBuffer[(WIDTH * y) + ray] = verticalDepth < horizontalDepth ? 0xFFFFFFFF : 0xFFCCCCCC;
//            }
//
//            // set the color of the floor
//            for(int y = wallBottomPixel; y < HEIGHT; y++){
//                colorBuffer[(WIDTH * y) + ray] = 0xFF777777;
//            }
    

            int wallTopPixel;
            int wallBottomPixel;
            float perpDistance;
            float distanceProjPlane;
            float projectWallHeight;     
            int wallStripHeight;
            int distanceFromTop;   
            int textureOffsetX;  
            int textureOffsetY; 
            int texNum;       
            uint32_t texelColor;
            int distance;

            perpDistance = depth;
            distanceProjPlane = (WIDTH / 2) / tan(HALF_FOV);
            projectWallHeight = (64 / perpDistance) * distanceProjPlane;

            wallStripHeight = (int)projectWallHeight;
                            
            wallTopPixel = (HEIGHT / 2) - (wallHeight / 2);
            wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
            
            wallBottomPixel = (HEIGHT / 2) + (wallHeight / 2);
            wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;
           

            // set the color of the sky
            for(int y = 0; y < wallTopPixel; y++)
                colorBuffer[(WIDTH * y) + ray] = 0xFF333333;

            
            if(verticalDepth < horizontalDepth) {
                textureOffsetX = (int) textureEndY % 64;
            } else {
                textureOffsetX = (int) textureEndX % 64;           
            } 

            texNum = textureImage -1; // this line changes the texture in the wall
             
            

            // set the color of the walls from top to bottom
            for(int y = wallTopPixel; y < wallBottomPixel; y++){
                distanceFromTop = y + (wallHeight / 2) - (HALF_HEIGHT);
                textureOffsetY = distanceFromTop * ((float)TEXTURE_HEIGHT / wallHeight);
                
                texelColor = textures[texNum][(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
                colorBuffer[(WIDTH * y) + ray] = texelColor;        
            }
            
            // set the color of the floor
            for(int y = wallBottomPixel; y < HEIGHT; y++){
                colorBuffer[(WIDTH * y) + ray] = 0xFF777777;
            }
        
        
        currentAngle -= STEP_ANGLE;
    }
    
    render_colorBuffer();
    clear_colorBuffer(0xFF000000);

     if(showMap){
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
    free(colorBuffer);
    SDL_DestroyTexture(colorBufferTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void init(void){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Error in init\n");
        exit(1);
    }

    window = SDL_CreateWindow("My game", HALF_WIDTH, HALF_HEIGHT, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    
    if(!window){
        fprintf(stderr, "Error creating SDL window.\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        fprintf(stderr, "Error creating SDL renderer\n");
        exit(1);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}
    
int main(void){

    init();
    setup();

    while(gameLoop){
        Uint32 frameStart = SDL_GetTicks();
        input();
        update();
        render();

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        
        Uint32 delayTime = 1000 / FPS - frameTime;
        if(delayTime > 1000 / FPS) delayTime = 0;
        SDL_Delay(delayTime);

    }

    destroy_window();
    
    return EXIT_SUCCESS;
}

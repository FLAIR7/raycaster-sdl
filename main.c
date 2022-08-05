#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

// screen
#define WIDTH           500
#define HALF_WIDTH      250
#define HEIGHT          400
#define HALF_HEIGHT     200

// FPS
#define FPS 60

// constants
SDL_Window* window;
SDL_Renderer* renderer;
#define PI 3.14159265359

int gameLoop = 1;

// map
#define MAP_SIZE    16
#define MAP_SCALE   25
#define MAP_RANGE   MAP_SCALE * MAP_SIZE
#define MAP_SPEED   (MAP_SCALE / 2) / 10

int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 
    1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 
    1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

// player 
double playerX = MAP_SCALE + 20;
double playerY = MAP_SCALE + 20;
double playerAngle =  PI / 3;
double playerMoveX = 0;
double playerMoveY = 0;
double playerMoveAngle = 0;

// camera
#define DOUBLE_PI   (2 * PI)
#define FOV         (PI / 3)
#define HALF_FOV    (FOV / 2)
#define STEP_ANGLE  (FOV / WIDTH);


void input(void){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym){
                case SDLK_DOWN:
                case SDLK_UP:
                    playerMoveX = 0;
                    playerMoveY = 0;
                    break;
                case SDLK_RIGHT:
                case SDLK_LEFT:
                    playerMoveAngle = 0;
                    break;
            }
        }
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym){
                case SDL_QUIT:
                    gameLoop = 0;
                    break;
                case SDLK_ESCAPE:
                    gameLoop = 0;
                    break;
                case SDLK_DOWN:
                    playerMoveX = -1;
                    playerMoveY = -1;
                    break;
                case SDLK_UP:
                    playerMoveX = 1;
                    playerMoveY = 1;
                    break;
                case SDLK_LEFT:
                    playerMoveAngle = 1;
                    break;
                case SDLK_RIGHT:
                    playerMoveAngle = -1;
                    break;
            }
        }
    }
}

void update(void){
    double playerOffsetX = sin(playerAngle) * MAP_SPEED;
    double playerOffsetY = cos(playerAngle) * MAP_SPEED;
    int mapTargetX = floor(playerY / MAP_SCALE) * MAP_SIZE + floor((playerX + playerOffsetX * playerMoveX) / MAP_SCALE);
    int mapTargetY = floor((playerY + playerOffsetY * playerMoveY) / MAP_SCALE) * MAP_SIZE + floor(playerX / MAP_SCALE);
    

    if(playerMoveX && map[mapTargetX] == 0) playerX += playerOffsetX * playerMoveX;
    if(playerMoveY && map[mapTargetY] == 0) playerY += playerOffsetY * playerMoveY;
    if(playerMoveAngle) playerAngle += 0.03 * playerMoveAngle;
}



void render(void){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    // Calculate map and player offsets
    int mapOffsetX = floor(WIDTH / 2 - MAP_RANGE / 2);
    int mapOffsetY = floor(HEIGHT / 2 - MAP_RANGE / 2);
    double playerMapX = playerX + mapOffsetX;
    double playerMapY = playerY + mapOffsetY;
    
    // Draw 2d map
    for(int row = 0; row < MAP_SIZE; row++){
        for(int col = 0; col < MAP_SIZE; col++){
            int square = row * MAP_SIZE + col;
            if(map[square] != 0){
                SDL_Rect squareMap = {
                    mapOffsetX + col * MAP_SCALE,
                    mapOffsetY + row * MAP_SCALE,
                    MAP_SCALE - 1,
                    MAP_SCALE - 1
                };
                SDL_SetRenderDrawColor(renderer, 0, 102, 102, 255);
                SDL_RenderFillRect(renderer, &squareMap);
            } else {
                SDL_Rect squareMap = {
                    mapOffsetX + col * MAP_SCALE,
                    mapOffsetY + row * MAP_SCALE,
                    MAP_SCALE,
                    MAP_SCALE,
                };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &squareMap);
            }
        }
    }
    
    // draw the player on 2D
    SDL_Rect player = {
        playerMapX,
        playerMapY,
        5,
        5
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player);

    // player arm
    SDL_RenderDrawLine(renderer, playerMapX, playerMapY, playerMapX + sin(playerAngle) * 15, playerMapY + cos(playerAngle) * 15); 
    
    // raycasting
    double currentAngle = playerAngle + HALF_FOV;
    double rayStartX = floor(playerX / MAP_SCALE) * MAP_SCALE;
    double rayStartY = floor(playerY / MAP_SCALE) * MAP_SCALE;

    for(int ray = 0; ray < WIDTH; ray++){
        double currentSin = sin(currentAngle);
        double currentCos = cos(currentAngle);
        currentSin = currentSin ? currentSin : 0.000001;
        currentCos = currentCos ? currentCos : 0.000001;
        
        // vertical line intersection
        double rayEndX;
        double rayEndY;
        double rayDirectionX;
        double verticalDepth;
        if(currentSin > 0){
            rayEndX = rayStartX + MAP_SCALE;
            rayDirectionX = 1;
        } else {
            rayEndX = rayStartX;
            rayDirectionX = -1;
        }
        
        for(int offset = 0; offset < MAP_RANGE; offset += MAP_SCALE){
            verticalDepth = (rayEndX - playerX) / currentSin;
            rayEndY = playerY + verticalDepth * currentCos;
            double mapTargetX = floor(rayEndX / MAP_SCALE);
            double mapTargetY = floor(rayEndY / MAP_SCALE);
            if(currentSin <= 0)
                mapTargetX += rayDirectionX;
            int targetSquare = mapTargetY * MAP_SIZE + mapTargetX;
            if(targetSquare < 0 || targetSquare > sizeof map / sizeof map[0]) break;
            if(map[targetSquare] != 0) break;
            rayEndX += rayDirectionX * MAP_SCALE;
        }

        double tempX = rayEndX;
        double tempY = rayEndY;
        
        // horizontal line intersection
        rayEndY = 0;
        rayEndX = 0;
        double rayDirectionY;
        double horizontalDepth;
        if(currentCos > 0){
            rayEndY = rayStartY + MAP_SCALE;
            rayDirectionY = 1;
        } else {
            rayEndY = rayStartY;
            rayDirectionY = -1;
        }

        for(int offset = 0; offset < MAP_RANGE; offset += MAP_SCALE){
            horizontalDepth = (rayEndY - playerY) / currentCos;
            rayEndX = playerX + horizontalDepth * currentSin;
            double mapTargetX = floor(rayEndX / MAP_SCALE);
            double mapTargetY = floor(rayEndY / MAP_SCALE);
            if(currentCos <= 0)
                mapTargetY += rayDirectionY;
            double targetSquare = mapTargetY * MAP_SIZE + mapTargetX;
            if(targetSquare < 0 || targetSquare > sizeof(map) / sizeof(*map) - 1)  break;
            if(map[(int)targetSquare] != 0) break;
            rayEndY += rayDirectionY * MAP_SCALE;
        }

        double endX = verticalDepth < horizontalDepth ? tempX : rayEndX;
        double endY = verticalDepth < horizontalDepth ? tempY : rayEndY;

        SDL_RenderDrawLine(renderer, playerMapX, playerMapY, endX + mapOffsetX, endY + mapOffsetY);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        currentAngle -= STEP_ANGLE;
    }
    
    SDL_RenderPresent(renderer);
}

void destroy_window(void){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void init(void){
     if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Error");
        exit(1);
    }
    window = SDL_CreateWindow("My game", HALF_WIDTH, HALF_HEIGHT, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!window || !renderer){
        fprintf(stderr, "Error");
        exit(1);
    }
    
}

int main(void){
    init();
    
    Uint32 start; // to handle FPS

    while(gameLoop){
        start = SDL_GetTicks();
        input(); 
        
        if(1000/FPS> SDL_GetTicks() - start){
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }
        
        update();
        render();

    }

    destroy_window();
    
    return EXIT_SUCCESS;
}

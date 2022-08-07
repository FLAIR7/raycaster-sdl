#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

// SCREEN
#define WIDTH           800
#define HALF_WIDTH      400
#define HEIGHT          600
#define HALF_HEIGHT     300

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
#define PI 3.14159265359

int gameLoop = 1;

// MAP
#define MAP_SIZE    32
#define MAP_SCALE   10
#define MAP_RANGE   MAP_SCALE * MAP_SIZE
#define MAP_SPEED   (MAP_SCALE / 2) / 10

int showMap = 0;
int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
};
int map_realsize = sizeof map / sizeof map[0]; // the lenght of the map

// player
typedef struct {
    float playerX;          
    float playerY;          
    float playerAngle;      
    float playerMoveX;      
    float playerMoveY;      
    float playerMoveAngle;  
} Player;

Player player;

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
        }
    }
}

void setup(void){
    player.playerX = MAP_SCALE + 20;
    player.playerY = MAP_SCALE + 20;
    player.playerMoveX = 0;
    player.playerMoveY = 0;
    player.playerMoveAngle = 0;
    player.playerAngle = PI / 3;
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

void render(void){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Calculate map and player offsets
    int mapOffsetX = floor(WIDTH / 2)- 400;
    int mapOffsetY = 0;
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
            if(targetSquare < 0 || targetSquare > map_realsize) break;
            if(map[targetSquare] != 0) break;
            rayEndX += rayDirectionX * MAP_SCALE;
        }
        
        // horizontal line intersection
        rayEndY = 0;
        rayEndX = 0;
        float rayDirectionY;
        float horizontalDepth;
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
            if(map[targetSquare] != 0) break;
            rayEndY += rayDirectionY * MAP_SCALE;
        }
    
        // 3D
        float depth = verticalDepth < horizontalDepth ? verticalDepth : horizontalDepth;
        depth *= cos(player.playerAngle - currentAngle);        
        float wallHeight = MIN(MAP_SCALE * 800 / (depth + 0.0001), HEIGHT);
        SDL_Rect wall = {
            mapOffsetX + ray,
            mapOffsetY + (HEIGHT / 2 - wallHeight / 2),
            1,
            wallHeight
        };
        SDL_RenderFillRect(renderer, &wall);

        if(verticalDepth < horizontalDepth)
            SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
        else 
            SDL_SetRenderDrawColor(renderer, 85, 85, 85, 255);
        
        currentAngle -= STEP_ANGLE;
    }
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
    
    setup();

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

#include "main.h"

// CONSTANTS
SDL_Window* window;
SDL_Renderer* renderer;

int game_loop = 1;

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
int map_realsize = sizeof map / sizeof map[0]; // the length of the map

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
                    player.player_move_x = 0;
                    player.player_move_y = 0;
                    break;
                case SDLK_RIGHT:
                case SDLK_LEFT:
                    player.player_move_angle = 0;
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
                    player.player_move_x = 1;
                    player.player_move_y = 1;
                    break;
                case SDLK_DOWN:
                    player.player_move_x = -1;
                    player.player_move_y = -1;
                    break;
                case SDLK_LEFT:
                    player.player_move_angle = 1;
                    break;
                case SDLK_RIGHT:
                    player.player_move_angle = -1;
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
    player.player_x = MAP_SCALE + 20;
    player.player_y = MAP_SCALE + 20;
    player.player_move_x = 0;
    player.player_move_y = 0;
    player.player_move_angle = 0;
    player.player_angle = PI / 3;
    
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
    float player_offset_x = sin(player.player_angle) * MAP_SPEED;
    float player_offset_y = cos(player.player_angle) * MAP_SPEED;
    int map_target_x = floor(player.player_y / MAP_SCALE) * MAP_SIZE + floor((player.player_x + player_offset_x * player.player_move_x * 10) / MAP_SCALE);
    int map_target_y = floor((player.player_y + player_offset_y * player.player_move_y * 10) / MAP_SCALE) * MAP_SIZE + floor(player.player_x / MAP_SCALE);
    
    // collision
    if(player.player_move_x && map[map_target_x] == 0) player.player_x += player_offset_x * player.player_move_x;
    if(player.player_move_y && map[map_target_y] == 0) player.player_y += player_offset_y * player.player_move_y;
    if(player.player_move_angle) player.player_angle += 0.03 * player.player_move_angle;
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
    int map_offset_x = floor(WIDTH / 2) - HALF_WIDTH;
    int map_offset_y = floor(HEIGHT / 2) - HALF_HEIGHT;
    float player_map_x = (player.player_x / MAP_SCALE) * 10 + map_offset_x;
    float player_map_y = (player.player_y / MAP_SCALE) * 10 + map_offset_y;

    // raycasting
    float current_angle = player.player_angle + HALF_FOV;
    float ray_start_x = floor(player.player_x / MAP_SCALE) * MAP_SCALE;
    float ray_start_y = floor(player.player_y / MAP_SCALE) * MAP_SCALE;

    for(int ray = 0; ray < WIDTH; ray++){
        float current_sin = sin(current_angle);
        float current_cos = cos(current_angle);
        current_sin = current_sin ? current_sin : 0.000001;
        current_cos = current_cos ? current_cos : 0.000001;
        
        // vertical line intersection
        float ray_end_x;
        float ray_end_y;
        float ray_direction_x;
        float vertical_depth;
        int texture_end_y;
        int texture_y;
        if(current_sin > 0){
            ray_end_x = ray_start_x + MAP_SCALE;
            ray_direction_x = 1;
        } else {
            ray_end_x = ray_start_x;
            ray_direction_x = -1;
        }
        
        for(int offset = 0; offset < MAP_RANGE; offset += MAP_SCALE){
            vertical_depth = (ray_end_x - player.player_x) / current_sin;
            ray_end_y = player.player_y + vertical_depth * current_cos;
            float map_target_x = floor(ray_end_x / MAP_SCALE);
            float map_target_y = floor(ray_end_y / MAP_SCALE);
            if(current_sin <= 0)
                map_target_x += ray_direction_x;
            int target_square = map_target_y * MAP_SIZE + map_target_x;
            if(target_square < 0 || target_square > map_realsize - 1) break;
            if(map[target_square] != 0) { 
                texture_y = map[target_square];
                if(map[target_square] == 14) texture_y = 4;
                if(map[target_square] == 15) texture_y = 10;
                break; 
            }
            ray_end_x += ray_direction_x * MAP_SCALE;
        } texture_end_y = ray_end_y;
        
        // horizontal line intersection
        ray_end_y = 0;
        ray_end_x = 0;
        float ray_direction_y;
        float horizontal_depth;
        int texture_end_x;
        int texture_x;
        if(current_cos > 0){
            ray_end_y = ray_start_y + MAP_SCALE;
            ray_direction_y = 1;
        } else {
            ray_end_y = ray_start_y;
            ray_direction_y = -1;
        }

        for(int offset = 0; offset < MAP_RANGE; offset += MAP_SCALE){
            horizontal_depth = (ray_end_y - player.player_y) / current_cos;
            ray_end_x = player.player_x + horizontal_depth * current_sin;
            float map_target_x = floor(ray_end_x / MAP_SCALE);
            float map_target_y = floor(ray_end_y / MAP_SCALE);
            if(current_cos <= 0)
                map_target_y += ray_direction_y;
            int target_square = map_target_y * MAP_SIZE + map_target_x;
            if(target_square < 0 || target_square > map_realsize - 1)  break;
            if(map[target_square] != 0) { 
                texture_x = map[target_square];
                if(map[target_square] == 14) texture_x = 10;
                if(map[target_square] == 15) texture_x = 4;
                break; 
            }
            ray_end_y += ray_direction_y * MAP_SCALE;
        } texture_end_x = ray_end_x;
        
        // 3D Projection
        float depth = vertical_depth < horizontal_depth ? vertical_depth : horizontal_depth;
        int texture_image = vertical_depth < horizontal_depth ? texture_y : texture_x;
        int texture_offset = vertical_depth < horizontal_depth ? texture_end_y : texture_end_x;
        texture_offset = floor(texture_offset - floor(texture_offset / MAP_SCALE) * MAP_SCALE);
        depth *= cos(player.player_angle - current_angle);        
        float wall_height = MIN(floor(MAP_SCALE * 480 / (depth + 0.0001)), 50000);

        int wall_top_pixel;
        int wall_bottom_pixel;
        int distance_from_top;   
        int texture_offsetX;  
        int texture_offsetY; 
        int tex_num;       
        uint32_t texture_color;
        int texture_width;
        int texture_height;

        wall_top_pixel = (HEIGHT / 2) - (wall_height / 2);
        wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
            
        wall_bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
        wall_bottom_pixel = wall_bottom_pixel > HEIGHT ? HEIGHT : wall_bottom_pixel;
           
        // set the color of the sky
        for(int y = 0; y < wall_top_pixel; y++)
            color_buffer[(WIDTH * y) + ray] = 0xFF333333;

        if(vertical_depth < horizontal_depth) {
            texture_offsetX = (int) texture_end_y % 64;
        } else {
            texture_offsetX = (int) texture_end_x % 64;           
        } 

        tex_num = texture_image -1; // this line changes the texture in the wall
        texture_width = wall_textures[tex_num].width;
        texture_height = wall_textures[tex_num].height;
            
        // set the texture of the walls from top to bottom
        for(int y = wall_top_pixel; y < wall_bottom_pixel; y++){
            distance_from_top = y + (wall_height / 2) - (HALF_HEIGHT);
            texture_offsetY = distance_from_top * ((float)texture_height / wall_height);
                
            texture_color = wall_textures[tex_num].texture_buffer[(texture_width * texture_offsetY) + texture_offsetX];
            color_buffer[(WIDTH * y) + ray] = texture_color;        
        }
            
        // set the color of the floor
        for(int y = wall_bottom_pixel; y < HEIGHT; y++){
            color_buffer[(WIDTH * y) + ray] = 0xFF777777;
        }
    
        current_angle -= STEP_ANGLE;
    }
    
    render_color_buffer();
    clear_color_buffer(0xFF000000);

     if(show_map){
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
            
            // draw the player on 2D
            SDL_Rect player2d = {
                player_map_x,
                player_map_y,
                5,
                5
            };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &player2d);
            
            // player arm
            SDL_RenderDrawLine(renderer, player_map_x, player_map_y, player_map_x + sin(player.player_angle) * 15, player_map_y + cos((player.player_angle)) * 15);
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
    
int main(int argv, char** args){

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

#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct rec {
    float x;
    float y;
    float width;
    float heigth;
} rec;


int init_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Unable to initialize SDL");
        return FALSE;
    }

    window = SDL_CreateWindow (
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if (!window) {
        fprintf(stderr, "Unable to create SDL window");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Unable to create SDL Renderer");
        return FALSE;
    }
    return TRUE;
}

void setup(){
    rec.x = 20;
    rec.y = 20;
    rec.width = 15;
    rec.heigth = 15;
}

void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            game_is_running = FALSE; 
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game_is_running = FALSE;
            }
    }
}

void update(){
    rec.x += 1;
    rec.y += 1;
}

void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Draw a rectangle
    SDL_Rect rectangle = {
        rec.x, 
        rec.y, 
        rec.width, 
        rec.heigth
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_RenderPresent(renderer);
}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    game_is_running = init_window();

    setup();

    while (game_is_running){
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
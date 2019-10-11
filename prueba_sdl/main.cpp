#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>

#define SUCCESS 0

int main() {
    SDL_Window *win = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *bitmapTex = nullptr;
    int width = 800, height = 600;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &win, &renderer);

    bitmapTex = IMG_LoadTexture(renderer, "sprites/pitstop_car_1.png");


    bool rotleft = false;
    bool rotright = false;
    bool advance = false;
    int posx = 0;
    int posy = 0;
    bool running = true;
    int angle = 0;
    do {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            auto& keyEvent = (SDL_KeyboardEvent&) e;
            switch (e.type) {
                case SDL_QUIT: running = false; break;
                case SDL_KEYDOWN: {
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT: rotleft = true; break;
                        case SDLK_RIGHT: rotright = true; break;
                        case SDLK_UP: advance = true; break;
                    }
                    break;
                }
                case SDL_KEYUP: {
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT: rotleft = false; break;
                        case SDLK_RIGHT: rotright = false; break;
                        case SDLK_UP: advance = false; break;
                    }
                    break;
                }
            }
        }

        if (rotleft)
            angle -= 1;
        if (rotright)
            angle +=1;
        if (advance) {
            posx += floor(10*cos(2*3.14159265*(angle%360 / (double)360)));
            posy += floor(10*sin(2*3.14159265*(angle%360 / (double)360)));
        }

        SDL_Rect dst{ posx/10, posy/10,50,100 };
        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, bitmapTex, nullptr, &dst, angle-90, nullptr, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    } while (running);

    SDL_DestroyTexture(bitmapTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;    return SUCCESS;
}
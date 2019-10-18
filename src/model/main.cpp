#include <cmath>
#include "Wheel.h"
#include <SDL2/SDL.h>
#include "common/Key.h"
#include "RacingTrack.h"
#include "Box2D/Box2D.h"
#include <SDL2/SDL_image.h>
#include <thread>
#include <chrono>
#include <iostream>

#define SUCCESS 0

int main() {
    SDL_Window *win = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *bitmapTex = nullptr;
    int width = 800, height = 600;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &win, &renderer);
    bitmapTex = IMG_LoadTexture(renderer,"/home/facundotorraca/Documents/Taller de Programacion/TallerDeProgramacion-TP4/src/model/sprites/pitstop_car_1.png");
    bool running = true;

    float posx = 0;
    float posy = 0;
    float angle = 0;

    b2Vec2 gravitiy(0, 0);
    RacingTrack racing_track(gravitiy);
    Wheel wheel(racing_track, 100, -20, 150);

    uint8_t key = 0;
    do {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            auto& keyEvent = (SDL_KeyboardEvent&) e;
            if (keyEvent.type == SDL_QUIT) {
                running = false;
            }

            if (keyEvent.type == SDL_KEYDOWN) {
                switch (keyEvent.keysym.sym) {
                    case SDLK_DOWN:
                        key = KEY_DOWN;
                        break;
                    case SDLK_LEFT:
                        key = KEY_LEFT;
                        break;
                    case SDLK_RIGHT:
                        key = KEY_RIGHT;
                        break;
                    case SDLK_UP:
                        key = KEY_UP;
                        break;
                }
            }
            else if (keyEvent.type == SDL_KEYUP) {
                switch (keyEvent.keysym.sym) {
                    case SDLK_DOWN:
                        key = 0;
                        break;
                    case SDLK_LEFT:
                        key = 0;
                        break;
                    case SDLK_RIGHT:
                        key = 0;
                        break;
                    case SDLK_UP:
                        key = 0;
                        break;
                }
            }
        }

        b2Vec2 position;
        wheel.update(key);
        racing_track.update();
        position = wheel.getPosition();
        angle = wheel.get_angle();
        posx = 50.0f * position.x;
        posy = 50.0f * position.y;

        SDL_Rect dst{(int)posx/10, (int)posy/10,50,100 };
        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, bitmapTex, nullptr, &dst, angle,nullptr, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(33));

    } while (running);

    SDL_DestroyTexture(bitmapTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;    return SUCCESS;
}

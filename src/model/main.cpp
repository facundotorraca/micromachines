#include <cmath>
#include "Car.h"
#include <vector>
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

    SDL_Surface* surface_car = nullptr;
    SDL_Surface* suface_wheel = nullptr;

    SDL_Texture *bitmapTex_1 = nullptr;
    SDL_Texture *bitmapTex_2 = nullptr;
    int width = 1024, height = 720;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &win, &renderer);

    bitmapTex_1 = IMG_LoadTexture(renderer,"assets/sprites/autocopado.png");
    bitmapTex_2 = IMG_LoadTexture(renderer,"assets/sprites/wheel.png");
    bool running = true;

    float center_car_x = 0;
    float center_car_y = 0;
    float angle_car = 0;

    RacingTrack racing_track;
    CarSpecs specs(250, -40, 300, 500, 40, 40);
    Car car(racing_track, specs);

    uint8_t key_v = 0;
    uint8_t key_h = 0;
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
                        key_v = KEY_DOWN;
                        break;
                    case SDLK_LEFT:
                        key_h = KEY_LEFT;
                        break;
                    case SDLK_RIGHT:
                        key_h = KEY_RIGHT;
                        break;
                    case SDLK_UP:
                        key_v = KEY_UP;
                        break;
                }
            }
            if (keyEvent.type == SDL_KEYUP) {
                switch (keyEvent.keysym.sym) {
                    case SDLK_DOWN:
                        key_v = 0;
                        break;
                    case SDLK_LEFT:
                        key_h = 0;
                        break;
                    case SDLK_RIGHT:
                        key_h = 0;
                        break;
                    case SDLK_UP:
                        key_v = 0;
                        break;
                }
            }
        }

        b2Vec2 position;
        //car.update(key_v,key_h);
        racing_track.update();
        position = car.getPosition();
        angle_car = car.get_angle();

        std::vector<float> w_angles = car.get_wheels_angle();
        std::vector<b2Vec2> w_pos = car.get_wheels_position();

        center_car_x = 50 * (w_pos[0].x + w_pos[1].x + w_pos[2].x + w_pos[3].x)/4;
        center_car_y = 50 * (w_pos[0].y + w_pos[1].y + w_pos[2].y + w_pos[3].y)/4;

        float with_car = 50 * 4; float with_wheel = 50 * 0.3;
        float height_car = 50*6; float height_wheel = 50 * 1;

        SDL_Rect dst{int(center_car_x - (with_car / 2)), int(center_car_y - (height_car / 2)), int(with_car), int(height_car)};
        SDL_Rect wbl{int((50.0f * w_pos[0].x) - (with_wheel/2)), int((50.0f * w_pos[0].y) - (height_wheel/2)),int(with_wheel),int(height_wheel)};
        SDL_Rect wbr{int((50.0f * w_pos[1].x) - (with_wheel/2)), int((50.0f * w_pos[1].y) - (height_wheel/2)),int(with_wheel),int(height_wheel)};
        SDL_Rect wfl{int((50.0f * w_pos[2].x) - (with_wheel/2)), int((50.0f * w_pos[2].y) - (height_wheel/2)),int(with_wheel),int(height_wheel)};
        SDL_Rect wfr{int((50.0f * w_pos[3].x) - (with_wheel/2)), int((50.0f * w_pos[3].y) - (height_wheel/2)),int(with_wheel),int(height_wheel)};

        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, bitmapTex_2, nullptr, &wbl, w_angles[0],nullptr, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, bitmapTex_2, nullptr, &wbr, w_angles[1],nullptr, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, bitmapTex_2, nullptr, &wfl, w_angles[2],nullptr, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, bitmapTex_2, nullptr, &wfr, w_angles[3],nullptr, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, bitmapTex_1, nullptr, &dst, angle_car,nullptr, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);

        std::this_thread::sleep_for(std::chrono::milliseconds(33));

    } while (running);

    SDL_DestroyTexture(bitmapTex_1);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;    return SUCCESS;
}

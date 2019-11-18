//
// Created by javier on 17/11/19.
//

#include <cstdint>
#include <SDL_mixer.h>
#include <common/MsgTypes.h>
#include <common/Sizes.h>
#include <iostream>
#include "SoundSystem.h"

#define SOUND_ENGINE 1
#define SOUND_COUNTDOWN 2
#define SOUND_GO 4
#define SOUND_CRASH 5
#define SOUND_FIX 8
#define SOUND_EXPLOSION 9
#define SOUND_BRAKE 10

void SoundSystem::center(int32_t x, int32_t y) {
    posx = x;
    posy = y;
}

bool SoundSystem::isOnScreen(int32_t x, int32_t y){
    return hypot(x-posx, y-posy) < 1900;
}

void SoundSystem::playEngineSound(int32_t id, int32_t x, int32_t y, int32_t vel) {
    if ((id+1) > 0 && (id+1) < 14 && isOnScreen(x, y) && !Mix_Playing(id+1)){
        std::cerr << "playing engine" << std::endl;
        auto chunk = sounds.at(SOUND_ENGINE);
        Mix_PlayChannel((id+1), chunk, 0);
    }
    Mix_Volume((id+1), vel*3.6/METER_TO_PIXEL);
}

void SoundSystem::playCountdownSound(int32_t number) {
    if (number != 0)
        Mix_PlayChannel(14, sounds.at(SOUND_COUNTDOWN), 0);
    else
        Mix_PlayChannel(14, sounds.at(SOUND_GO), 0);
}

void SoundSystem::playEffectSound(int32_t effect) {
    if (effect == MSG_EFFECT_ROCK || effect == MSG_EFFECT_BOOST ||
    effect == MSG_EFFECT_MUD || effect == MSG_EFFECT_OIL){
        Mix_PlayChannel(15, sounds.at(effect), 0);
    }
}

void SoundSystem::playExplosionSound(int32_t x, int32_t y) {
    if (isOnScreen(x, y))
        Mix_PlayChannel(16, sounds.at(SOUND_EXPLOSION), 0);
}

void SoundSystem::playFixSound(int32_t x, int32_t y) {
    if (hypot(x-posx, y-posy) == 0)
        Mix_PlayChannel(16, sounds.at(SOUND_FIX), 0);
}

void SoundSystem::playCrashSound(int32_t x, int32_t y) {
    if (isOnScreen(x, y))
        Mix_PlayChannel(16, sounds.at(SOUND_CRASH), 0);
}

void SoundSystem::playBackgroundMusic() {
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(95);
}

SoundSystem::SoundSystem() : posx(0), posy(0) {
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
    Mix_AllocateChannels(17);

    /*------------------------------LOAD SOUNDS-------------------------------*/
    sounds.emplace(SOUND_ENGINE, Mix_LoadWAV("assets/sounds/engine.wav"));
    sounds.emplace(SOUND_COUNTDOWN, Mix_LoadWAV("assets/sounds/countdown.wav"));
    sounds.emplace(SOUND_GO, Mix_LoadWAV("assets/sounds/go.wav"));
    sounds.emplace(SOUND_CRASH, Mix_LoadWAV("assets/sounds/crash.wav"));
    sounds.emplace(SOUND_FIX, Mix_LoadWAV("assets/sounds/fix.wav"));
    sounds.emplace(SOUND_EXPLOSION, Mix_LoadWAV("assets/sounds/explosion.wav"));
    sounds.emplace(SOUND_BRAKE, Mix_LoadWAV("assets/sounds/brake.wav"));
    sounds.emplace(MSG_EFFECT_MUD, Mix_LoadWAV("assets/sounds/mud.wav"));
    sounds.emplace(MSG_EFFECT_BOOST, Mix_LoadWAV("assets/sounds/boost.wav"));
    sounds.emplace(MSG_EFFECT_ROCK, Mix_LoadWAV("assets/sounds/glass.wav"));
    sounds.emplace(MSG_EFFECT_OIL, Mix_LoadWAV("assets/sounds/oil.wav"));

    /*------------------------------LOAD MUSIC--------------------------------*/
    music = Mix_LoadMUS("assets/sounds/music.mp3");
}

SoundSystem::~SoundSystem() {
    for (auto& sound : sounds) {
        Mix_FreeChunk(sound.second);
    }
    Mix_FreeMusic(music);
    Mix_Quit();
}

void SoundSystem::playBrakesSound(int32_t x, int32_t y) {
    if (isOnScreen(x, y))
        Mix_PlayChannel(16, sounds.at(SOUND_BRAKE), 0);
}

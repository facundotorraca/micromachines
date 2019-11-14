//
// Created by javier on 10/11/19.
//

#include <chrono>
#include <SDL_messagebox.h>
#include "ScreenRecorder.h"

ScreenRecorder::ScreenRecorder() : recording(false), format(), current_output(nullptr),
    ctx(nullptr), width(0), height(0), recording_texture(nullptr){
}

void ScreenRecorder::startRecording(SDL_Renderer* renderer, int width, int height) {
    this->width = width;
    this->height = height;
    recording_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, width, height);
    buffer.clear();
    buffer.resize(width*height*3);
    ctx = sws_getContext(width, height, AV_PIX_FMT_RGB24, 1280, 720, AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string video_name(ctime(&time));
    video_name.erase(video_name.length()-1);
    current_output.reset(new OutputFormat(format, video_name+".mpeg"));
    this->recording = true;
}

void ScreenRecorder::recordFrame(SDL_Renderer *renderer) {
    if (recording) {
        int res = SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGB24, buffer.data(), width*3);
        if (res){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RendererReadPixels error", SDL_GetError(), nullptr);
        }
        current_output->writeFrame(buffer.data(), ctx, width);
    }
}

void ScreenRecorder::stopRecording() {
    this->recording = false;
    current_output->close();
    sws_freeContext(ctx);
    ctx = nullptr;
    current_output.reset(nullptr);
    SDL_DestroyTexture(recording_texture);
}

bool ScreenRecorder::isRecording() {
    return recording;
}

ScreenRecorder::~ScreenRecorder() {
    sws_freeContext(ctx);
    if (recording_texture){
        SDL_DestroyTexture(recording_texture);
    }
}

SDL_Texture *ScreenRecorder::getRecordingTexture() {
    return recording_texture;
}


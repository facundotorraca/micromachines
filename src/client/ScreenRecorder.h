//
// Created by javier on 10/11/19.
//

#ifndef MICROMACHINES_SCREENRECORDER_H
#define MICROMACHINES_SCREENRECORDER_H

#include <vector>
#include <SDL2/SDL_render.h>
#include <memory>
#include <client/ffmpeg/ThreadWriter.h>

class ScreenRecorder {
    int width, height;
    bool recording;
    std::vector<uint8_t> buffer;
    SDL_Texture* recording_texture;
    std::unique_ptr<ThreadWriter> writer;
    std::shared_ptr<ProtectedQueue<std::vector<uint8_t>>> queue;
public:
    ScreenRecorder();
    void startRecording(SDL_Renderer* renderer, int width, int height);
    void recordFrame(SDL_Renderer* renderer);
    void stopRecording();
    bool isRecording();
    SDL_Texture* getRecordingTexture();
    ~ScreenRecorder();
};


#endif //MICROMACHINES_SCREENRECORDER_H

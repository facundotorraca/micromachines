//
// Created by javier on 10/11/19.
//

#ifndef MICROMACHINES_SCREENRECORDER_H
#define MICROMACHINES_SCREENRECORDER_H

#include "ffmpeg/FormatContext.h"
#include "ffmpeg/OutputFormat.h"
extern "C" {
    #include <libswscale/swscale.h>
    #include <libavformat/avformat.h>
}
#include <vector>
#include <SDL2/SDL_render.h>
#include <memory>

class ScreenRecorder {
    bool recording;
    FormatContext format;
    std::unique_ptr<OutputFormat> current_output;
    SwsContext* ctx;
    int width, height;
    std::vector<uint8_t> buffer;
    SDL_Texture* recording_texture;
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

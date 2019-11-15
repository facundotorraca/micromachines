//
// Created by javier on 14/11/19.
//

#include <SDL_render.h>
#include "ThreadWriter.h"

void ThreadWriter::run() {
    while (this->running) {
        try {
            auto data = queue->pop();
            current_output->writeFrame(data.data(), ctx, width, height);
        } catch (ProtectedQueueError& e) {
            this->running = false;
        }
    }
}

ThreadWriter::ThreadWriter(
        std::shared_ptr<ProtectedQueue<std::vector<uint8_t>>>& queue, int w, int h) : queue(queue), width(w), height(h){
    ctx = sws_getContext(width, height, AV_PIX_FMT_RGB24, 640, 480, AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string video_name(ctime(&time));
    video_name.erase(video_name.length()-1);
    this->current_output.reset(new OutputFormat(format, video_name+".mpeg"));
}

ThreadWriter::~ThreadWriter() {
    current_output->close();
    current_output.reset();
    sws_freeContext(ctx);
}




//
// Created by javier on 14/11/19.
//

#include "ThreadWriter.h"
#include <chrono>
#include "OutputFormat.h"

void ThreadWriter::run() {
    while (this->running) {
        try {
            auto data = queue.pop();
            std::unique_lock<std::mutex> lock(mtx);
            if (current_output)
                current_output->writeFrame(data.data(), ctx, width, height);
        } catch (ProtectedQueueError& e) {
            this->running = false;
        }
    }
}

ThreadWriter::ThreadWriter(
        ProtectedQueue<std::vector<uint8_t>>& queue) : queue(queue), current_output(
        nullptr), ctx(nullptr), width(0), height(0){}

ThreadWriter::~ThreadWriter() {
    saveVideo();
}

void ThreadWriter::setup(int w, int h) {
    this->width = w;
    this->height = h;
    ctx = sws_getContext(w, h, AV_PIX_FMT_RGB24, 640, 480, AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string video_name(ctime(&time));
    video_name.erase(video_name.length()-1);
    this->current_output.reset(new OutputFormat(format, video_name+".mpeg"));
}

void ThreadWriter::saveVideo() {
    std::unique_lock<std::mutex> lock(mtx);
    if (current_output){
        current_output->close();
        current_output.reset();
        sws_freeContext(ctx);
    }
}




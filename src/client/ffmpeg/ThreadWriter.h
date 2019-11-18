//
// Created by javier on 14/11/19.
//

#ifndef MICROMACHINES_THREADWRITER_H
#define MICROMACHINES_THREADWRITER_H


#include <common/Thread.h>
#include <vector>
#include <common/ProtectedQueue.h>
#include "OutputFormat.h"
#include "FormatContext.h"
#include "OutputFormat.h"
extern "C" {
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}

class ThreadWriter : public Thread {
    ProtectedQueue<std::vector<uint8_t>>& queue;
    FormatContext format;
    std::unique_ptr<OutputFormat> current_output;
    SwsContext* ctx;
    int width, height;
    std::mutex mtx;
public:
    explicit ThreadWriter(ProtectedQueue<std::vector<uint8_t>>& queue);
    void run() override;
    void setup(int w, int h);

    void saveVideo();
    ~ThreadWriter() override;
};


#endif //MICROMACHINES_THREADWRITER_H

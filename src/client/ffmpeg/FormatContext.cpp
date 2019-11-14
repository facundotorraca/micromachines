#include "FormatContext.h"
#include <stdexcept>
#include <string>
extern "C" {
#include <libavformat/avformat.h>
}

FormatContext::FormatContext() {
    av_register_all();
    this->pFormatCtx = avformat_alloc_context();
}

FormatContext::~FormatContext() {
    avformat_free_context(this->pFormatCtx);
}

AVFormatContext * FormatContext::getContext() const {
    return this->pFormatCtx;
}

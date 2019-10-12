#include "ProtectedQueueMatch.h"
#include "Player.h"
#include "ProtectedQueueError.h"
#include <mutex>

/*--------------Public--------------*/
ProtectedQueueMatch::ProtectedQueueMatch(size_t max_q_len) {
    this->max_q_len = max_q_len;
    this->q_closed = false;
}

void ProtectedQueueMatch::push(Match* match) {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    while (this->queue.size() >= this->max_q_len) {
        this->cv_push.wait(lock);
    }

    this->queue.push(match);
    this->cv_pop.notify_all();
}

Match* ProtectedQueueMatch::pop() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    while (this->queue.empty() && !this->q_closed) {
        this->cv_pop.wait(lock);
    }

    if (this->queue.empty()) {
        throw ProtectedQueueError("ProtectedQueue: POP Error");
    } else {
        Match* match = this->queue.front();
        this->queue.pop();
        this->cv_push.notify_all();
        return match;
    }
}

bool ProtectedQueueMatch::empty() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    return this->queue.empty();
}

void ProtectedQueueMatch::close() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    this->q_closed = true;
    //Notify free pass to take!
    this->cv_pop.notify_all();
}

bool ProtectedQueueMatch::closed() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    return this->q_closed;
}

/*--------------Private--------------*/
ProtectedQueueMatch::~ProtectedQueueMatch() {}



#pragma once
#include <mutex>
#include <thread>

#include "6502/6502.h"

namespace RT6502::Threads {

class RT6502Thread {
    std::jthread Worker;

    bool IsRunning = false;

    // mutex
    std::mutex Mtx;
    std::condition_variable Cv;

   public:
    RT6502 Emulator;

    RT6502Thread();
    ~RT6502Thread();

    void Start();
    void Pause();

   private:
    void Run(const std::stop_token& stopToken);
};
}  // namespace RT6502::Threads
#pragma once
#include <mutex>
#include <thread>

#include "6502/6502.h"

namespace RT6502::Threads {

class RT6502Thread : public RT6502 {
    std::jthread Worker;

    bool IsRunning = false;

    // mutex
    std::mutex Mtx;
    std::condition_variable Cv;

   public:
    RT6502Thread();
    ~RT6502Thread();

    void Start();
    void Pause();

    void Reset(const Word startAddress = 0x0000) noexcept;
    bool LoadFile(const char*);

   private:
    void Run(const std::stop_token& stopToken);
};
}  // namespace RT6502::Threads
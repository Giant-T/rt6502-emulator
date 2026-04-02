#pragma once

#include <chrono>

namespace RT6502 {

using namespace std::chrono;

class StopWatch {
    time_point<steady_clock> StartTime;

    nanoseconds ElapsedTime;
    bool IsRunning = false;

   public:
    void Start();
    void Resume(const time_point<steady_clock>& currentTime);
    void Resume();
    void Pause();
    void Reset();

    [[nodiscard]] nanoseconds GetDuration(const time_point<steady_clock>& currentTime) const;
    [[nodiscard]] nanoseconds GetDuration() const;
};

}  // namespace RT6502

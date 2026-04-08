#include "6502/stopwatch.h"

void RT6502::StopWatch::Start() {
    Reset();
    Resume();
}

void RT6502::StopWatch::Resume(const time_point<steady_clock>& currentTime) {
    if (!IsRunning) {
        IsRunning = true;
        StartTime = currentTime;
    }
}

void RT6502::StopWatch::Resume() {
    Resume(steady_clock::now());
}

void RT6502::StopWatch::Pause() {
    if (IsRunning) {
        IsRunning = false;
        ElapsedTime += steady_clock::now() - StartTime;
    }
}

void RT6502::StopWatch::Reset() {
    IsRunning = false;
    ElapsedTime = nanoseconds::zero();
}

std::chrono::nanoseconds RT6502::StopWatch::GetDuration(const time_point<steady_clock>& currentTime) const {
    if (IsRunning) {
        return ElapsedTime + (currentTime - StartTime);
    }

    return ElapsedTime;
}

std::chrono::nanoseconds RT6502::StopWatch::GetDuration() const {
    return GetDuration(steady_clock::now());
}
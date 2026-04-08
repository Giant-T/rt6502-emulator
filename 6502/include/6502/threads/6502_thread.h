#pragma once
#include <condition_variable>
#include <mutex>
#include <thread>

#include "6502/6502.h"
#include "6502/stopwatch.h"

namespace RT6502::Threads {

class RT6502Thread final : public RT6502 {
    std::jthread Worker;

    bool IsRunning = false;

    // mutex
    std::mutex Mtx;
    std::condition_variable Cv;

    // Statistiques
    StopWatch ExecutionTime;
    time_point<steady_clock> CycleLastEndTime = steady_clock::now();
    nanoseconds LastCycleInternalExecutionTime = nanoseconds::zero();
    nanoseconds LastCycleSimulatedExecutionTime = nanoseconds::zero();
    nanoseconds TotalCycleElapsedTime = nanoseconds::zero();

   public:
    RT6502Thread();
    ~RT6502Thread();

    void Start();
    void Pause();

    void Reset(Word startAddress = 0x0000);
    bool LoadFile(const char*);

    void ResetStats();

    template <class T = nanoseconds>
    T AverageCycleElapsedTime() const {
        if (CyclesCounter == 0)
            return T(0);
        return duration_cast<T>(TotalCycleElapsedTime / CyclesCounter);
    }

    const auto& GetLastCycleInternalExecutionTime() const { return LastCycleInternalExecutionTime; }
    const auto& GetLastCycleSimulatedExecutionTime() const { return LastCycleSimulatedExecutionTime; }
    const auto& GetTotalCycleElapsedTime() const { return TotalCycleElapsedTime; }
    auto GetExpectedExecutedCycles() const { return ExecutionTime.GetDuration() / ClockSpeed.CycleDuration(); }
    auto GetExpectedExecutedCycles(const time_point<steady_clock>& currentTime) const { return ExecutionTime.GetDuration(currentTime) / ClockSpeed.CycleDuration(); }
    auto GetCyclesMissingBetweenRealAndSimulated() const { return static_cast<signed long long>(CyclesCounter - GetExpectedExecutedCycles()); }
    auto GetCyclesMissingBetweenRealAndSimulated(const time_point<steady_clock>& currentTime) const { return static_cast<signed long long>(CyclesCounter - GetExpectedExecutedCycles(currentTime)); }
    auto GetExecutionTime() const { return ExecutionTime.GetDuration(); }

    const auto& Running() const { return IsRunning; }

   private:
    void Run(const std::stop_token& stopToken);
    void ExecuteCycle();
};
}  // namespace RT6502::Threads
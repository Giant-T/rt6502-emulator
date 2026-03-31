#pragma once
#include <mutex>
#include <thread>

#include "6502/6502.h"

namespace RT6502::Threads {

class RT6502Thread final : public RT6502 {
    std::jthread Worker;

    bool IsRunning = false;

    // mutex
    std::mutex Mtx;
    std::condition_variable Cv;

    // Statistiques
    time_point<steady_clock> EmulationStartTime = high_resolution_clock::now();
    time_point<steady_clock> CycleLastEndTime = high_resolution_clock::now();
    nanoseconds LastCycleInternalExecutionTime = nanoseconds::zero();
    nanoseconds LastCycleSimulatedExecutionTime = nanoseconds::zero();
    nanoseconds TotalCycleElapsedTime = nanoseconds::zero();

   public:
    RT6502Thread();
    ~RT6502Thread();

    void Start();
    void Pause();

    void Reset(const Word startAddress = 0x0000);
    bool LoadFile(const char*);

    void ResetStats();

    template <class T>
    T AverageCycleElapsedTime() const {
        if (CyclesCounter == 0)
            return T(0);
        return duration_cast<T>(TotalCycleElapsedTime / CyclesCounter);
    }

    const auto& GetLastCycleInternalExecutionTime() const { return LastCycleInternalExecutionTime; }
    const auto& GetLastCycleSimulatedExecutionTime() const { return LastCycleSimulatedExecutionTime; }
    const auto& GetTotalCycleElapsedTime() const { return TotalCycleElapsedTime; }
    const auto& GetExpectedExecutedCycles(const time_point<steady_clock>& currentTime = high_resolution_clock::now()) const { return (currentTime - EmulationStartTime) / ClockSpeed.CycleDuration(); }
    const auto& GetCyclesMissingBetweenRealAndSimulated(const time_point<steady_clock>& currentTime = high_resolution_clock::now()) const { return GetExpectedExecutedCycles(currentTime) - CyclesCounter; }

   private:
    void Run(const std::stop_token& stopToken);
    void ExecuteCycle();
};
}  // namespace RT6502::Threads
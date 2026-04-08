#include "6502/threads/6502_thread.h"

#include <functional>

#ifdef _WINDOWS
#include <windows.h>
#endif

RT6502::Threads::RT6502Thread::RT6502Thread() : Worker(std::bind_front(&RT6502Thread::Run, this)) {
#ifdef _WINDOWS
    SetThreadPriority(Worker.native_handle(), THREAD_PRIORITY_TIME_CRITICAL);
#endif
}

RT6502::Threads::RT6502Thread::~RT6502Thread() {
    Worker.request_stop();
    Cv.notify_all();
}

void RT6502::Threads::RT6502Thread::Start() {
    IsRunning = true;
    Cv.notify_all();
}

void RT6502::Threads::RT6502Thread::Pause() {
    IsRunning = false;
}

void RT6502::Threads::RT6502Thread::Reset(const Word startAddress) {
    Pause();                     // Arrêter l'émulateur si il s'exécute
    std::scoped_lock lock(Mtx);  // Attendre d'avoir le lock

    ExecutionTime.Reset();
    ResetStats();

    RT6502::Reset(startAddress);
}

bool RT6502::Threads::RT6502Thread::LoadFile(const char* filepath) {
    Pause();                     // Arrêter l'émulateur si il s'exécute
    std::scoped_lock lock(Mtx);  // Attendre d'avoir le lock

    return RT6502::LoadFile(filepath);
}

void RT6502::Threads::RT6502Thread::ResetStats() {
    LastCycleInternalExecutionTime = nanoseconds::zero();
    LastCycleSimulatedExecutionTime = nanoseconds::zero();
    TotalCycleElapsedTime = nanoseconds::zero();
}

void RT6502::Threads::RT6502Thread::Run(const std::stop_token& stopToken) {
    std::unique_lock lock(Mtx);

    while (!stopToken.stop_requested()) {
        Cv.wait(lock, [this, stopToken] { return IsRunning || stopToken.stop_requested(); });  // Attendre qu'on puisse s'exécuter
        CycleLastEndTime = steady_clock::now();
        ExecutionTime.Resume(CycleLastEndTime);

        // Continuer l'exécution jusqu'à ce qu'on soit demandé d'arrêter.
        while (!stopToken.stop_requested() && IsRunning) {
            ExecuteCycle();
        }

        ExecutionTime.Pause();
    }
}

void RT6502::Threads::RT6502Thread::ExecuteCycle() {
    const time_point<steady_clock> cycleStartTime = steady_clock::now();

    RT6502::ExecuteCycle();

    time_point<steady_clock> cycleEndTime = steady_clock::now();
    LastCycleInternalExecutionTime = cycleEndTime - cycleStartTime;

    // Attendre que sa fasse assez longtemps depuis l'exécution du cycle précédent
    while (GetCyclesMissingBetweenRealAndSimulated(cycleEndTime) >= 0) {
        cycleEndTime = steady_clock::now();
    }

    // Statistiques sur l'exécution du cycle
    LastCycleSimulatedExecutionTime = cycleEndTime - CycleLastEndTime;
    TotalCycleElapsedTime += LastCycleSimulatedExecutionTime;

    CycleLastEndTime = cycleEndTime;
}
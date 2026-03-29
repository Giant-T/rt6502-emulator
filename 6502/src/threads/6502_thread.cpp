#include "6502/threads/6502_thread.h"

#include <functional>

RT6502::Threads::RT6502Thread::RT6502Thread() : Worker(std::bind_front(&RT6502Thread::Run, this)) {
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

void RT6502::Threads::RT6502Thread::Reset(const Word startAddress) noexcept {
    Pause();                     // Arrêter l'émulateur si il s'exécute
    std::scoped_lock lock(Mtx);  // Attendre d'avoir le lock

    RT6502::Reset(startAddress);
}

bool RT6502::Threads::RT6502Thread::LoadFile(const char* filepath) {
    Pause();                     // Arrêter l'émulateur si il s'exécute
    std::scoped_lock lock(Mtx);  // Attendre d'avoir le lock

    return RT6502::LoadFile(filepath);
}

void RT6502::Threads::RT6502Thread::Run(const std::stop_token& stopToken) {
    std::unique_lock lock(Mtx);

    while (!stopToken.stop_requested()) {
        Cv.wait(lock, [this, stopToken] { return IsRunning || stopToken.stop_requested(); });  // Attendre qu'on puisse s'exécuter

        // Revalider si on doit terminer le thread
        if (stopToken.stop_requested()) return;

        Execute();
    }
}
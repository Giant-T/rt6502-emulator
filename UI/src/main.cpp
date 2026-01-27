#include <6502/6502.h>

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>

ftxui::Component App(ftxui::ScreenInteractive& screen) {
    return ftxui::CatchEvent(
        ftxui::Container::Vertical({}),
        [&](const ftxui::Event& event) {
            if (event.character() == "q")
                screen.Exit();

            return true;
        }
    );
}

int main() {
    rt6502::rt6502 emulator;
    emulator.reset();

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    screen.Loop(App(screen));

    return EXIT_SUCCESS;
}

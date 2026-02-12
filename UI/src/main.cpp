#include <6502/6502.h>
#include <6502/decode.h>

#include <cstdint>
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <utility>

#include "6502/memory.h"

enum : uint8_t { TOP_SIZE = 18 };

ftxui::Component KeyboardEvents(ftxui::ScreenInteractive& screen, ftxui::Component component) {
    return ftxui::CatchEvent(
        std::move(component),
        [&](const ftxui::Event& event) {
            if (event.character() == "q") {  // Exits the program when pressing 'q'
                screen.Exit();
                return true;
            }

            return false;
        }
    );
}

ftxui::Element RegistersTable(RT6502::RT6502& emulator) {
    const auto oper = RT6502::Decode::Decode(emulator.Cpu.PC, emulator.Mem);

    auto table = ftxui::Table({
        {"Register", "Values"},
        {"PC", std::format("{:04X}", emulator.Cpu.PC)},
        {"SP", std::format("{:02X}", emulator.Cpu.SP)},
        {"A", std::format("{:02X}", emulator.Cpu.A)},
        {"X", std::format("{:02X}", emulator.Cpu.X)},
        {"Y", std::format("{:02X}", emulator.Cpu.Y)},
        {"N", std::to_string(emulator.Cpu.PS.N)},
        {"V", std::to_string(emulator.Cpu.PS.V)},
        {"B", std::to_string(emulator.Cpu.PS.B)},
        {"D", std::to_string(emulator.Cpu.PS.D)},
        {"I", std::to_string(emulator.Cpu.PS.I)},
        {"Z", std::to_string(emulator.Cpu.PS.Z)},
        {"C", std::to_string(emulator.Cpu.PS.C)},
        {"Decode", oper.Display()},
    });

    table.SelectColumns(0, -1).Border();
    table.SelectColumn(1).Border();

    table.SelectRow(0).Decorate(ftxui::bold);
    table.SelectRow(0).Border(ftxui::DOUBLE);

    return table.Render();
}

ftxui::Component RegistersLayout(RT6502::RT6502& emulator) {
    return ftxui::Renderer(
        [&] {
            return ftxui::vbox({ftxui::text("Registers"), ftxui::separator(), RegistersTable(emulator)});
        }
    );
}

ftxui::Component AssemblyLayout() {
    return ftxui::Renderer(
        [] {
            return ftxui::vbox({
                ftxui::text("Assembly"),
                ftxui::separator(),
                ftxui::text("Informations") | ftxui::flex,
            });
        }
    );
}

ftxui::Component MemoryLayout(RT6502::RT6502& emulator) {
    static std::string test;

    ftxui::Component addressInput = ftxui::Input(&test, "0x20");

    return ftxui::Renderer([&] {
        return ftxui::vbox({
            ftxui::text("Memory"),
            ftxui::separator(),
            ftxui::hbox(ftxui::text("Adresse: "), addressInput->Render()),
        });
    });
}

ftxui::Component AppLayout(int& topSize, int& registersSize, RT6502::RT6502& emulator) {
    auto registers = RegistersLayout(emulator);
    auto assembly = AssemblyLayout();
    auto memory = MemoryLayout(emulator);

    auto top = ftxui::ResizableSplitLeft(registers, memory, &registersSize);

    return ftxui::ResizableSplitTop(top, assembly, &topSize) | ftxui::border;
}

ftxui::Component App(ftxui::ScreenInteractive& screen, int& topSize, int& registersSize, RT6502::RT6502& emulator) {
    return KeyboardEvents(
        screen,
        AppLayout(topSize, registersSize, emulator)
    );
}

int main() {
    RT6502::RT6502 emulator;

    emulator.Reset();
    emulator.Reset();
    emulator.Execute();
    emulator.Execute();
    emulator.Execute();
    emulator.Execute();
    emulator.Execute();

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    int topSize = TOP_SIZE;
    int registersSize = TOP_SIZE;

    screen.Loop(App(screen, topSize, registersSize, emulator));

    return EXIT_SUCCESS;
}

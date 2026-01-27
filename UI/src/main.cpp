#include <6502/6502.h>
#include <6502/decode.h>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>

#include "ftxui/dom/table.hpp"

using namespace ftxui;

int main() {
    RT6502::RT6502 emulator;
    emulator.Reset();
    emulator.Execute();
    emulator.Execute();
    emulator.Execute();
    emulator.Execute();
    emulator.Execute();

    const auto oper = RT6502::Decode::Decode(emulator.Cpu.PC, emulator.Memory);

    auto table = Table({
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

    table.SelectAll().Border(LIGHT);

    // Add border around the first column.
    table.SelectColumn(0).Border(LIGHT);

    // Make first row bold with a double border.
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(DOUBLE);

    // Select row from the second to the last.
    auto content = table.SelectRows(1, -1);

    // Alternate in between 3 colors.
    content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
    content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
    content.DecorateCellsAlternateRow(color(Color::White), 3, 2);

    auto document = table.Render();
    auto screen = Screen::Create(Dimension::Fit(document, true));
    Render(screen, document);
    screen.Print();
    std::cout << '\n';

    return EXIT_SUCCESS;
}
#include <6502/6502.h>
#include <6502/decode.h>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>

#include "ftxui/dom/table.hpp"

using namespace ftxui;

int main() {
    rt6502::rt6502 emulator;
    emulator.reset();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();

    const auto oper = rt6502::decode::decode(emulator.cpu.PC, emulator.memory);

    auto table = Table({
        {"Register", "Values"},
        {"PC", std::format("{:04X}", emulator.cpu.PC)},
        {"SP", std::format("{:02X}", emulator.cpu.SP)},
        {"A", std::format("{:02X}", emulator.cpu.A)},
        {"X", std::format("{:02X}", emulator.cpu.X)},
        {"Y", std::format("{:02X}", emulator.cpu.Y)},
        {"N", std::to_string(emulator.cpu.PS.N)},
        {"V", std::to_string(emulator.cpu.PS.V)},
        {"B", std::to_string(emulator.cpu.PS.B)},
        {"D", std::to_string(emulator.cpu.PS.D)},
        {"I", std::to_string(emulator.cpu.PS.I)},
        {"Z", std::to_string(emulator.cpu.PS.Z)},
        {"C", std::to_string(emulator.cpu.PS.C)},
        {"Decode", oper.display()},
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
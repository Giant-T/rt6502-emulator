#include "app.h"

#include <cctype>
#include <cstdint>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/box.hpp>
#include <string>

#include "6502/decode.h"
#include "6502/memory.h"
#include "6502/threads/6502_thread.h"

enum : uint8_t { HEX = 16 };

App::App() : layoutHeight(LAYOUT_HEIGHT), layoutWidth(LAYOUT_WIDTH) {
    emulator.Reset();
}

App::App(const std::string& fileName, int firstMemAddr, int layoutHeight, int layoutWidth) : layoutHeight(layoutHeight), layoutWidth(layoutWidth), bottomLayoutWidth(layoutWidth) {
    emulator.LoadFile(fileName.data());
    emulator.Reset(firstMemAddr);
}

ftxui::Component App::KeyboardEvents(ftxui::ScreenInteractive& screen, ftxui::Component component) {
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

ftxui::Element App::RegistersTable() {
    const auto oper = RT6502::Decode::Decode(emulator.Cpu.PC, emulator.Mem);
    std::string operStr = oper.Display();
    if (operStr.length() < OPER_WIDTH)
        operStr.append(OPER_WIDTH - operStr.length(), ' ');

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
        {"Decode", operStr},
    });

    table.SelectColumns(0, -1).Border();
    table.SelectColumn(1).Border();

    table.SelectRow(0).Decorate(ftxui::bold);
    table.SelectRow(0).Border(ftxui::DOUBLE);

    return table.Render();
}

ftxui::Component App::RegistersLayout() {
    return ftxui::Renderer(
        [&] {
            return ftxui::vbox({ftxui::text("Registers"), ftxui::separator(), RegistersTable()});
        }
    );
}

ftxui::Component App::AssemblyLayout() {
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

ftxui::Component App::AddressInput() {
    static std::string address;
    ftxui::InputOption options{};
    options.multiline = false;

    options.on_change = [&] {
        if (address.empty()) {
            return;
        }
        if (std::isxdigit(address.back()))
            return;

        address.pop_back();
    };

    options.on_enter = [&] {
        // TODO(william): faire la recherche et refresh l'affichage
        if (address.empty())
            this->address = 0;
        else {
            const int tableWidth = layoutWidth / 5;
            const int tableHeight = layoutHeight;
            const int numberOfCells = tableWidth * tableHeight;

            try {
                this->address = std::stoi(address, nullptr, HEX);

                if (this->address + numberOfCells >= RT6502::Memory::MAX_MEMORY) {
                    this->address = RT6502::Memory::MAX_MEMORY - numberOfCells - 1;
                    address = std::format("{:x}", this->address);
                }
            } catch (...) {
                this->address = RT6502::Memory::MAX_MEMORY - numberOfCells - 1;
                address = std::format("{:x}", this->address);
            }
        }
    };

    ftxui::Component addressInput = ftxui::Input(
        &address,
        "Search at address",
        options
    );

    return addressInput;
}

ftxui::Component App::MemoryDisplay() const {
    return ftxui::Renderer([&] {
        const int tableWidth = layoutWidth / 5;
        const int tableHeight = layoutHeight;

        std::vector<std::vector<std::string>> memoryTable{};
        memoryTable.reserve(tableHeight);

        for (int y = 0; y < tableHeight; ++y) {
            std::vector<std::string> row;
            row.reserve(tableWidth);
            for (int x = 0; x < tableWidth; ++x) {
                int idx = address + (y * tableWidth) + x;
                row.push_back(std::format("{:#04X}", emulator.Mem[idx]));
            }
            memoryTable.push_back(row);
        }

        auto table = ftxui::Table(memoryTable);

        for (int col = 0; col < tableWidth - 1; ++col) {
            table.SelectColumn(col).BorderRight();
        }

        return table.Render();
    });
}

ftxui::Component App::MemoryLayout() {
    return ftxui::Container::Vertical({
        ftxui::Renderer([&] {
            return ftxui::vbox({
                ftxui::text("Memory at address: " + std::format("{:#04X}", address)),
                ftxui::separator(),
            });
        }),
        AddressInput(),
        MemoryDisplay(),
    });
}

ftxui::Component App::MetricsLayout() const {
    return ftxui::Renderer([&] {
        return ftxui::vbox({
            ftxui::text("Metrics"),
            ftxui::separator(),
            ftxui::text(std::format("Execution Time: {:%H:%M:%S}", emulator.GetExecutionTime())),
            ftxui::text(std::format("Frequency: {}", RT6502::Frequency(emulator.AverageCycleElapsedTime()))),
            ftxui::text(std::format("PC: {:04X}", emulator.Cpu.PC - 1)),
            ftxui::text(std::format("Total Cycles [Real]: {}", emulator.GetExpectedExecutedCycles())),
            ftxui::text(std::format("Total Cycles [Simulated]: {}", emulator.CyclesCounter)),
            ftxui::text(std::format("Total Cycles Diff: {}", emulator.GetCyclesMissingBetweenRealAndSimulated())),
            ftxui::text(std::format("Total Cycle Duration [Simulated]: {}", emulator.GetTotalCycleElapsedTime())),
            ftxui::text(std::format("Last Cycle Duration [Internal]: {}", emulator.GetLastCycleInternalExecutionTime())),
            ftxui::text(std::format("Last Cycle Duration [Simulated]: {}", emulator.GetLastCycleSimulatedExecutionTime())),
            ftxui::text(std::format("Expected Average Cycle Duration: {}", emulator.ClockSpeed.CycleDuration())),
            ftxui::text(std::format("Average Cycle Duration [Internal]: {}", emulator.AverageCycleInternalExecutionTime())),
            ftxui::text(std::format("Average Cycle Duration [Simulated]: {}", emulator.AverageCycleElapsedTime())),
            ftxui::text(std::format("Remaining Duration: {}", emulator.ClockSpeed.CycleDuration() - emulator.AverageCycleElapsedTime())),
        });
    });
}

ftxui::Component App::VerticalLayout() {
    auto registers = RegistersLayout();
    auto assembly = AssemblyLayout();
    auto memory = MemoryLayout();
    auto metrics = MetricsLayout();

    auto top = ftxui::ResizableSplitRight(memory, registers, &layoutWidth);
    auto bottom = ftxui::ResizableSplitRight(metrics, assembly, &bottomLayoutWidth);

    return ftxui::ResizableSplitTop(top, bottom, &layoutHeight) |
           ftxui::border;
}

ftxui::Component App::MainLayout(ftxui::ScreenInteractive& screen) {
    return KeyboardEvents(
        screen,
        VerticalLayout()
    );
}

void App::Run() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    ftxui::Loop loop{&screen, MainLayout(screen)};

    emulator.Start();

    while (!loop.HasQuitted()) {
        // TODO(william): Check voir si ça cause des erreurs sinon ça marche live
        screen.RequestAnimationFrame();

        loop.RunOnce();
    }
}

#pragma once

#include <cstdint>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/node.hpp>

#include "6502/6502.h"

class App {
    enum : uint8_t { LAYOUT_HEIGHT = 18,
                     LAYOUT_WIDTH = 18 };

   public:
    App();
    explicit App(const std::string&, int = 0, int = LAYOUT_HEIGHT, int = LAYOUT_WIDTH);
    App(App&&) = default;
    App(const App&) = default;
    App& operator=(App&&) = default;
    App& operator=(const App&) = default;
    ~App() = default;

    void Run();

   private:
    RT6502::RT6502 emulator{};
    int layoutHeight;
    int layoutWidth;
    int address{0};

    [[nodiscard]] ftxui::Component MainLayout(ftxui::ScreenInteractive&);
    [[nodiscard]] ftxui::Element RegistersTable();
    [[nodiscard]] ftxui::Component RegistersLayout();
    [[nodiscard]] ftxui::Component AssemblyLayout();
    [[nodiscard]] ftxui::Component VerticalLayout();
    [[nodiscard]] ftxui::Component AddressInput();
    [[nodiscard]] ftxui::Component MemoryLayout();
    [[nodiscard]] ftxui::Component MemoryDisplay() const;
    [[nodiscard]] static ftxui::Component KeyboardEvents(ftxui::ScreenInteractive&, ftxui::Component);
};

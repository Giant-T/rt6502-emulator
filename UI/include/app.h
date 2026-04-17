#pragma once

#include <cstdint>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/node.hpp>

#include "6502/threads/6502_thread.h"

class App {
    enum : uint8_t { LAYOUT_HEIGHT = 19,
                     LAYOUT_WIDTH = 50,
                     OPER_WIDTH = 13 };

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
    RT6502::Threads::RT6502Thread emulator;
    int layoutHeight;
    int layoutWidth;
    int bottomLayoutWidth;
    uint32_t address{0};
    std::vector<std::string> assembly;

    [[nodiscard]] ftxui::Component MainLayout(ftxui::ScreenInteractive&);
    [[nodiscard]] std::vector<std::string> DecodeFrom(int);
    [[nodiscard]] ftxui::Component ActionsLayout();
    [[nodiscard]] ftxui::Element RegistersTable();
    [[nodiscard]] ftxui::Component RegistersLayout();
    [[nodiscard]] ftxui::Component AssemblyLayout();
    [[nodiscard]] ftxui::Component VerticalLayout();
    [[nodiscard]] ftxui::Component AddressInput();
    [[nodiscard]] ftxui::Component MemoryLayout();
    [[nodiscard]] ftxui::Component MemoryDisplay() const;
    [[nodiscard]] ftxui::Component MetricsLayout() const;
    [[nodiscard]] ftxui::Component KeyboardEvents(ftxui::ScreenInteractive&, ftxui::Component);
};

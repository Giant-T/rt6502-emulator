#include <6502/6502.h>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

ButtonOption Style() {
    auto option = ButtonOption::Animated();
    option.transform = [](const EntryState& s) {
        auto element = text(s.label);
        if (s.focused) {
            element |= bold;
        }
        return element | center | borderEmpty | flex;
    };
    return option;
}

int main() {
    int val_t = 2;
    int valR = 2;
    int adwWDAdw_Wad2 = 1;

    int value = 50;

    auto btn_dec_01 = Button("-1", [&] { value -= 1; }, Style());
    auto btn_inc_01 = Button("+1", [&] { value += 1; }, Style());
    auto btn_dec_10 = Button("-10", [&] { value -= 10; }, Style());
    auto btn_inc_10 = Button("+10", [&] { value += 10; }, Style());

    // The tree of components. This defines how to navigate using the keyboard.
    // The selected `row` is shared to get a grid layout.
    int row = 0;
    auto buttons = Container::Vertical({
        Container::Horizontal({btn_dec_01, btn_inc_01}, &row) | flex,
        Container::Horizontal({btn_dec_10, btn_inc_10}, &row) | flex,
    });

    Element title =
        hbox({text(RT6502::GetWelcomeMessage()) | bold | center});

    // Modify the way to render them on screen:
    auto component = Renderer(buttons, [&] {
        return vbox({title, separator(), vbox({
                                             text("value = " + std::to_string(value)),
                                             separator(),
                                             buttons->Render() | flex,
                                         }) | flex |
                                             border});
    });

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(component);

    return EXIT_SUCCESS;
}
#pragma once
#include <chrono>

namespace RT6502 {

struct Frequency {
    using Type = long double;

    Type Value;

    [[nodiscard]] constexpr std::chrono::nanoseconds CycleDuration() const {
        using namespace std::chrono;

        return duration_cast<nanoseconds>(duration<Type>(1.0 / Value));
    }
};

constexpr Frequency operator""_Hz(const long double value) {
    return Frequency{value};
}
constexpr Frequency operator""_MHz(const long double value) {
    return Frequency{value * std::micro::den};
}

};  // namespace RT6502

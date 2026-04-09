#pragma once
#include <chrono>

namespace RT6502 {

struct Frequency {
    using Type = long double;

    Type Hertz;

    constexpr explicit Frequency(const Type hertz) : Hertz(hertz) {}
    template <class T>
    constexpr explicit Frequency(const T period) : Hertz(period.count() == 0 ? 1 : T::period::den / period.count()) {}

    [[nodiscard]] constexpr std::chrono::nanoseconds CycleDuration() const {
        using namespace std::chrono;

        return duration_cast<nanoseconds>(duration<Type>(1.0 / Hertz));
    }
};

constexpr Frequency operator""_Hz(const long double hertz) {
    return Frequency{hertz};
}
constexpr Frequency operator""_MHz(const long double hertz) {
    return Frequency{hertz * std::micro::den};
}

}  // namespace RT6502

template <>
struct std::formatter<RT6502::Frequency> : std::formatter<RT6502::Frequency::Type> {
    static auto format(const RT6502::Frequency& id, std::format_context& ctx) {
        return std::format_to(ctx.out(), "{}MHz", id.Hertz / std::micro::den);
    }
};

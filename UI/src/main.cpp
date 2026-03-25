#include <6502/6502.h>
#include <6502/decode.h>

#include "app.h"

int main() {
    App app{"ressources/6502_functional_test.bin", 0x0400};
    app.Run();

    return EXIT_SUCCESS;
}

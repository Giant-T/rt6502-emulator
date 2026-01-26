/**
 * Contient la liste des instructions CPU.
 *
 * @authors Nicolas Béland
 * @date 2026-01-23
 */

#pragma once

#include "types.h"
#include "cpu.h"

namespace rt6502::instruction_set {

void A9_LDA_IM(Byte, CPU&);

void LDA(Byte, CPU&);

}
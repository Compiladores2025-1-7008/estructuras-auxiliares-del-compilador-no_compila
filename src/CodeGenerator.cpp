#include "CodeGenerator.hpp"
#include <string>

std::string CodeGenerator::newTemp() {
    return "t" + std::to_string(nextTemp++);
}

std::string CodeGenerator::newLabel() {
    return "L" + std::to_string(nextLabel++);
}

void CodeGenerator::reset() {
    nextTemp = 0;
    nextLabel = 0;
}

#include "CodeGenerator.hpp"
#include <string>

/**
 * Genera un nuevo nombre para una variable temporal.
 * std::string Nombre del temporal (ej. "t0", "t1")
 */
std::string CodeGenerator::newTemp() {
    return "t" + std::to_string(nextTemp++);
}

/**
 * Genera una nueva etiqueta para control de flujo.
 * std::string Nombre de la etiqueta (ej. "L0", "L1")
 */
std::string CodeGenerator::newLabel() {
    return "L" + std::to_string(nextLabel++);
}

/**
 * Reinicia los contadores de temporales y etiquetas.
 */
void CodeGenerator::reset() {
    nextTemp = 0;
    nextLabel = 0;
}

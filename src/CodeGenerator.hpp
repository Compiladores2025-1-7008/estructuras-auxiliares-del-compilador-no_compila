#pragma once
#include <string>

class CodeGenerator {
private:
    int nextTemp = 0; // Contador para temporales
    int nextLabel = 0; // Contador para etiquetas

public:
    // Genera un nuevo nombre para una variable temporal.
    std::string newTemp(); 
    // Genera una nueva etiqueta para control de flujo.
    std::string newLabel() ;
    // Reinicia los contadores de temporales y etiquetas.
    void reset() ;
};

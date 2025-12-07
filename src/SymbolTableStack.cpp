#include "SymbolTableStack.hpp"
#include <stdexcept>

// Crear nuevo ámbito (tabla vacía)
void SymbolTableStack::pushScope() {
    stack.push_back(new SymbolTable());
}

// Quitar el ámbito actual (no se libera)
void SymbolTableStack::popScope() {
    if (stack.empty())
        throw std::runtime_error("popScope: pila vacía");

    // No liberar 
    stack.pop_back();
}

// Sale el ámbito y retorna la referencia sin liberarla
SymbolTable* SymbolTableStack::popSymbolTable() {
    if (stack.empty())
        throw std::runtime_error("popSymbolTable: pila vacía");

    SymbolTable* top = stack.back();
    stack.pop_back();
    return top;  // sin liberar
}

// Inserta un símbolo en el ámbito más interno (el actual)
// Retorna true si tuvo éxito, false si ya existe 
bool SymbolTableStack::insertTop(const SymbolEntry &entry) {
    if (stack.empty())
        return false;
    return stack.back()->insert(entry);
}

// Inserta un símbolo en el ámbito Global (el primero de la pila)
// Sirve para declarar funciones o variables globales desde cualquier punto
bool SymbolTableStack::insertBase(const SymbolEntry &entry) {
    if (stack.empty())
        return false;
    return stack.front()->insert(entry);
}

// Busca un símbolo en el ámbito más interno (el actual)
const SymbolEntry* SymbolTableStack::lookupTop(const std::string &id) {
    if (stack.empty())
        return nullptr;
    return stack.back()->lookup(id);
}

// Busca un símbolo en el ámbito Global (el primero de la pila)
const SymbolEntry* SymbolTableStack::lookupBase(const std::string &id) {
    if (stack.empty())
        return nullptr;
    return stack.front()->lookup(id);
}

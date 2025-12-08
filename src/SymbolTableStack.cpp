#include "SymbolTableStack.hpp"
#include <stdexcept>

/**
 * Crea un nuevo ámbito y lo agrega a la pila.
 * Se usa cuando el compilador entra a un nuevo bloque o función.
 */
void SymbolTableStack::pushScope() {
    stack.push_back(new SymbolTable());
}

/**
 * Elimina el ámbito superior de la pila.
 * No libera memoria; solo remueve el scope.
 * Lanza excepción si la pila está vacía.
 */
void SymbolTableStack::popScope() {
    if (stack.empty())
        throw std::runtime_error("popScope: pila vacía");
    stack.pop_back();
}

/**
 * Saca el ámbito superior y lo retorna.
 * Permite que el llamador decida cuándo liberar la memoria.
 * Lanza excepción si la pila está vacía.
 */
SymbolTable* SymbolTableStack::popSymbolTable() {
    if (stack.empty())
        throw std::runtime_error("popSymbolTable: pila vacía");

    SymbolTable* top = stack.back();
    stack.pop_back();
    return top;
}

/**
 * Inserta una entrada en el ámbito superior.
 * Retorna false si la pila está vacía.
 */
bool SymbolTableStack::insertTop(const SymbolEntry &entry) {
    if (stack.empty())
        return false;
    return stack.back()->insert(entry);
}

/**
 * Inserta una entrada en el ámbito base (global).
 * Retorna false si la pila está vacía.
 */
bool SymbolTableStack::insertBase(const SymbolEntry &entry) {
    if (stack.empty())
        return false;
    return stack.front()->insert(entry);
}

/**
 * Busca una entrada solo en el ámbito superior.
 * Retorna nullptr si no existe o la pila está vacía.
 */
const SymbolEntry* SymbolTableStack::lookupTop(const std::string &id) {
    if (stack.empty())
        return nullptr;
    return stack.back()->lookup(id);
}

/**
 * Busca una entrada solo en el ámbito base.
 * Retorna nullptr si no existe o la pila está vacía.
 */
const SymbolEntry* SymbolTableStack::lookupBase(const std::string &id) {
    if (stack.empty())
        return nullptr;
    return stack.front()->lookup(id);
}

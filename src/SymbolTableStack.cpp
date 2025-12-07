#include "SymbolTableStack.hpp"
#include <stdexcept>

void SymbolTableStack::pushScope() {
    stack.push_back(new SymbolTable());
}

void SymbolTableStack::popScope() {
    if (stack.empty())
        throw std::runtime_error("popScope: pila vacía");

    // No liberar 
    stack.pop_back();
}

SymbolTable* SymbolTableStack::popSymbolTable() {
    if (stack.empty())
        throw std::runtime_error("popSymbolTable: pila vacía");

    SymbolTable* top = stack.back();
    stack.pop_back();
    return top;  // sin liberar
}

bool SymbolTableStack::insertTop(const SymbolEntry &entry) {
    if (stack.empty())
        return false;
    return stack.back()->insert(entry);
}

bool SymbolTableStack::insertBase(const SymbolEntry &entry) {
    if (stack.empty())
        return false;
    return stack.front()->insert(entry);
}

const SymbolEntry* SymbolTableStack::lookupTop(const std::string &id) {
    if (stack.empty())
        return nullptr;
    return stack.back()->lookup(id);
}

const SymbolEntry* SymbolTableStack::lookupBase(const std::string &id) {
    if (stack.empty())
        return nullptr;
    return stack.front()->lookup(id);
}

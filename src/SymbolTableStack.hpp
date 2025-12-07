#pragma once
#include <vector>
#include <memory>
#include "SymbolTable.hpp"

class SymbolTableStack {
private:
    // La pila almacena punteros a tablas
    std::vector<SymbolTable*> stack;

public:
    // Crear nuevo ámbito (tabla vacía)
    void pushScope();

    // Quitar el ámbito actual (no se libera)
    void popScope();

    // Sale el ámbito y retorna la referencia sin liberarla
    SymbolTable* popSymbolTable();

    // Insertar solo en el tope
    bool insertTop(const SymbolEntry &entry);

    // Insertar solo en la base (ámbito global)
    bool insertBase(const SymbolEntry &entry);

    // Buscar solo en la tabla del tope
    const SymbolEntry* lookupTop(const std::string &id);

    // Buscar solo en la tabla de la base
    const SymbolEntry* lookupBase(const std::string &id);

    // Obtener ámbito actual
    SymbolTable* currentScope() {
        if (stack.empty()) return nullptr;
        return stack.back();
    }

    // Obtener ámbito global
    SymbolTable* globalScope() {
        if (stack.empty()) return nullptr;
        return stack.front();
    }

    size_t levels() const { return stack.size(); }
};

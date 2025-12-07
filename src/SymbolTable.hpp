#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <iostream>

//
// Categorías de símbolos
//
enum class Category {
    VAR,
    CONST,
    STRUCT,
    FUNCTION,
    PARAM,
    STRUCT_FIELD   // necesario para campos de un struct
};

//
// Entrada de un símbolo
//
struct SymbolEntry {
    std::string id;                // nombre del símbolo o campo
    int typeId;                    // id del tipo en TypeTable
    Category category;             // categoría del símbolo
    int address = 0;               // offset (struct) o dirección
    std::vector<int> params;       // parámetros (para funciones)
};

//
// Tabla de símbolos
//
class SymbolTable {
private:
    // Tabla principal (búsqueda por nombre)
    std::unordered_map<std::string, SymbolEntry> table;

    // Claves en ORDEN de declaración → indispensable para structs
    std::vector<std::string> orderedKeys;

public:

    // =============================================================
    // Inserción
    // =============================================================
    bool insert(const SymbolEntry &entry) {
        if (table.count(entry.id))
            return false;  // ya existe

        table[entry.id] = entry;
        orderedKeys.push_back(entry.id);
        return true;
    }

    // =============================================================
    // Consultas simples
    // =============================================================

    int getType(const std::string &id) {
        if (!table.count(id)) return -1;
        return table[id].typeId;
    }

    int getAddress(const std::string &id) {
        if (!table.count(id)) return -1;
        return table[id].address;
    }

    Category getCategory(const std::string &id) {
        if (!table.count(id)) return Category::VAR; // default
        return table[id].category;
    }

    std::vector<int> getParams(const std::string &id) {
        if (!table.count(id)) return {};
        return table[id].params;
    }

    // =============================================================
    // lookup completo (devuelve puntero)
    // =============================================================
    const SymbolEntry* lookup(const std::string &id) const {
        auto it = table.find(id);
        return (it != table.end()) ? &it->second : nullptr;
    }

    // =============================================================
    // NUEVO: obtener entradas en orden de declaración
    // NECESARIO para addStructType() del TypeTable
    // =============================================================
    std::vector<SymbolEntry> getOrderedEntries() const {
        std::vector<SymbolEntry> out;
        out.reserve(orderedKeys.size());

        for (const auto &k : orderedKeys)
            out.push_back(table.at(k));

        return out;
    }

    // =============================================================
    // NUEVO: actualizar offset (address) de un campo
    // NECESARIO para calcular layout de struct
    // =============================================================
    void updateOffset(const std::string &id, int newOffset) {
        if (table.count(id))
            table[id].address = newOffset;
    }

    // =============================================================
    // Depuración
    // =============================================================
    void print() const {
        std::cout << "=== SymbolTable ===\n";
        for (const auto &k : orderedKeys) {
            const auto &s = table.at(k);
            std::cout << s.id 
                      << " | type=" << s.typeId
                      << " | addr=" << s.address
                      << " | cat=" << (int)s.category
                      << "\n";
        }
        std::cout << "====================\n";
    }
};

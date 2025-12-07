#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <iostream>

// Usamos Enum sin "class" para que VarCategory sea visible globalmente y que funcionen los tests
enum Category {
    VAR,
    CONST,
    STRUCT,
    FUNCTION,
    PARAM,
    STRUCT_FIELD,
    
    // Alias para compatibilidad
    VarCategory = VAR,
    FunctionCategory = FUNCTION
};

struct SymbolEntry {
    std::string id;
    int typeId;
    Category category;
    

    // Permite acceder al mismo dato llamándolo 'address' o 'dir' 
    union {
        int address;
        int dir;
    };

    std::vector<int> params;
    
    // Constructor por defecto de la union de address y dir
    SymbolEntry() : id(""), typeId(-1), category(VAR), address(0), params() {}
    
    // Constructor auxiliar para facilitar la inserción
    SymbolEntry(std::string i, int t, Category c, int a, std::vector<int> p) 
        : id(i), typeId(t), category(c), address(a), params(p) {}
};

class SymbolTable {
private:
    std::unordered_map<std::string, SymbolEntry> table;
    std::vector<std::string> orderedKeys;

public:
    // --- MÉTODOS COMPATIBLES ---
    
    // Firma corregida: Paso por valor (sin const&) para evitar problemas de alias
    bool insert(SymbolEntry entry); 

    // Métodos para los TESTS
    void insert(std::string id, int typeId, Category cat, int dir, std::vector<int> params = {});
    std::optional<SymbolEntry> get(const std::string &id);

    // Getters y utilidades
    const SymbolEntry* lookup(const std::string &id) const;
    void updateOffset(const std::string &id, int newOffset);
    std::vector<SymbolEntry> getOrderedEntries() const;

    int getType(const std::string &id);
    int getAddress(const std::string &id);
    Category getCategory(const std::string &id);
    std::vector<int> getParams(const std::string &id);

    void print() const;
};
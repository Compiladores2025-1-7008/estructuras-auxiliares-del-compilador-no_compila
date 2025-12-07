#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <iostream>

// Usamos Enum sin "class" para que VarCategory sea visible globalmente y que funcionen los tests
enum Category {
    VAR,   // Variable simple
    CONST, // Constante
    STRUCT, // Estructura
    FUNCTION, //Funcion 
    PARAM, // Parametro de la funcion
    STRUCT_FIELD, // Campo de estructura
    
    // Alias para compatibilidad
    VarCategory = VAR,
    FunctionCategory = FUNCTION
};

// Entrada de la tabla de símbolos
struct SymbolEntry {
    std::string id; // Identificador 
    int typeId;  // Tipo (ID en TypeTable)
    Category category; // Categoría (variable, función, etc.)
    

    // Permite acceder al mismo dato llamándolo 'address' o 'dir' 
    union {
        int address; // Dirección o desplazamiento
        int dir;   // Alias para compatibilidad
    };

    std::vector<int> params;
    
    // Constructor por defecto de la union de address y dir
    SymbolEntry() : id(""), typeId(-1), category(VAR), address(0), params() {}
    
    // Constructor auxiliar para facilitar la inserción
    SymbolEntry(std::string i, int t, Category c, int a, std::vector<int> p) 
        : id(i), typeId(t), category(c), address(a), params(p) {}
};

// Tabla de símbolos
class SymbolTable {
private:
    // // Tabla Hash para búsquedas rápidas O(1) por nombre.
    std::unordered_map<std::string, SymbolEntry> table;
    // Vector para mantener el orden de inserción
    std::vector<std::string> orderedKeys;

public:
    // --- METODOS COMPATIBLES ---
    
    // Firma corregida: Paso por valor (sin const&) para evitar problemas de alias
    bool insert(SymbolEntry entry); 

    // Métodos para los TESTS
    void insert(std::string id, int typeId, Category cat, int dir, std::vector<int> params = {});
    std::optional<SymbolEntry> get(const std::string &id);

    // Getters y utilidades
    const SymbolEntry* lookup(const std::string &id) const;
    void updateOffset(const std::string &id, int newOffset);
    std::vector<SymbolEntry> getOrderedEntries() const;
    
    // Consultas simples
    int getType(const std::string &id);
    int getAddress(const std::string &id);
    Category getCategory(const std::string &id);
    std::vector<int> getParams(const std::string &id);

    // Imprime el contenido de la tabla en consola
    void print() const;
};
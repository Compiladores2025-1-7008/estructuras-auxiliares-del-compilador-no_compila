#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "SymbolTable.hpp"

enum class TypeKind { BASIC, ARRAY, STRUCT };

// Estructura para representar un tipo
struct TypeEntry {
    int id;
    TypeKind kind;
    std::string name;
    int size;    
    // 'elements' y 'numElements' comparten la misma memoria para que no exista conflicto con los test
    union {
        int elements;
        int numElements;
    };

    // Areglo y Struct
    int baseTypeId = -1;
    SymbolTable *structFields = nullptr;

    // Constructor para inicializar por defecto 
    TypeEntry() 
        : id(0), kind(TypeKind::BASIC), name(""), size(0), 
          elements(1), baseTypeId(-1), structFields(nullptr) {}
};

// Tabla de tipos
class TypeTable {
private:
    std::vector<TypeEntry> types; // Almacena los tipos
    int lastId = 0;

public:
    TypeTable();

    // --- METODOS PARA LOS TESTS ---
    int insertType(const std::string &name, int size);
    int insertArrayType(const std::string &name, int baseTypeId, int elements);
    
    const TypeEntry &getType(int id) const;

    // --- METODOS---
    int addBasicType(const std::string &name, int size);
    int addArrayType(int baseTypeId, int elements);
    int addStructType(const std::string &name, SymbolTable *fields);

    // --- CONSULTAS ---
    const TypeEntry &get(int id) const;
    int getSize(int id) const;
    int getNumElements(int id) const;
    int getBaseType(int id) const;
    SymbolTable *getStructFields(int id) const;

    void print() const;
};
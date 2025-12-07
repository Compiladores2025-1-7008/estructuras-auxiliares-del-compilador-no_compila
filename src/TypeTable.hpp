#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

class SymbolTable; // forward

enum class TypeKind
{
    BASIC,
    ARRAY,
    STRUCT
};

struct TypeEntry
{
    int id;
    TypeKind kind;
    std::string name;
    int size;
    int elements = 1;
    int baseTypeId = -1;
    SymbolTable *structFields = nullptr;
};

class TypeTable
{
public:
    TypeTable();

private:
    std::vector<TypeEntry> types;
    int lastId = 0;

public:
    // --- Creación de tipos ---
    int addBasicType(const std::string &name, int size);
    int addArrayType(int baseTypeId, int elements);
    int addStructType(const std::string &name, SymbolTable *fields);

    // --- Consultas ---
    const TypeEntry &get(int id) const;

    int getSize(int id) const;
    int getNumElements(int id) const;
    int getBaseType(int id) const;
    SymbolTable *getStructFields(int id) const;

    // Depuración
    void print() const;
};

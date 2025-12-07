#include "TypeTable.hpp"
#include <stdexcept>

// Constructor
TypeTable::TypeTable() {
    addBasicType("void", 0);
    addBasicType("bool", 1);
    addBasicType("char", 1);
    addBasicType("int", 4);
    addBasicType("float", 4);
    addBasicType("double", 8);
}

// -------------------------------------------------------
// METODOS PARA TESTS
// -------------------------------------------------------

int TypeTable::insertType(const std::string &name, int size) {
    return addBasicType(name, size);
}

int TypeTable::insertArrayType(const std::string &name, int baseTypeId, int elements) {
    int id = addArrayType(baseTypeId, elements);
    types[id].name = name; 
    return id;
}

// Implementación de getType 
const TypeEntry &TypeTable::getType(int id) const {
    return get(id);
}

// -------------------------------------------------------
// METODOS 
// -------------------------------------------------------

int TypeTable::addBasicType(const std::string &name, int size) {
    TypeEntry t;
    t.id = lastId++;
    t.kind = TypeKind::BASIC;
    t.name = name;
    t.size = size;
    t.elements = 1;
    t.baseTypeId = -1;
    t.structFields = nullptr;
    types.push_back(t);
    return t.id;
}

int TypeTable::addArrayType(int baseTypeId, int elements) {
    if (baseTypeId < 0 || baseTypeId >= (int)types.size())
        throw std::runtime_error("TypeTable: baseTypeId inválido");

    const TypeEntry &base = types[baseTypeId];
    TypeEntry t;
    t.id = lastId++;
    t.kind = TypeKind::ARRAY;
    t.baseTypeId = baseTypeId;
    t.elements = elements;
    t.size = base.size * elements;
    t.name = base.name + "[" + std::to_string(elements) + "]";
    t.structFields = nullptr;
    types.push_back(t);
    return t.id;
}

int TypeTable::addStructType(const std::string &name, SymbolTable *fields) {
    if (!fields) return -1;
    int offset = 0;
    auto entries = fields->getOrderedEntries();
    for (auto &e : entries) {
        fields->updateOffset(e.id, offset);
        offset += 4; 
    }
    TypeEntry t;
    t.id = lastId++;
    t.kind = TypeKind::STRUCT;
    t.name = name;
    t.size = offset;
    t.elements = 1;
    t.structFields = fields;
    types.push_back(t);
    return t.id;
}

// -------------------------------------------------------
// CONSULTAS
// -------------------------------------------------------

const TypeEntry &TypeTable::get(int id) const {
    if (id < 0 || id >= (int)types.size())
         throw std::runtime_error("TypeTable: ID fuera de rango");
    return types[id];
}

int TypeTable::getSize(int id) const {
    if (id < 0 || id >= (int)types.size()) return 0;
    return types[id].size;
}

int TypeTable::getNumElements(int id) const {
    if (id < 0 || id >= (int)types.size()) return 0;
    return types[id].elements;
}

int TypeTable::getBaseType(int id) const {
    if (id < 0 || id >= (int)types.size()) return -1;
    return types[id].baseTypeId;
}

SymbolTable *TypeTable::getStructFields(int id) const {
    if (id < 0 || id >= (int)types.size()) return nullptr;
    return types[id].structFields;
}

void TypeTable::print() const {
    std::cout << "==== Tabla de Tipos ====\n";
    for (const auto &t : types) {
        std::cout << "ID: " << t.id << " | " << t.name << " | Size: " << t.size << "\n";
    }
    std::cout << "========================\n";
}
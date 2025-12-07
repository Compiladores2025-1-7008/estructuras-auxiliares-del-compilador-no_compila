#include "TypeTable.hpp"
#include "SymbolTable.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

// =======================================================
//  Constructor: aquí puedes registran básicos
// =======================================================

TypeTable::TypeTable()
{
    addBasicType("void", 0);
    addBasicType("bool", 1);
    addBasicType("char", 1);
    addBasicType("int", 4);
    addBasicType("float", 4);
    addBasicType("double", 8);
}

// =======================================================
//  addBasicType
// =======================================================

int TypeTable::addBasicType(const std::string &name, int size)
{
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

// =======================================================
//  addArrayType
// =======================================================

int TypeTable::addArrayType(int baseTypeId, int elements)
{
    if (baseTypeId < 0 || baseTypeId >= (int)types.size())
        throw runtime_error("addArrayType: baseTypeId inválido");

    const TypeEntry &base = types[baseTypeId];

    if (elements <= 0)
        throw runtime_error("addArrayType: número de elementos debe ser > 0");

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

// =======================================================
//  addStructType
// =======================================================

int TypeTable::addStructType(const std::string &name, SymbolTable *fields)
{
    if (!fields)
        throw runtime_error("addStructType: campos nulos");

    int offset = 0;

    // Lista ORDENADA de campos
    auto fieldList = fields->getOrderedEntries();

    for (auto &sym : fieldList)
    {
        // asignar offset actual
        sym.address = offset;

        // actualizar en SymbolTable
        fields->updateOffset(sym.id, offset);

        // aumentar offset según tamaño del tipo de ese campo
        offset += getSize(sym.typeId);
    }

    // Crear entrada de tipo struct
    TypeEntry t;
    t.id = lastId++;
    t.kind = TypeKind::STRUCT;
    t.name = name;
    t.size = offset;
    t.elements = 1;
    t.baseTypeId = -1;
    t.structFields = fields;

    types.push_back(t);
    return t.id;
}

// =======================================================
//  get
// =======================================================

const TypeEntry &TypeTable::get(int id) const
{
    if (id < 0 || id >= (int)types.size())
        throw runtime_error("TypeTable::get: id fuera de rango");

    return types[id];
}

// =======================================================
//  Getters
// =======================================================

int TypeTable::getSize(int id) const
{
    return get(id).size;
}

int TypeTable::getNumElements(int id) const
{
    return get(id).elements;
}

int TypeTable::getBaseType(int id) const
{
    return get(id).baseTypeId;
}

SymbolTable *TypeTable::getStructFields(int id) const
{
    return get(id).structFields;
}

// =======================================================
//  print
// =======================================================

void TypeTable::print() const
{
    cout << "==== Tabla de Tipos ====\n";

    for (const auto &t : types)
    {
        cout << "[" << t.id << "] ";

        switch (t.kind)
        {
        case TypeKind::BASIC:
            cout << "BASIC  ";
            break;
        case TypeKind::ARRAY:
            cout << "ARRAY  ";
            break;
        case TypeKind::STRUCT:
            cout << "STRUCT ";
            break;
        }

        cout << t.name << " | size=" << t.size;

        if (t.kind == TypeKind::ARRAY)
        {
            cout << " | elems=" << t.elements
                 << " | baseType=" << t.baseTypeId;
        }

        if (t.kind == TypeKind::STRUCT)
        {
            cout << " | campos:\n";

            auto fields = t.structFields->getOrderedEntries();

            for (auto &f : fields)
            {
                cout << "       - " << f.id
                     << ": typeId=" << f.typeId
                     << " offset=" << f.address
                     << "\n";
            }
        }
        else
        {
            cout << "\n";
        }
    }

    cout << "========================\n";
}

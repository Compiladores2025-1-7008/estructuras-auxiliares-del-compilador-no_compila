#include "SymbolTable.hpp"

//
// Insertar símbolo
//
bool SymbolTable::insert(const SymbolEntry &entry)
{
    if (table.count(entry.id))
        return false;

    table[entry.id] = entry;
    orderedKeys.push_back(entry.id);
    return true;
}

//
// Consultas simples
//
int SymbolTable::getType(const std::string &id)
{
    if (!table.count(id))
        return -1;
    return table[id].typeId;
}

int SymbolTable::getAddress(const std::string &id)
{
    if (!table.count(id))
        return -1;
    return table[id].address;
}

Category SymbolTable::getCategory(const std::string &id)
{
    if (!table.count(id))
        return Category::VAR;
    return table[id].category;
}

std::vector<int> SymbolTable::getParams(const std::string &id)
{
    if (!table.count(id))
        return {};
    return table[id].params;
}

//
// lookup completo
//
const SymbolEntry *SymbolTable::lookup(const std::string &id) const
{
    auto it = table.find(id);
    return (it != table.end()) ? &it->second : nullptr;
}

//
// Lista ordenada de símbolos
//
std::vector<SymbolEntry> SymbolTable::getOrderedEntries() const
{
    std::vector<SymbolEntry> out;
    out.reserve(orderedKeys.size());

    for (const auto &k : orderedKeys)
        out.push_back(table.at(k));

    return out;
}

//
// Actualizar offset (struct)
//
void SymbolTable::updateOffset(const std::string &id, int newOffset)
{
    if (table.count(id))
        table[id].address = newOffset;
}

//
// Debug print
//
void SymbolTable::print() const
{
    std::cout << "=== SymbolTable ===\n";
    for (const auto &k : orderedKeys)
    {
        const auto &s = table.at(k);
        std::cout << s.id
                  << " | type=" << s.typeId
                  << " | addr=" << s.address
                  << " | cat=" << (int)s.category
                  << "\n";
    }
    std::cout << "====================\n";
}

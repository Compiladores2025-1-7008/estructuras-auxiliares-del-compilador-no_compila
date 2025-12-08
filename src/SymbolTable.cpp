#include "SymbolTable.hpp"

// =======================================================
// Insertar (Estilo Compañero)
// =======================================================
bool SymbolTable::insert(SymbolEntry entry)
{
    if (table.count(entry.id))
        return false;

    table[entry.id] = entry;
    orderedKeys.push_back(entry.id);
    return true;
}

// =======================================================
// Insertar (Estilo TESTS)
// =======================================================
void SymbolTable::insert(std::string id, int typeId, Category cat, int dir, std::vector<int> params) {
    // Usamos el constructor del struct o inicialización directa
    SymbolEntry entry(id, typeId, cat, dir, params);
    insert(entry); 
}

// =======================================================
// Get (Estilo TESTS - Retorna Optional)
// =======================================================
std::optional<SymbolEntry> SymbolTable::get(const std::string &id) {
    auto it = table.find(id);
    if (it != table.end()) {
        return it->second;
    }
    return std::nullopt;
}

// =======================================================
// Lookup (Devuelve Puntero)
// =======================================================
const SymbolEntry *SymbolTable::lookup(const std::string &id) const
{
    auto it = table.find(id);
    return (it != table.end()) ? &it->second : nullptr;
}

// =======================================================
// Consultas Simples
// =======================================================
int SymbolTable::getType(const std::string &id)
{
    if (!table.count(id)) return -1;
    return table[id].typeId;
}

int SymbolTable::getAddress(const std::string &id)
{
    if (!table.count(id)) return -1;
    // se uso una union para que .address exista y sea un int
    return table[id].address; 
}

Category SymbolTable::getCategory(const std::string &id)
{
    if (!table.count(id)) return Category::VAR;
    return table[id].category;
}

std::vector<int> SymbolTable::getParams(const std::string &id)
{
    if (!table.count(id)) return {};
    return table[id].params;
}

// =======================================================
// Utilidades
// =======================================================
std::vector<SymbolEntry> SymbolTable::getOrderedEntries() const
{
    std::vector<SymbolEntry> out;
    out.reserve(orderedKeys.size());
    for (const auto &k : orderedKeys)
        out.push_back(table.at(k));
    return out;
}

void SymbolTable::updateOffset(const std::string &id, int newOffset)
{
    if (table.count(id)) {
        table[id].address = newOffset; 
    }
}

void SymbolTable::print() const
{
    std::cout << "=== SymbolTable ===\n";
    for (const auto &k : orderedKeys)
    {
        const auto &s = table.at(k);
        // Aquí s.address funciona correctamente como int para el operador <<
        std::cout << s.id
                  << " | type=" << s.typeId
                  << " | addr=" << s.address 
                  << " | cat=" << (int)s.category
                  << "\n";
    }
    std::cout << "====================\n";
}
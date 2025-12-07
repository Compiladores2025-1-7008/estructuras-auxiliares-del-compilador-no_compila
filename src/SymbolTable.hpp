#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <iostream>

enum class Category {
    VAR,
    CONST,
    STRUCT,
    FUNCTION,
    PARAM,
    STRUCT_FIELD
};

struct SymbolEntry {
    std::string id;
    int typeId;
    Category category;
    int address = 0;
    std::vector<int> params;
};

class SymbolTable {
private:
    std::unordered_map<std::string, SymbolEntry> table;
    std::vector<std::string> orderedKeys;

public:
    bool insert(const SymbolEntry &entry);

    int getType(const std::string &id);
    int getAddress(const std::string &id);
    Category getCategory(const std::string &id);
    std::vector<int> getParams(const std::string &id);

    const SymbolEntry* lookup(const std::string &id) const;

    std::vector<SymbolEntry> getOrderedEntries() const;
    void updateOffset(const std::string &id, int newOffset);

    void print() const;
};

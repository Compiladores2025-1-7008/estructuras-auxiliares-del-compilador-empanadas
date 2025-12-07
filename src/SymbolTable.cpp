#include "SymbolTable.hpp"
#include <iostream>

bool SymbolTable::insert(const std::string &id, int typeId, Category category, 
                         int dir, const std::vector<int> &params) {
    SymbolEntry entry{id, typeId, category, dir, params};
    return insert(entry);
}

bool SymbolTable::insert(const SymbolEntry &entry) {
    // Solo inserta si no existe
    if (table.find(entry.id) != table.end()) {
        return false;
    }
    table[entry.id] = entry;
    return true;
}

std::optional<SymbolEntry> SymbolTable::get(const std::string &id) const {
    auto it = table.find(id);
    if (it != table.end()) {
        return it->second;
    }
    return std::nullopt;
}

int SymbolTable::getType(const std::string &id) {
    auto it = table.find(id);
    if (it != table.end()) {
        return it->second.typeId;
    }
    return -1;
}

int SymbolTable::getAddress(const std::string &id) {
    auto it = table.find(id);
    if (it != table.end()) {
        return it->second.dir;
    }
    return -1;
}

Category SymbolTable::getCategory(const std::string &id) {
    auto it = table.find(id);
    if (it != table.end()) {
        return it->second.category;
    }
    return VarCategory; // valor por defecto
}

std::vector<int> SymbolTable::getParams(const std::string &id) {
    auto it = table.find(id);
    if (it != table.end()) {
        return it->second.params;
    }
    return {};
}

void SymbolTable::print() const {
    std::cout << "=== Symbol Table ===" << std::endl;
    for (const auto &[key, entry] : table) {
        std::cout << "ID: " << entry.id 
                  << ", Type: " << entry.typeId
                  << ", Dir: " << entry.dir
                  << ", Category: " << static_cast<int>(entry.category);
        if (!entry.params.empty()) {
            std::cout << ", Params: [";
            for (size_t i = 0; i < entry.params.size(); ++i) {
                std::cout << entry.params[i];
                if (i < entry.params.size() - 1) std::cout << ", ";
            }
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}


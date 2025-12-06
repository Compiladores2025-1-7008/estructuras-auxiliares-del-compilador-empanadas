#include "TypeTable.hpp"
#include <iostream>
#include <stdexcept>

// Para compatibilidad con tests
int TypeTable::insertType(const std::string& name, int size) {
    return addBasicType(name, size);
}

int TypeTable::insertArrayType(const std::string& name, int baseTypeId, int numElements) {
    TypeEntry entry;
    entry.id = lastId++;
    entry.kind = TypeKind::ARRAY;
    entry.name = name;
    entry.baseTypeId = baseTypeId;
    entry.numElements = numElements;
    entry.size = get(baseTypeId).size * numElements;
    entry.structFields = nullptr;
    
    types.push_back(entry);
    return entry.id;
}

// Implementación API original
int TypeTable::addBasicType(const std::string& name, int size) {
    TypeEntry entry;
    entry.id = lastId++;
    entry.kind = TypeKind::BASIC;
    entry.name = name;
    entry.size = size;
    entry.numElements = 1;
    entry.baseTypeId = -1;
    entry.structFields = nullptr;
    
    types.push_back(entry);
    return entry.id;
}

int TypeTable::addArrayType(int baseTypeId, int elements) {
    TypeEntry entry;
    entry.id = lastId++;
    entry.kind = TypeKind::ARRAY;
    entry.name = get(baseTypeId).name + "[]";
    entry.baseTypeId = baseTypeId;
    entry.numElements = elements;
    entry.size = get(baseTypeId).size * elements;
    entry.structFields = nullptr;
    
    types.push_back(entry);
    return entry.id;
}

int TypeTable::addStructType(const std::string &name, SymbolTable* fields) {
    TypeEntry entry;
    entry.id = lastId++;
    entry.kind = TypeKind::STRUCT;
    entry.name = name;
    entry.size = 0; // Calcular según campos
    entry.numElements = 1;
    entry.baseTypeId = -1;
    entry.structFields = fields;
    
    types.push_back(entry);
    return entry.id;
}

// Para tests (devuelve copia)
TypeEntry TypeTable::getType(int id) const {
    if (id < 0 || id >= static_cast<int>(types.size())) {
        throw std::out_of_range("Type ID out of range");
    }
    return types[id];
}

// API original (devuelve referencia)
const TypeEntry& TypeTable::get(int id) const {
    if (id < 0 || id >= static_cast<int>(types.size())) {
        throw std::out_of_range("Type ID out of range");
    }
    return types[id];
}

int TypeTable::getSize(int id) const {
    return get(id).size;
}

int TypeTable::getNumElements(int id) const {
    return get(id).numElements;
}

int TypeTable::getBaseType(int id) const {
    return get(id).baseTypeId;
}

SymbolTable* TypeTable::getStructFields(int id) const {
    return get(id).structFields;
}

void TypeTable::print() const {
    std::cout << "=== Type Table ===" << std::endl;
    for (const auto &type : types) {
        std::cout << "ID: " << type.id 
                  << ", Name: " << type.name
                  << ", Size: " << type.size
                  << ", Elements: " << type.numElements;
        if (type.baseTypeId != -1) {
            std::cout << ", BaseType: " << type.baseTypeId;
        }
        std::cout << std::endl;
    }
}

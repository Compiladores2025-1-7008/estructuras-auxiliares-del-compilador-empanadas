#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

// Declaración adelantada para evitar dependencia circular
class SymbolTable;

// Enumeración que define las categorías de tipos soportados
enum class TypeKind {
    BASIC,   // Tipos primitivos: int, float, char, etc.
    ARRAY,   // Arreglos de tipos base
    STRUCT   // Estructuras con campos
};

struct TypeEntry {
    int id;
    TypeKind kind;
    std::string name;
    int size;
    int numElements = 1;  // Los tests usan "numElements"
    int baseTypeId = -1;
    SymbolTable* structFields = nullptr;
};

class TypeTable {
private:
    std::vector<TypeEntry> types;
    int lastId = 0;

public:
    // --- Creación de tipos (para compatibilidad con tests) ---
    int insertType(const std::string& name, int size);  // tipo básico
    int insertArrayType(const std::string& name, int baseTypeId, int numElements);
    
    // --- Creación de tipos (API original) ---
    int addBasicType(const std::string& name, int size);
    int addArrayType(int baseTypeId, int elements);
    int addStructType(const std::string &name, SymbolTable* fields);

    // --- Consultas ---
    TypeEntry getType(int id) const;  // Para tests (devuelve copia)
    const TypeEntry& get(int id) const;  // API original (devuelve referencia)

    int getSize(int id) const;
    int getNumElements(int id) const;
    int getBaseType(int id) const;
    SymbolTable* getStructFields(int id) const;

    // Depuración
    void print() const;
};

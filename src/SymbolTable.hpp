#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>

// Enumeración que define las categorías de símbolos en el programa
// Permite clasificar cada identificador según su naturaleza
enum Category {
    VarCategory,        // Variable común
    ConstCategory,      // Constante
    StructCategory,     // Estructura o tipo compuesto
    FunctionCategory,   // Función o procedimiento
    ParamCategory       // Parámetro formal de función
};

struct SymbolEntry {
    std::string id;
    int typeId;
    Category category;
    int dir;  // address (los tests usan "dir")
    std::vector<int> params;
};

class SymbolTable {
private:
    std::unordered_map<std::string, SymbolEntry> table;

public:
    // Insertar con parámetros individuales (para tests)
    bool insert(const std::string &id, int typeId, Category category, int dir, 
                const std::vector<int> &params = {});
    
    // Insertar con SymbolEntry completo
    bool insert(const SymbolEntry &entry);
    
    // Obtener símbolo completo (para tests)
    std::optional<SymbolEntry> get(const std::string &id) const;
    
    // -----------------------------------------
    // Consultas individuales simples
    // -----------------------------------------
    int getType(const std::string &id);

    int getAddress(const std::string &id);

    Category getCategory(const std::string &id);

    std::vector<int> getParams(const std::string &id);

    // -----------------------------------------
    // Consulta completa (si necesitas todos los datos)
    // -----------------------------------------
    const SymbolEntry* lookup(const std::string &id) const {
        auto it = table.find(id);
        return (it != table.end()) ? &it->second : nullptr;
    }

    // Para imprimir/depurar
    void print() const;
};


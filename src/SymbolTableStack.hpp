#pragma once
#include <vector>
#include <memory>
#include "SymbolTable.hpp"

// Clase que implementa una pila de tablas de símbolos
// Permite gestionar ámbitos anidados (scopes) en el programa
// La base de la pila representa el ámbito global
// El tope representa el ámbito local actual
class SymbolTableStack {
private:
    std::vector<std::unique_ptr<SymbolTable>> stack;  // Pila de tablas

public:
    // Crea un nuevo ámbito y lo coloca en el tope de la pila
    void pushScope();

    // Sale de un ámbito
    void popScope();

    // Sale el ámbito y retorna la referencia a la tabla de símbolos en la cima
    SymbolTable* popSymbolTable();

    // Insertar solo en tope
    bool insertTop(const SymbolEntry &entry);

    // Insertar solo en la base (ámbito global)
    bool insertBase(const SymbolEntry &entry);

    // Buscar solo en tope
    SymbolEntry* lookupTop(const std::string &id);

    // Buscar solo en la base
    SymbolEntry* lookupBase(const std::string &id);

    // Depuración
    SymbolTable* currentScope() {
        if (stack.empty()) return nullptr;
        return stack.back().get();
    }

    SymbolTable* globalScope() {
        if (stack.empty()) return nullptr;
        return stack.front().get();
    }

    size_t levels() const { return stack.size(); }
};

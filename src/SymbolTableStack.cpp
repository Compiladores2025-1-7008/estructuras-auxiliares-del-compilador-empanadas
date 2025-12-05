#include "SymbolTableStack.hpp"

void SymbolTableStack::pushScope() {
    stack.push_back(std::make_unique<SymbolTable>());
}

void SymbolTableStack::popScope() {
    if (!stack.empty()) {
        stack.pop_back();
    }
}

SymbolTable* SymbolTableStack::popSymbolTable() {
    if (stack.empty()) {
        return nullptr;
    }
    SymbolTable* table = stack.back().release();
    stack.pop_back();
    return table;
}

bool SymbolTableStack::insertTop(const SymbolEntry &entry) {
    if (stack.empty()) {
        return false;
    }
    return stack.back()->insert(entry);
}

bool SymbolTableStack::insertBase(const SymbolEntry &entry) {
    if (stack.empty()) {
        return false;
    }
    return stack.front()->insert(entry);
}

SymbolEntry* SymbolTableStack::lookupTop(const std::string &id) {
    if (stack.empty()) {
        return nullptr;
    }
    return const_cast<SymbolEntry*>(stack.back()->lookup(id));
}

SymbolEntry* SymbolTableStack::lookupBase(const std::string &id) {
    if (stack.empty()) {
        return nullptr;
    }
    return const_cast<SymbolEntry*>(stack.front()->lookup(id));
}

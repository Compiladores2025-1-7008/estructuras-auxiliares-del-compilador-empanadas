#pragma once
#include "TypeTable.hpp"
#include <algorithm>

// Clase que implementa el manejador de tipos del compilador
// Gestiona la jerarquía de tipos y las conversiones entre ellos
// Basado en el Capítulo 6 de Aho, Sethi, Ullman
class TypeManager {
public:
    // Determina la prioridad de un tipo en la jerarquía
    // Jerarquía: void(0) < bool(0) < char(1) < int(2) < float(3) < double(3)
    static int priority(const TypeTable &TT, int typeId) {
        const auto &t = TT.get(typeId);
        if (t.name == "char") return 1;
        if (t.name == "int")  return 2;
        if (t.name == "float")return 3;
        return 0;
    }

    // Retorna el tipo de mayor jerarquía entre dos tipos
    // Utilizado para determinar el tipo resultado de operaciones
    static int maxType(const TypeTable &TT, int t1, int t2) {
        return (priority(TT, t1) > priority(TT, t2)) ? t1 : t2;
    }

    // Retorna el tipo de menor jerarquía entre dos tipos
    static int minType(const TypeTable &TT, int t1, int t2) {
        return (priority(TT, t1) < priority(TT, t2)) ? t1 : t2;
    }

    // Versiones simplificadas para pruebas (asumen IDs como prioridades)
    static int maxType(int t1, int t2) {
        return std::max(t1, t2);
    }

    static int minType(int t1, int t2) {
        return std::min(t1, t2);
    }

    // Conversión implícita (widening): convierte un tipo de menor jerarquía a mayor
    // Utilizado en asignaciones y expresiones aritméticas
    // Retorna el tipo de mayor jerarquía
    static int ampliar(int dir, int tipo1, int tipo2) {
        return std::max(tipo1, tipo2);
    }

    // Ampliar con TypeTable
    static int ampliar(const TypeTable &TT, int dir, int tipo1, int tipo2) {
        return maxType(TT, tipo1, tipo2);
    }

    // Reducir: convertir tipo grande → menor (requiere cuidado)
    static int reducir(int dir, int tipo1, int tipo2) {
        // Retorna el tipo menor
        return std::min(tipo1, tipo2);
    }

    // Reducir con TypeTable
    static int reducir(const TypeTable &TT, int dir, int tipo1, int tipo2) {
        return minType(TT, tipo1, tipo2);
    }
    
    // Alias en inglés para compatibilidad con tests
    static int amplify(int dir, int tipo1, int tipo2) {
        return ampliar(dir, tipo1, tipo2);
    }
    
    static int reduce(int dir, int tipo1, int tipo2) {
        return reducir(dir, tipo1, tipo2);
    }
};

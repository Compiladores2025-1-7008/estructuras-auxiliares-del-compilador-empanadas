#pragma once
#include <string>

// Clase generadora de código intermedio de tres direcciones
// Produce variables temporales y etiquetas para código intermedio
// Basado en el Capítulo 8 de Aho, Sethi, Ullman
class CodeGenerator {
private:
    int nextTemp = 0;   // Contador de variables temporales
    int nextLabel = 0;  // Contador de etiquetas

public:
    // Genera una nueva variable temporal: t0, t1, t2, ...
    // Utilizada para almacenar resultados intermedios de expresiones
    std::string newTemp();

    // Genera una nueva etiqueta: L0, L1, L2, ...
    // Utilizada para marcar destinos de saltos en el código intermedio
    std::string newLabel();

    // Reinicia los contadores a cero
    // Útil para comenzar la generación de una nueva función
    void reset();
};

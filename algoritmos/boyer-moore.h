#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include "PatternSearchAlgorithm.h"
#include <algorithm>

// Implementación del algoritmo Boyer-Moore
// Basado en el código de GeeksforGeeks y adaptado al proyecto
class BoyerMoore : public PatternSearchAlgorithm {
private:
    static const int NO_OF_CHARS = 256;
    
    // Función de preprocesamiento para la heurística de mal carácter de Boyer Moore
    void badCharHeuristic(const string& str, int size, int badchar[NO_OF_CHARS]) {
        // Inicializar todas las ocurrencias como -1
        for (int i = 0; i < NO_OF_CHARS; i++)
            badchar[i] = -1;
        
        // Llenar el valor real de la última ocurrencia de un carácter
        for (int i = 0; i < size; i++)
            badchar[(int)str[i]] = i;
    }
    
public:
    vector<int> search(const string& text, const string& pattern) override {
        vector<int> positions;
        int m = pattern.size();
        int n = text.size();
        
        if (m == 0 || n == 0) return positions;
        
        int badchar[NO_OF_CHARS];
        
        // Llenar el arreglo de mal carácter llamando la función de preprocesamiento
        badCharHeuristic(pattern, m, badchar);
        
        int s = 0; // s es el desplazamiento del patrón con respecto al texto
        
        while (s <= (n - m)) {
            int j = m - 1;
            
            // Seguir reduciendo el índice j del patrón mientras
            // los caracteres del patrón y texto coincidan en este desplazamiento s
            while (j >= 0 && pattern[j] == text[s + j])
                j--;
            
            // Si el patrón está presente en el desplazamiento actual,
            // entonces el índice j se convertirá en -1 después del bucle anterior
            if (j < 0) {
                positions.push_back(s);
                
                // Desplazar el patrón para que el siguiente carácter en el texto
                // se alinee con la última ocurrencia de él en el patrón
                s += (s + m < n) ? m - badchar[text[s + m]] : 1;
            } else {
                // Desplazar el patrón para que el mal carácter en el texto
                // se alinee con la última ocurrencia de él en el patrón
                s += max(1, j - badchar[text[s + j]]);
            }
        }
        
        return positions;
    }
    
    string getName() const override {
        return "Boyer-Moore";
    }
};

#endif // BOYER_MOORE_H
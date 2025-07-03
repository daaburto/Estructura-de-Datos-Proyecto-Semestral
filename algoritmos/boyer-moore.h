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

    // Preprocesamiento para la heurística de buen sufijo 
    void StrongGoodSuffix(vector<int>& shift, vector<int>& bpos, const string& pat, int m) {
        int i = m, j = m + 1;
        bpos[i] = j;

        while (i > 0) {
            // Si el carácter en la posición i-1 no es equivalente al
            // carácter en j-1, entonces continuar buscando hacia la derecha
            // del patrón para encontrar el borde
            while (j <= m && pat[i-1] != pat[j-1]) {
                // El carácter que precede a la ocurrencia de t en el
                // patrón P es diferente del carácter que no coincide en P,
                // se deja de saltar las ocurrencias y desplazamos el patrón
                // de i a j
                if (shift[j] == 0)
                    shift[j] = j - i;
                // Actualizar la posición del siguiente borde
                j = bpos[j];
            }
            // p[i-1] coincidió con p[j-1], se encontró el borde.
            // almacenar la posición inicial del borde
            i--; j--;
            bpos[i] = j;
        }
    }

    // Caso 2 de la heurística de buen sufijo (Widest Border of the Pattern)
    void StrongGoodSuffix_Case2(vector<int>& shift, vector<int>& bpos, const string& pat, int m) {
        int i, j;
        j = bpos[0];

        for (i = 0; i <= m; i++) {
            // Establecer la posición del borde del primer carácter del patrón
            // a todos los índices en el arreglo que sean shift[i] = 0
            if (shift[i] == 0)
                shift[i] = j;
            // El sufijo se vuelve más corto que bpos[0], usar la posición del
            // siguiente borde más amplio como valor de j
            if (i == j)
                j = bpos[j];
        }
    }

public:
    vector<int> search(const string& text, const string& pattern) override {
        vector<int> positions;
        int m = pattern.size();
        int n = text.size();
        
        if (m == 0 || n == 0) return positions;
        
        int badchar[NO_OF_CHARS];
        vector<int> bpos(m + 1);
        vector<int> shift(m + 1, 0);

        // Preprocesamiento para heurística de mal carácter
        badCharHeuristic(pattern, m, badchar);

        // Preprocesamiento para heurística de buen sufijo
        StrongGoodSuffix(shift, bpos, pattern, m);
        StrongGoodSuffix_Case2(shift, bpos, pattern, m);

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
                // Usar la heurística de buen sufijo para el desplazamiento
                s += shift[0];
            } else {
                // Combinar ambas heurísticas y tomar el máximo desplazamiento
                int badCharShift = max(1, j - badchar[text[s + j]]);
                int goodSuffixShift = shift[j + 1];
                s += max(badCharShift, goodSuffixShift);
            }
        }

        return positions;
    }

    string getName() const override {
        return "Boyer-Moore";
    }
};

#endif // BOYER_MOORE_H
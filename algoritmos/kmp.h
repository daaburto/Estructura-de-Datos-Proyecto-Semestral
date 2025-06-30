#ifndef KNUTH_MORRIS_PRATT_H
#define KNUTH_MORRIS_PRATT_H

#include "PatternSearchAlgorithm.h"

// Implementación del algoritmo Knuth-Morris-Pratt
// Basado en el código de GeeksforGeeks y adaptado al proyecto
class KnuthMorrisPratt : public PatternSearchAlgorithm {
private:
    // Construir el arreglo LPS (Longest Proper Prefix which is also Suffix)
    void constructLps(const string& pat, vector<int>& lps) {
        // len almacena la longitud del prefijo más largo que también es sufijo
        // para el índice anterior
        int len = 0;
        
        // lps[0] siempre es 0
        lps[0] = 0;
        
        int i = 1;
        while (i < pat.length()) {
            // Si los caracteres coinciden, incrementar el tamaño de lps
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                // Si hay una discrepancia
                if (len != 0) {
                    // Actualizar len al valor lps anterior
                    // para evitar comparaciones redundantes
                    len = lps[len - 1];
                } else {
                    // Si no se encuentra prefijo coincidente, establecer lps[i] a 0
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
    
public:
    vector<int> search(const string& text, const string& pattern) override {
        int n = text.length();
        int m = pattern.length();
        
        vector<int> lps(m);
        vector<int> positions;
        
        if (m == 0 || n == 0) return positions;
        
        constructLps(pattern, lps);
        
        // Punteros i y j, para recorrer el texto y el patrón
        int i = 0;
        int j = 0;
        
        while (i < n) {
            // Si los caracteres coinciden, mover ambos punteros hacia adelante
            if (text[i] == pattern[j]) {
                i++;
                j++;
                
                // Si todo el patrón coincide, almacenar el índice de inicio en el resultado
                if (j == m) {
                    positions.push_back(i - j);
                    
                    // Usar LPS del índice anterior para evitar comparaciones innecesarias
                    j = lps[j - 1];
                }
            } else {
                // Si hay una discrepancia
                // Usar valor lps del índice anterior para evitar comparaciones redundantes
                if (j != 0)
                    j = lps[j - 1];
                else
                    i++;
            }
        }
        
        return positions;
    }
    
    string getName() const override {
        return "Knuth-Morris-Pratt";
    }
};

#endif // KNUTH_MORRIS_PRATT_H
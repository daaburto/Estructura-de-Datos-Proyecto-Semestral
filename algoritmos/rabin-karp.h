#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include "PatternSearchAlgorithm.h"

// Implementación del algoritmo Rabin-Karp
// Basado en el código de GeeksforGeeks y adaptado al proyecto
class RabinKarp : public PatternSearchAlgorithm {
private:
    // Número de caracteres en el alfabeto de entrada (ASCII)
    static const int d = 256;
    // Un número primo para operaciones de módulo para reducir colisiones
    static const int q = 101;
    
public:
    vector<int> search(const string& text, const string& pattern) override {
        int M = pattern.length();
        int N = text.length();
        
        vector<int> positions;
        
        if (M == 0 || N == 0) return positions;
        
        // Valor hash para el patrón
        int p = 0;
        // Valor hash para la ventana actual del texto
        int t = 0;
        // Multiplicador de dígito de orden alto
        int h = 1;
        
        // Precalcular h = pow(d, M-1) % q
        for (int i = 0; i < M - 1; i++)
            h = (h * d) % q;
        
        // Calcular valores hash iniciales para el patrón y la primera ventana del texto
        for (int i = 0; i < M; i++) {
            p = (d * p + pattern[i]) % q;
            t = (d * t + text[i]) % q;
        }
        
        // Deslizar el patrón sobre el texto uno por uno
        for (int i = 0; i <= N - M; i++) {
            // Si los valores hash coinciden, verificar caracteres uno por uno
            if (p == t) {
                bool match = true;
                for (int j = 0; j < M; j++) {
                    if (text[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if (match)
                    positions.push_back(i);
            }
            
            // Calcular valor hash para la siguiente ventana
            if (i < N - M) {
                t = (d * (t - text[i] * h) + text[i + M]) % q;
                
                // Asegurar que el valor hash sea no negativo
                if (t < 0)
                    t += q;
            }
        }
        
        return positions;
    }
    
    string getName() const override {
        return "Rabin-Karp";
    }
};

#endif // RABIN_KARP_H
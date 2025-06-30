#ifndef PATTERN_SEARCH_ALGORITHM_H
#define PATTERN_SEARCH_ALGORITHM_H

#include <vector>
#include <string>
#include <set>

using namespace std;

// Clase base para todas las soluciones algorítmicas
class PatternSearchAlgorithm {
public:
    virtual ~PatternSearchAlgorithm() = default;
    virtual vector<int> search(const string& text, const string& pattern) = 0;
    virtual string getName() const = 0;
    
    // Método para buscar en múltiples documentos
    set<int> searchInDocuments(const vector<string>& documents, const string& pattern) {
        set<int> result_docs;
        
        // Crear texto concatenado con separadores
        string concatenated_text = "";
        vector<int> doc_start_positions;
        
        for (int i = 0; i < documents.size(); i++) {
            doc_start_positions.push_back(concatenated_text.length());
            concatenated_text += documents[i];
            if (i < documents.size() - 1) {
                concatenated_text += "$";
            }
        }
        
        // Buscar patrón en texto concatenado
        vector<int> positions = search(concatenated_text, pattern);
        
        // Determinar qué documentos contienen el patrón
        for (int pos : positions) {
            for (int i = 0; i < doc_start_positions.size(); i++) {
                int start = doc_start_positions[i];
                int end = (i + 1 < doc_start_positions.size()) ? 
                         doc_start_positions[i + 1] - 1 : concatenated_text.length();
                
                if (pos >= start && pos < end) {
                    result_docs.insert(i);
                    break;
                }
            }
        }
        
        return result_docs;
    }
};

#endif // PATTERN_SEARCH_ALGORITHM_H
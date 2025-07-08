#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <vector> // Necesario para std::vector
#include "../algoritmos/suffix-tree.h"

using namespace std;

int main(int argc, char **argv){
    // Si no hay suficientes argumentos, detenemos la ejecución
    if (argc < 2){
        cerr << "Usage: " << argv[0] << " <Nombre del archivo de texto>" << endl;
        exit(1);
    }
    SuffixTree st;
    std::list<string> patrones = {"TATA", "AAAGATGAGGTAACTGGGGCACAAA", "ACGTE", "AAAGATGAGGTAACTGGGGCACAAAEASD", "ATTATGT", "GTGATGTGATCTCTGCTCACTGCAAGCTCCGCCCCTCGGGTTCATGCCATTCTCCTTCCTCAGCCTCCCGAGTACCTGGGACTACGGGCGCCCACCACCACACCTGGCTAATTTTTTTGTA", "TTTGGGAAA", "GTGATGTGATCTCTGCTCACTGCAAGCTCCGCCCCTCGGGTTCATGCCATTCTCCTTCCTCAGCCTCCCGAGTACCTGGGACTACGGGCGCCCACCACECACACCTGGCTAATTTTTTTGTA"};

    // Obtener el nombre del archivo desde los argumentos
    string nombreArchivo = argv[1];
    string textoCompleto; // Para almacenar todo el contenido del archivo

    // Leer todo el contenido del archivo una vez
    ifstream archivo_lectura(nombreArchivo);
    if (!archivo_lectura.is_open()){
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1;
    }
    string linea_lectura;
    while (getline(archivo_lectura, linea_lectura)) {
        textoCompleto += linea_lectura;
    }
    archivo_lectura.close();

    // --- Medir tiempo de CONSTRUCCIÓN del Suffix Tree ---
    auto start_build = chrono::high_resolution_clock::now();
    st.build_tree(textoCompleto); // Pasar el texto completo para construir el árbol
    auto end_build = chrono::high_resolution_clock::now();
    double build_time = chrono::duration_cast<chrono::nanoseconds>(end_build - start_build).count() * 1e-9;

    // --- Medir tiempo de BÚSQUEDA de los patrones ---
    double running_time = 0.0;
    // Medimos el tiempo por primera vez
    auto start = chrono::high_resolution_clock::now();
    for (const string& patron : patrones){ // Usar const reference para evitar copias innecesarias
        // Llama a st_search que ya espera que el árbol esté construido
        vector<int> posiciones = st.st_search(patron); 
        
    }
    // Medimos el tiempo por segunda vez
        auto end = chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido
    running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    running_time *= 1e-9;
    
    cout << argv[0] << "," << build_time << "," << running_time << endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include "../algoritmos/suffix-tree.h"

using namespace std;

int main(int argc, char **argv){
    // Si no hay suficientes argumentos, detenemos la ejecución
    if (argc < 2){
        cerr << "Usage: " << argv[0] << " <Cantidad de elementos>" << endl;
        exit(1);
    }
    
    SuffixTree st;
    std::list<string> palabras = {"TATA", "AAAGATGAGGTAACTGGGGCACAAA", "ACGTE", "AAAGATGAGGTAACTGGGGCACAAAEASD", "ATTATGT", "GTGATGTGATCTCTGCTCACTGCAAGCTCCGCCCCTCGGGTTCATGCCATTCTCCTTCCTCAGCCTCCCGAGTACCTGGGACTACGGGCGCCCACCACCACACCTGGCTAATTTTTTTGTA", "TTTGGGAAA", "GTGATGTGATCTCTGCTCACTGCAAGCTCCGCCCCTCGGGTTCATGCCATTCTCCTTCCTCAGCCTCCCGAGTACCTGGGACTACGGGCGCCCACCACECACACCTGGCTAATTTTTTTGTA"};

    // Obtener el nombre del archivo desde los argumentos
    string nombreArchivo = argv[1];
    double running_time=0;
    double building_time=0;

    for (string palabra : palabras){
        // Abrir el archivo en modo lectura
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()){
            cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
            return 1;
        }        // Ejecutar el algoritmo
        string linea;
        while (getline(archivo, linea)) {

            // Medimos el tiempo por primera vez
            auto start = chrono::high_resolution_clock::now();
            st.build_tree(palabra);
            // Medimos el tiempo por segunda vez    
            auto end = chrono::high_resolution_clock::now();

            building_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            // Medimos el tiempo por primera vez
            auto start = chrono::high_resolution_clock::now();
            st.st_find(palabra);
            // Medimos el tiempo por segunda vez    
            auto end = chrono::high_resolution_clock::now();

            // Calculamos el tiempo transcurrido
            building_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        }
            

        archivo.close();
        
    }
    running_time *= 1e-9;


    //Imprimimos el resultado
    cout << argv[0] << "," << running_time << running_ endl;

    return 0;
}
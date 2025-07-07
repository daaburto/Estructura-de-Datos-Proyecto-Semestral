#include <iostream>
#include <fstream>
#include <chrono>
#include "../algoritmos/rabin-karp.h"

using namespace std;

int main(int argc, char **argv){
    // Si no hay suficientes argumentos, detenemos la ejecución
    if (argc < 2){
        cerr << "Usage: " << argv[0] << " <Cantidad de elementos>" << endl;
        exit(1);
    }
    
    RabinKarp rk;
    string palabra = "AGA";

    // Obtener el nombre del archivo desde los argumentos
    string nombreArchivo = argv[1];

    // Abrir el archivo en modo lectura
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()){
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1;
    }

    // Obtener tamaño del archivo
    ifstream archivoParaTamano(nombreArchivo, ios::binary | ios::ate);
    if (!archivoParaTamano.is_open()) {
        cerr << "No se pudo abrir el archivo para medir tamaño: " << nombreArchivo << endl;
        return 1;
    }
    streamsize tamanoArchivo = archivoParaTamano.tellg();
    archivoParaTamano.close();
    
    // Medimos el tiempo por primera vez
    auto start = chrono::high_resolution_clock::now();

    // Ejecutar el algoritmo
    string linea;
    while (getline(archivo, linea)) {
        vector<int> posiciones = rk.search(linea, palabra);
    }

    archivo.close();

    // Medimos el tiempo por segunda vez
    auto end = chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido
    double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    running_time *= 1e-9;

    //Imprimimos el resultado
    cout << argv[0] << ";" << tamanoArchivo << ";" << running_time << endl;

    return 0;
}

// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <limits>
#include <algorithm>

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
const int INF = 10000000;

std::vector<int> resolver(const std::vector<std::vector<int>>& pueblos, int n) {
    
    Matriz<int> matriz(n, n+1, INF);
    std::vector<int> sol;

    for (int i = 1; i < matriz.numfils(); i++) {
        
        for (int j = i + 1; j < matriz.numcols(); j++) {

            if (i == 1) {
                matriz[i][j] = pueblos[i - 1][j - 2];
            }
            else {

                int min = INF;

                //calcular el minimo de la columna
                for (int k = 1; k < i; k++) {
                    if (matriz[k][j] < min) {
                        min = matriz[k][j];
                    }
                }


                if (pueblos[i - 1][j - i - 1] + matriz[i - 1][i] < min) {
                    matriz[i][j] = pueblos[i - 1][j - i - 1] + matriz[i - 1][i];
                }
                else {
                    matriz[i][j] = min;
                }

            }

        }
    }

    for (int i = 1; i < matriz.numfils(); i++) {
        sol.push_back(matriz[i][i + 1]);
    }

    return sol;

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    std::cin >> n;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<std::vector<int>> pueblos;
    int aux;

    for (int i = 0; i < n - 1; i++) {
        std::vector<int> a;
        for (int j = i; j < n - 1; j++) {
            std::cin >> aux;
            a.push_back(aux);
        }
        pueblos.push_back(a);
    }

    for (int i = n; i > 1; i--) {
        std::vector<int> sol = resolver(pueblos, i);
        for (int a : sol) {
            std::cout << a << " ";
        }
        pueblos.erase(pueblos.begin());
        std::cout << std::endl;
    }

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
/*#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif*/

    while (resuelveCaso());

    // para dejar todo como estaba al principio
/*#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif*/
    return 0;
}

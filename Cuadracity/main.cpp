
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

class OrdenTopologico {
    public:
        // g es DAG
        OrdenTopologico(Digrafo const& g) : visit(g.V(), false), cont(0) {
            dfs(g, 1); //desde el vertice 1 cuantos caminos hay hasta el final
        }
        // devuelve la ordenación topológica
        int const& orden() const {
            return cont;
        }
    private:
        std::vector<bool> visit;
        int cont;
        void dfs(Digrafo const& g, int v) {
            visit[v] = true;
            if(v == g.V()-1)
                cont++;
            for (int w : g.ady(v)){
                if (!visit[w])
                    dfs(g, w);                
            }

            visit[v] = false;

        }
};



// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(const Digrafo& g) {

    OrdenTopologico k(g);

    return k.orden();

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int rows, cols;

    std::cin >> rows >> cols;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo g(rows*cols+1);

    char aux;
    bool matriz[rows+1][cols+1] = {false};

    for(int i = 1; i <= rows; i++){
        for(int j = 1; j <= cols; j++){

            std::cin >> aux;

            if(aux == '.'){
                matriz[i][j] = true;
            }else if(aux == 'P'){
                matriz[i][j] = false;
            }

            if(matriz[i-1][j] && i > 1){ //hay que poner de norte a sur
                g.ponArista((i-2)*cols + j, (i-1)*cols + j); //norte-sur
            }

            if(matriz[i][j-1]){
                g.ponArista((i-1)*cols + j - 1, (i-1)*cols + j); //oeste-este
            }
        }
    }

    int sol = resolver(g);
    
    std::cout << sol << std::endl;
    // escribir sol

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

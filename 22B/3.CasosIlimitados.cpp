
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <deque>

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

using Camino = std::deque<int>; // para representar cam


class CicloDirigido {
   public:

      CicloDirigido(Digrafo const& g) : visit(g.V(),false), ant(g.V()),
      apilado(g.V(),false), hayciclo(false) {
         for (int v = 0; v < g.V(); ++v)
         if (!visit[v])
         dfs(g, v);
      }
      bool hayCiclo() const { return hayciclo; }
      bool hayCicloInterno() const {return _ciclo.empty(); }
      Camino const& ciclo() const { return _ciclo; }

   private:

      std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
      std::vector<int>  ant; // ant[v] = vértice anterior en el camino a v
      std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
      Camino _ciclo; // ciclo dirigido (vacío si no existe)
      bool hayciclo;

      void dfs(Digrafo const& g, int v) {
         apilado[v] = true;
         visit[v] = true;
         for (int w : g.ady(v)) {
            if (hayciclo) // si hemos encontrado un ciclo terminamos
               return;
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
               ant[w] = v; dfs(g, w);
            } else if (apilado[w] && g.ady(w).size() == 1) { // hemos detectado un ciclo
               // se recupera retrocediendo
               hayciclo = true;
               for (int x = v; x != w; x = ant[x])
                  _ciclo.push_front(x);
               _ciclo.push_front(w); _ciclo.push_front(v);
            }
         }
         apilado[v] = false;
      }
};

std::string resolver(const Digrafo &grafo) {
   
   std::string ret;
   CicloDirigido ciclo(grafo);
   
   if(ciclo.hayCiclo())
      ret = "NUNCA";
   else if(ciclo.hayCicloInterno())
      ret = "SIEMPRE";
   else
      ret = "A VECES";

   return ret;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int v;

   std::cin >> v;

   if (!std::cin)  // fin de la entrada
      return false;
   
   char c;
   int salto;
   Digrafo grafo(v);

   for(int i = 1; i < v; i++){
      std::cin >> c;
      if(c == 'J'){
         std::cin >> salto;
         grafo.ponArista(salto, i);
      }else if(c == 'C'){
         std::cin >> salto;
         grafo.ponArista(salto-1, i);
         grafo.ponArista(i-1, i);
      }else if(c == 'A'){
         grafo.ponArista(i-1, i);

      }
   }
   

   std::string sol = resolver(grafo);
   
   // escribir sol

   std::cout << sol << std::endl;
   
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

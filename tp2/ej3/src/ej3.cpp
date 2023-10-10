#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

int cantEdificios;
int sumaRepetidores;
int sumaDistancias;


// Modifica la variable aristas. Recibe por consola los parametros.
void armarListaAristas(int cantConexiones,vector<tuple<int, int, int, int>>& aristas // Nodo 1, nodo2, distancia, nro repetidores
) {
    int nodo1;
    int nodo2;
    int distancia;
    int numeroRepetidores;
    for (int i = 0; i < cantConexiones; i++) {
        // Recibe parametros
        cin >> nodo1;
        cin >> nodo2;
        cin >> distancia;
        cin >> numeroRepetidores;

        // Arma el vector de aristas
        aristas.emplace_back(nodo1, nodo2, distancia, numeroRepetidores);
    }
}
//Estructura DSU para que funcione el kruskal

struct DSU {
    DSU(int n){
        padre = vector<int>(n);
        for(int v = 1; v < n; v++) padre[v] = v;
        tamano = vector<int>(n,1);
    }

    int find(int v){
        while(padre[v] != v) v = padre[v];
        return v;
    }

    void unite(int u, int v){
        u = find(u); v = find(v);
        if(tamano[u] < tamano[v]) swap(u,v);
        //ahora u es al menos tan grande como v
        padre[v] = u;
        tamano[u] += tamano[v];
    }

    vector<int> padre;
    vector<int> tamano;

};

float kruskal(vector<tuple<int, int, int, int>>& aristas){

    DSU dsu(cantEdificios + 1);

    int edges = 0;
    for(auto [w,u,d,r] : aristas){
        //u y v estan en distinta cc?
        if(dsu.find(u) != dsu.find(w)){
            dsu.unite(u,w);
            sumaDistancias+= d;
            sumaRepetidores+=r;
            edges++;
        }
    }
    return static_cast<float>(sumaDistancias) / static_cast<float>(sumaRepetidores);
}

int main() {

    int cantTests;
    cin >> cantTests;

    int cantConexiones;
    float c1, c2; // Los costos de los MST que vamos a comparar

    for (int i = 0; i < cantTests; i++) {

        sumaDistancias = 0;
        sumaRepetidores = 0;

        // Recibir los valores del test case
        cin >> cantEdificios;
        cin >> cantConexiones;

        vector<tuple<int, int, int, int>> aristas; // Nodo 1, nodo2, distancia, nro repetidores

        // Armar la lista de aristas, de repetidores y de distancias
        armarListaAristas(cantConexiones, aristas);

        // Establece c1 en 0 para arrancar la comparacion en el ciclo
        c1 = 0;

        // Seteo en 0 la suma de las distancias y repetidores para que no se pisen los valores.
        sumaDistancias = 0;
        sumaRepetidores = 0;

        while (true)
        {
            // Ordeno las aristas con la formula c1 * r - d y pruebo kruskal hasta que converja.
            sort(aristas.begin(), aristas.end(), [&](const auto& a, const auto& b)
            {
                float costA = c1 * get<3>(a) - get<2>(a);
                float costB = c1 * get<3>(b) - get<2>(b);
                return costA < costB;
            });

            c2 = kruskal(aristas);

            // Si el costo del llamado anterior coincide con el actual encontramos la respuesta
            if (c1 == c2) break;

            // Si no sali del ciclo es porque todavia no encontre la respuesta, seteo c1 en el costo actual, reinicio variables y voy a la prox iteracion
            sumaDistancias = 0;
            sumaRepetidores = 0;
            c1 = c2;
        }

        cout << sumaDistancias << " " << sumaRepetidores << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

vector<tuple<int, int, int, int>> aristas; // Nodo 1, nodo2, distancia, nro repetidores
vector<pair<float, pair<int, int>>> aristasRatios;
// tuple<int,int,int>;

void armarListaAristas(int cantConexiones) {
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

        // Arma la lista de adyacencias
        aristas.push_back(make_tuple(nodo1, nodo2, distancia, numeroRepetidores));
        // get<0>(adyacencias[nodo1][0]) = 'nodoVecino'; 
    } 
}


void armarListaRatios(float x) {
    for (int i = 0; i < aristas.size(); i++) {
        tuple <int,int,int,int> aristaActual = aristas[i];

        // Armar el peso  w(e) = c1 − x ⋅ c2
        float peso = get<2>(aristaActual) - x * get<3>(aristaActual);

        // Pushear la arista armada
        aristasRatios.push_back({peso, {get<0>(aristaActual), get<1>(aristaActual)}});
    }
}



// Sacado de la practica turno noche
void prim() {
    
    priority_queue<pair<int, pair<int, int>>> colaAristas;
    vector<bool> visitado(n, false);

    for(auto [w, v] : g[0]) {
        colaAristas.push(make_pair(-w, make_pair(0, v)));
    }

    visitado[0] = true;
    int edges = 0;
    int s = 0;
    while(!q.empty()){
        int w;
        pair<int, int> e;
        tie(w, e) = q.top();
        q.pop();
        if(!visitado[e.second]){
            visitado[e.second] = true;
            for(auto [w2, v] : g[e.second]){
                q.push(make_pair(-w2, make_pair(e.second, v)));
            }
            s += -w;
            edges ++;
        }
    }
    if(edges == n-1){
        cout << s << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}




int main() {

    int cantTests;
    cin >> cantTests;

    int cantEdificios;
    int cantConexiones;

    float ratio;

    for (int i = 0; i < cantTests; i++) {

        // Recibir los valores del test case
        cin >> cantEdificios;
        cin >> cantConexiones;

        aristas = {}; 
        aristasRatios = {};
        
        armarListaAristas(cantConexiones);

        ratio = prim

    }

    return 0;
}

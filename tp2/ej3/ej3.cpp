#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

vector<tuple<int, int, int, int>> aristas; // Nodo 1, nodo2, distancia, nro repetidores
int cantEdificios;
int sumaRepetidores;
int sumaDistancias;
// tuple<int,int,int>;

// Modifica la variable global aristas. Recibe por consola los parametros.
void armarListaAristas(int cantConexiones, vector<vector<int>>& dist, vector<vector<int>>& repetidores) {
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
        aristas.push_back(make_tuple(nodo1, nodo2, distancia, numeroRepetidores));
        // get<0>(adyacencias[nodo1][0]) = 'nodoVecino';

        // Arma el vector de repetidores y de distancias
        dist[nodo1][nodo2] = distancia;
        dist[nodo2][nodo1] = distancia;
        repetidores[nodo1][nodo2] = numeroRepetidores;
        repetidores[nodo2][nodo1] = numeroRepetidores;
    }
}

// Dado un numero x, arma la lista de aristas con el ratio correspondiente.
void armarListaAdyacencias(double x, vector<vector<pair<double, int>>>& aristasConPeso) {
    for (int i = 0; i < aristas.size(); i++) {
        tuple <int,int,int,int> aristaActual = aristas[i];
        int nodo1 = get<0>(aristaActual);
        int nodo2 = get<1>(aristaActual);


        // Armar el peso  w(e) = c1 - x ⋅ c2
        double peso = get<2>(aristaActual) - x * get<3>(aristaActual);

        // Armar la lista de adyacencias
        aristasConPeso[nodo1].push_back({peso, nodo2});
        aristasConPeso[nodo2].push_back({peso, nodo1});
    }
}

// Va a armar una lista de adyacencias en la cual el costo va a ser la distancia entre cada par de nodos
void armarPrimerListaAdyacencias(vector<vector<pair<double, int>>>& aristasConPeso) {
    for (int i = 0; i < aristas.size(); i++) {
        tuple <int,int,int,int> aristaActual = aristas[i];
        int nodo1 = get<0>(aristaActual);
        int nodo2 = get<1>(aristaActual);
        int distancia = get<2>(aristaActual);

        // Armar la lista de adyacencias
        aristasConPeso[nodo1].push_back({distancia, nodo2});
        aristasConPeso[nodo2].push_back({distancia, nodo1});
    }
}


// Sacado de la practica turno noche, modificado para poder usarlo en nuestra implementacion. Retorna la suma de los repetidores y de las distancias para poder calcular el ratio.
double prim_m_lg_n(vector<vector<int>>& dist, vector<vector<int>>& repetidores, vector<vector<pair<double, int>>>& aristasConPeso){
    priority_queue<pair<double, pair<int, int>>> q;
    vector<bool> visited(cantEdificios + 1, false);

    for(auto [w, v] : aristasConPeso[1]){
        q.push(make_pair(-w, make_pair(1, v)));
    }

    visited[1] = true;
    int edges = 0;
    while(!q.empty()){
        int w;
        pair<int, int> e;
        tie(w, e) = q.top();
        q.pop();
        if(!visited[e.second]){
            visited[e.second] = true;
            for(auto [w2, v] : aristasConPeso[e.second]){
                q.push(make_pair(-w2, make_pair(e.second, v)));
            }
            // Actualiza variables globales al agregar una arista al MST
            sumaDistancias += dist[e.first][e.second];
            sumaRepetidores += repetidores[e.first][e.second];
            edges ++;
        }
    }

    // Devuelve el costo del MST
    return static_cast<double>(sumaDistancias) / static_cast<double>(sumaRepetidores);
}


int main() {

    int cantTests;
    cin >> cantTests;


    int cantConexiones;
    double c1, c2; // Los costos de los MST que vamos a comparar


    for (int i = 0; i < cantTests; i++) {

        sumaDistancias = 0;
        sumaRepetidores = 0;

        // Recibir los valores del test case
        cin >> cantEdificios;
        cin >> cantConexiones;

        vector<vector<int>> dist(cantEdificios + 1, vector<int>(cantEdificios + 1)); // Para un par de nodos tiene el costo del repetidor
        vector<vector<int>> repetidores(cantEdificios + 1, vector<int>(cantEdificios + 1)); // Para un par de nodos tiene la distancia entre ellos
        vector<vector<pair<double, int>>> aristasConPeso(cantEdificios + 1); // El primer elemento del pair es el costo, el segundo el nodo del que es vecino

        // Armar la lista de aristas, de repetidores y de distancias
        armarListaAristas(cantConexiones, dist, repetidores);

        armarPrimerListaAdyacencias(aristasConPeso); // Armo una lista de adyacencias con la distancia en el peso para poder hacer el primer llamado a prim

        // Primer llamado a prim
        c1 = prim_m_lg_n(dist, repetidores,aristasConPeso);
        // Seteo en 0 la suma de las distancias y repetidores para que no se pisen los valores.
        sumaDistancias = 0;
        sumaRepetidores = 0;

        while (true)
        {
            vector<vector<pair<double, int>>> aristasConPeso(cantEdificios + 1); // Limpiar el vector de adyacencias
            armarListaAdyacencias(c1, aristasConPeso); // Actualizo el valor de las aristas con el nuevo costo obtenido.
            c2 = prim_m_lg_n(dist, repetidores, aristasConPeso); // Llamado a prim con la lista de aristas actualizada

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




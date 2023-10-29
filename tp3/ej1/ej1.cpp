#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

// Sacado de https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/graph/dijkstra.cpp
int dijkstra(vector<vector<pair<int, int>>>& adyacencias, int s, int t) {

    int n = adyacencias.size();
    
    // Usamos una matriz de distancias para llevar un seguimiento de los túneles utilizados
    vector<vector<int>> dist(n, vector<int>(4, 1e7));  

    // Cola de prioridad que almacena tuplas de {distAcumulada, nodoActual, tunelesUsados}, 
    // y los ordena según cuál tenga la distancia acumulada más chica
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    
    // Nodo inicial
    pq.push(make_tuple(0, s, 0));
    dist[s][0] = 0;

    while (!pq.empty()) {

        // Sacamos el nodo con la menor distancia acumulada
        int nodoActual = get<1>(pq.top());
        int distAcumulada = get<0>(pq.top());
        int tunelesUsados = get<2>(pq.top());
        pq.pop();

        // Si la distancia acumulada es mayor a la ya guardada, seguimos con el que sigue
        if (distAcumulada > dist[nodoActual][tunelesUsados]) 
            continue;
        
        // Para cada una de los nodos alcanzables desde el actual, vemos si podemos mejorar la distancia
        for (pair<int, int> arista : adyacencias[nodoActual]) {

            // Calculamos la distancia hasta el nodo, teniendo en cuenta la acumulada
            int proximoNodo = arista.first;
            int peso = arista.second;
            int nuevaDist = distAcumulada + peso;
            
            int nuevosTunelesUsados = tunelesUsados;

            // Si la arista tenia peso 2, es un tunel
            if (peso == 2) 
                nuevosTunelesUsados++;
            
            // Si usamos menos de 3 tuneles, y la distancia es mejor a la guardada, la actualizamos
            if (nuevosTunelesUsados <= 3 && nuevaDist < dist[proximoNodo][nuevosTunelesUsados]) {
                dist[proximoNodo][nuevosTunelesUsados] = nuevaDist;
                pq.push(make_tuple(nuevaDist, proximoNodo, nuevosTunelesUsados));
            }
        }
    }

    // Buscamos la distancia minima en el destino
    int minDist = 1e7;
    for (int tunelesUsados = 0; tunelesUsados <= 3; tunelesUsados++) 
        minDist = min(minDist, dist[t][tunelesUsados]);
    
    if (minDist != 1e7) 
        return minDist;
    
    return -1;
}


int main() {

    int cantTests;
    cin >> cantTests;

    for (int i = 0; i < cantTests; i++) {
        // Recibir los valores del caso de test
        int cantSalones;
        int cantTuneles;
        cin >> cantSalones;
        cin >> cantTuneles;
        vector<vector<pair<int, int>>> listaAdyacencias(cantSalones + 1);

        // Recibir la entrada y salida de cada tunel
        int posEntrada;
        int posSalida;
        int weight = 2;
        for (int j = 0; j < cantTuneles; j++) {
            cin >> posEntrada;
            cin >> posSalida;
            listaAdyacencias[posEntrada].push_back({posSalida, weight});
        }

        // Definir la arista que representa el salto entre salones para cada uno
        for (int k = 1; k < cantSalones; k++)
            listaAdyacencias[k].push_back({k + 1, 1});
        
        int respuesta = dijkstra(listaAdyacencias, 1, cantSalones);

        // Sumamos 1 porque es lo que tarda en llegar al primer nodo.
        cout << respuesta + 1 << endl;
    }
    return 0;
}
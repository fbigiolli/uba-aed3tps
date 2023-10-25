#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <utility>
#include <tuple>
#include <vector>


using namespace std;

// from https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/graph/dijkstra.cpp
int dijkstra(vector<vector<pair<int, int>>>adj, int s, int t) {
    int n = adj.size();
    vector<vector<int>> dist(n, vector<int>(4, 1e7));  // Usamos una matriz de distancias para llevar un seguimiento de los túneles utilizados
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.push(make_tuple(0, s, 0));
    dist[s][0] = 0;

    while (!pq.empty()) {
        int currentNode = get<1>(pq.top());
        int currentDist = get<0>(pq.top());
        int tunnelsUsed = get<2>(pq.top());
        pq.pop();

        if (currentDist > dist[currentNode][tunnelsUsed]) {
            continue;
        }

        for (pair<int, int> edge : adj[currentNode]) {
            int nextNode = edge.first;
            int edgeWeight = edge.second;
            int newDist = currentDist + edgeWeight;
            
            int newTunnelsUsed = tunnelsUsed;
            if (edgeWeight == 2) {
                newTunnelsUsed++;
            }

            if (newTunnelsUsed <= 3 && newDist < dist[nextNode][newTunnelsUsed]) {
                dist[nextNode][newTunnelsUsed] = newDist;
                pq.push(make_tuple(newDist, nextNode, newTunnelsUsed));
            }
        }
    }

    int minDist = 1e7;
    for (int tunnelsUsed = 0; tunnelsUsed <= 3; tunnelsUsed++) {
        minDist = min(minDist, dist[t][tunnelsUsed]);
    }

    if (minDist != 1e7) {
        return minDist;
    }
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
        for (int j = 0; j < cantTuneles; j++)
        {
            cin >> posEntrada;
            cin >> posSalida;
            listaAdyacencias[posEntrada].push_back({posSalida,weight});
        }

        // Definir la arista que representa el salto entre salones para cada uno
        for (int k = 1; k < cantSalones; k++)
        {
            listaAdyacencias[k].push_back({k+1,1});
        }

        int respuesta = dijkstra(listaAdyacencias,1,cantSalones);

        // Sumamos 1 porque es lo que tarda en llegar al primer nodo.
        cout << respuesta + 1 << endl;
    }
    return 0;
}
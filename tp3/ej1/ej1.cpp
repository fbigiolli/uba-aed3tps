#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

constexpr int64_t INF = numeric_limits<int64_t>::max();

// from https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/graph/dijkstra.cpp
int dijkstra(vector<vector<pair<int, int>>> *adj, int s, int t) {
    /// n denotes the number of vertices in graph
    int n = adj->size();

    /// setting all the distances initially to INF
    vector<int64_t> dist(n, INF);

    /// creating a min heap using priority queue
    /// first element of pair contains the distance
    /// second element of pair contains the vertex
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                        greater<pair<int, int>>>
        pq;

    /// pushing the source vertex 's' with 0 distance in min heap
    pq.push(make_pair(0, s));

    /// marking the distance of source as 0
    dist[s] = 0;

    while (!pq.empty()) {
        /// second element of pair denotes the node / vertex
        int currentNode = pq.top().second;

        /// first element of pair denotes the distance
        int currentDist = pq.top().first;

        pq.pop();

        /// for all the reachable vertex from the currently exploring vertex
        /// we will try to minimize the distance
        for (pair<int, int> edge : (*adj)[currentNode]) {
            /// minimizing distances
            if (currentDist + edge.second < dist[edge.first]) {
                dist[edge.first] = currentDist + edge.second;
                pq.push(make_pair(dist[edge.first], edge.first));
            }
        }
    }
    if (dist[t] != INF) {
        return dist[t];
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
        for (int k = 1; k < cantSalones - 1; k++)
        {
            listaAdyacencias[k].push_back({k+1,1});
        }

        int respuesta = 
        
    }
    return 0;
}

    // int dijkstra(vector<vector<pair<int, int>>> *adj, int s, int t) {
    //     int n = adj->size();
    //     vector<vector<int64_t>> dist(n, vector<int64_t>(4, INF));  // Usamos una matriz de distancias para llevar un seguimiento de los túneles utilizados
    //     priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    //     pq.push(make_tuple(0, s, 0));
    //     dist[s][0] = 0;

    //     while (!pq.empty()) {
    //         int currentNode = get<1>(pq.top());
    //         int currentDist = get<0>(pq.top());
    //         int tunnelsUsed = get<2>(pq.top());
    //         pq.pop();

    //         if (currentDist > dist[currentNode][tunnelsUsed]) {
    //             continue;
    //         }

    //         for (pair<int, int> edge : (*adj)[currentNode]) {
    //             int nextNode = edge.first;
    //             int edgeWeight = edge.second;
    //             int newDist = currentDist + edgeWeight;

    //             int newTunnelsUsed = tunnelsUsed;
    //             if (edgeWeight == 2) {
    //                 newTunnelsUsed++;
    //             }

    //             if (newTunnelsUsed <= 3 && newDist < dist[nextNode][newTunnelsUsed]) {
    //                 dist[nextNode][newTunnelsUsed] = newDist;
    //                 pq.push(make_tuple(newDist, nextNode, newTunnelsUsed));
    //             }
    //         }
    //     }

    //     int minDist = INF;
    //     for (int tunnelsUsed = 0; tunnelsUsed <= 3; tunnelsUsed++) {
    //         minDist = min(minDist, dist[t][tunnelsUsed]);
    //     }

    //     if (minDist != INF) {
    //         return minDist;
    //     }
    //     return -1;
    // }

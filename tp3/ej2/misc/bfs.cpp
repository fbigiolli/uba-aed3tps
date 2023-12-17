#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> grafo;  // Representación del grafo en forma de lista de adyacencia
vector<bool> visitado;      // Para llevar un registro de los nodos visitados
vector<int> distancia;      // Para almacenar la distancia desde el nodo fuente

// Búsqueda en amplitud para encontrar la distancia más corta desde el origen al destino
int bfs(int origen, int destino) {
    queue<int> cola;
    visitado.assign(grafo.size(), false);
    distancia.assign(grafo.size(), -1);

    cola.push(origen);
    visitado[origen] = true;
    distancia[origen] = 0;

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        // Explorar los vecinos del nodo actual
        for (int vecino : grafo[actual]) {
            if (!visitado[vecino]) {
                cola.push(vecino);
                visitado[vecino] = true;
                distancia[vecino] = distancia[actual] + 1;
            }
        }
    }

    // Devolver la distancia desde el origen al destino
    return distancia[destino];
}

int main() {
    int n, m;  // Número de nodos y aristas
    cin >> n >> m;

    // Inicializar el grafo con n nodos
    grafo.resize(n);

    // Leer las aristas del grafo
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // Suponiendo que el grafo es no dirigido
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }

    int origen, destino;
    cin >> origen >> destino;

    int distanciaMasCorta = bfs(origen, destino);

    if (distanciaMasCorta == -1) {
        cout << "No hay un camino desde " << origen << " hasta " << destino << endl;
    } else {
        cout << "La distancia más corta desde " << origen << " hasta " << destino << " es: " << distanciaMasCorta << endl;
    }

    return 0;
}

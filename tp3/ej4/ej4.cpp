#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

const int INF = 1e7;
int n;

/* La idea es modelar el problema interpretando el grafo como la cantidad de personas que pueden ir desde s a t llevando una cantidad c de herramientas cada una.
Para esto, dividimos la capacidad de cada arista por la cant de herramientas, de modo que justamente cada arista del grafo represente la cant de personas que pueden pasar por ella.
Usamos una busqueda binaria para encontrar el maximo valor posible de herramientas por persona. Cuando converge la busqueda binaria es porque encontramos el resultado final.
*/

int bfs(int s, int t, vector<int>& parent, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent, capacity, adj)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {

    int cantTests;
    cin >> cantTests;

    for (int i = 0; i < cantTests; i++) {

        int cantEsquinas;
        int cantCalles;
        int cantPersonas;

        cin >> cantEsquinas;
        cin >> cantCalles;
        cin >> cantPersonas;

        n = cantEsquinas;

        vector<vector<int>> adyacencias(cantEsquinas);
        vector<vector<int>> capacity(cantEsquinas, vector<int>(cantEsquinas, 0));
        vector<vector<int>> tempCapacity(cantEsquinas, vector<int>(cantEsquinas, 0));

        int desde;
        int hasta;
        int maxHerramientas;

        int minCantHerramientasTotal = INF;
        int maxCantHerramientasTotal = 0;

        for(int j = 0; j < cantCalles; j++) {
            cin >> desde;
            cin >> hasta;
            cin >> maxHerramientas;

            maxCantHerramientasTotal = max(maxCantHerramientasTotal, maxHerramientas);
            minCantHerramientasTotal = min(minCantHerramientasTotal, maxHerramientas);
            
            // Corregimos para indexar desde 0  
            desde--;
            hasta--;
 
            adyacencias[desde].push_back(hasta);
            adyacencias[hasta].push_back(desde);
            capacity[desde][hasta] = maxHerramientas;
        }

        // Hacemos una busqueda binaria para encontrar la mayor cantidad posible de herramientas por persona
        int left = minCantHerramientasTotal / cantPersonas + 1;
        int right = maxCantHerramientasTotal;
        int mid;
        int flow;
        while (left <= right) {
            mid = (left + right) / 2;

            // Actualizamos valor de las aristas
            for (int j = 0; j < capacity.size(); j++) {
                for (int k = 0; k < capacity.size(); k++) {
                    tempCapacity[j][k] = capacity[j][k] / mid;
                }
            }

            flow = maxflow(0, cantEsquinas - 1, tempCapacity, adyacencias);
            if (flow >= cantPersonas){
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        cout << min(left,right) * cantPersonas << endl;


    }



    return 0;
}
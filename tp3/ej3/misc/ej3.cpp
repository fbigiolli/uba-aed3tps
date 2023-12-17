    /*
    * Author: Amit Kumar
    * Created: May 24, 2020
    * Copyright: 2020, Open-Source
    * Last Modified: May 25, 2020
    */
    #include <algorithm>
    #include <bitset>
    #include <cstring>
    #include <iostream>
    #include <limits>
    #include <queue>
    #include <tuple>
    #include <utility>
    #include <vector>
    #include <iostream>
    #include <list>

    using namespace std;

    // max capacity of node in graph
    const int MAXN = 505;
    class Graph {
        vector<vector<int> > residual_capacity, capacity;
        int total_nodes = 0;
        int total_edges = 0, source = 0, sink = 0;
        vector<int> parent;
        vector<tuple<int, int, int> > edge_participated;
        bitset<MAXN> visited;
        int max_flow = 0;
        bool bfs(int source, int sink) {  //  to find the augmented - path
            visited.reset();
            queue<int> q;
            q.push(source);
            bool is_path_found = false;
            while (q.empty() == false && is_path_found == false) {
                int current_node = q.front();
                visited.set(current_node);
                q.pop();
                for (int i = 0; i < total_nodes; ++i) {
                    if (residual_capacity[current_node][i] > 0 && !visited[i]) {
                        visited.set(i);
                        parent[i] = current_node;
                        if (i == sink) {
                            return true;
                        }
                        q.push(i);
                    }
                }
            }
            return false;
        }

    public:

        void ford_fulkerson() {
            while (bfs(source, sink)) {
                int current_node = sink;
                int flow = numeric_limits<int>::max();
                while (current_node != source) {
                    int parent_ = parent[current_node];
                    flow = min(flow, residual_capacity[parent_][current_node]);
                    current_node = parent_;
                }
                current_node = sink;
                max_flow += flow;
                while (current_node != source) {
                    int parent_ = parent[current_node];
                    residual_capacity[parent_][current_node] -= flow;
                    residual_capacity[current_node][parent_] += flow;
                    current_node = parent_;
                }
            }
        }

    };

    int main() {

        int cantTests;
        cin >> cantTests;

        for (int i = 0; i < cantTests; i++) {
            // Recibir los valores del caso de test
            int size;
            cin >> size;

            // Armar el tablero
            vector<vector<int>> tablero(size,vector<int>(size));
            for (int k = 0; k < size; k++)
            {
                for (int j = 0; j < size; j++)
                {
                int estado;
                cin >> estado;
                tablero[i][j] = estado;  
                }
            }
            
            /*Vamos a modelar el problema con dos subconjuntos: uno que contenga subfilas y otro que contenga subcolumnas, separados por casilleros rotos
            Los vamos a representar con un pair que simboliza principio y fin.*/

            vector<list<pair<int,int>>> subfilas;
            vector<list<pair<int,int>>> subcolumnas;

            // Recorrer el tablero para armar subfilas y subcolumnas
            for (int fila = 0; fila < tablero.size(); fila++)
            {
                int inicioSubfila = 0;
                for (int col = 0; col < tablero.size(); col++)
                {
                    if (tablero[fila][col] == 1 || col == tablero.size() - 1) 
                    {
                        if (inicioSubfila != col)
                        {
                            subfilas[fila].push_back({inicioSubfila,col - 1});
                        }
                        
                        inicioSubfila = col + 1;
                    }
                }
            }
            
                //Ahora hacemos lo mismo para las subcolumnas
            for (int fila = 0; fila < tablero.size(); fila++)
            {
                int inicioSubcolumna = 0;
                for (int col = 0; col < tablero.size(); col++)
                {
                    if (tablero[col][fila] == 1 || fila == tablero.size() - 1) 
                    {
                        if (inicioSubcolumna != fila)
                        {
                            subcolumnas[col].push_back({inicioSubcolumna,fila - 1});
                        }
                        
                        inicioSubcolumna = fila + 1;
                    }
                }

                // 1 0 0 1 
                // 0 0 1 0
                // 1 0 1 0
                // 1 0 1 1
                
            }
        }
        return 0;
    }

    vector<vector<int>> tablero = {{1,0,0,1},
                                    {0,0,1,0},
                                    {1,0,1,0},
                                    {1,0,1,1}};
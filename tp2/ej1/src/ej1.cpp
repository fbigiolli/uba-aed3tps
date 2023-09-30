#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int noVisto = 0, visto = 2;

// Aristas del grafo, ya con una ignorada
vector<vector<int>> aristas;

// Aristas que pasan desde el juez
vector<pair<int, int>> links;

vector<int> padre;
vector<int> estado;

int cantBases;
int cantLinks;

vector<pair<int, int>> linksImportantes;

// Tiempo que un nodo tomó para ser visitado
vector<int> tiempoVisto;

// Mínimo tiempo de visita de todos los nodos adyacentes (y distintos al padre) de un nodo
vector<int> minTiempoVisto;

int tiempo;
int bridges;

void dfsPuentes(int v) {

    estado[v] = visto;

    tiempoVisto[v] = tiempo;
    minTiempoVisto[v] = tiempo;
    tiempo++;

    for(int u : aristas[v]) {

        if(u == padre[v])
            continue;

        if(estado[u] == noVisto) {
            
            padre[u] = v;

            dfsPuentes(u);
            
            minTiempoVisto[v] = min(minTiempoVisto[v], minTiempoVisto[u]);

            if(minTiempoVisto[u] > tiempoVisto[v]) 
                bridges++;

        }   

        else if(u != padre[v]) 
            minTiempoVisto[v] = min(minTiempoVisto[u], minTiempoVisto[v]);        

    }

}

void armarListas(int links_amount, int ignorar) {

    for (int i = 0; i < links_amount; i++) {
        if(i != ignorar) {
            // Recibir los valores de las bases
            int base1 = links[i].first;
            int base2 = links[i].second;

            // Marcar como vecinas ambas bases
            aristas[base1].push_back(base2);
            aristas[base2].push_back(base1);
        }
    }
}

void probarAristas(int cantLinks) {

    for(int i = 0; i < cantLinks; i++) {

        armarListas(cantLinks, i);
        dfsPuentes(0);

        if(bridges != 0)
            linksImportantes.push_back(links[i]);
            
        bridges = 0;

        aristas = vector<vector<int>>(cantBases);

        padre = vector<int>(cantBases);
        estado = vector<int>(cantBases);

        tiempoVisto = vector<int>(cantBases);

        minTiempoVisto = vector<int>(cantBases);

        tiempo = 1;

    }

}

void acomodarEImprimirLinks() {

    sort(linksImportantes.begin(), linksImportantes.end());

    cout << linksImportantes.size() << endl;

    for(auto [v, w] : linksImportantes)
        cout << v << " " << w << endl;
}

int main() {   
    int cantTests;
    cin >> cantTests;

    for (int i = 0; i < cantTests; i++) {

        // Recibir los valores del test case

        cin >> cantBases;
        cin >> cantLinks;

        links = {};

        for(int j = 0; j < cantLinks; j++) {
            int base1;
            int base2;
            cin >> base1;
            cin >> base2;

            if(base1 < base2)
                links.push_back({base1, base2});
            else
                links.push_back({base2, base1});
        }

        bridges = 0;
        linksImportantes = {};

        aristas = vector<vector<int>>(cantBases);

        padre = vector<int>(cantBases);
        estado = vector<int>(cantBases);

        tiempoVisto = vector<int>(cantBases);

        minTiempoVisto = vector<int>(cantBases);

        tiempo = 1;

        probarAristas(cantLinks);

        acomodarEImprimirLinks();

    }
   
    return 0;
}

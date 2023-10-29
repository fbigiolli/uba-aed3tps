#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// MODELA EL GRAFO COMO UN DAG Y BUSCA EL CAMINO MINIMO

int INF = 1e7;

// Esta función no terminó funcionando (ja) en algún casó especifico del juez
// Si se ponen todas las aristas en todos los niveles (incluso las que no van a ser usadas), anda joya
// La dejamos por la parte que arma los tuneles
void buscarSalidas(int cantSalones, int cantTuneles, vector<int>& salidas, vector<pair<int,int>>& tuneles) {

    // A partir del 2do nivel, solo pongo aristas entre salones a partir del 1er salón "llegable" desde el nivel anterior
        
    // Voy a buscar las 3 salidas más a la izquierda, pero que empiecen a partir de la anterior
    // Es decir, sean Xi, Yi las posiciones de entrada y salida de los 3 tuneles que estoy buscando
    // Quiero que Y1 sea la menor de todas las Yi posibles, y que X2 >= Y1, y así con las siguientes
    // Esto me sirve porque sé que al nivel 2 solo voy a poder "recorrerlo" a partir de Y1, y no necesito armar lo que haya antes, y así

    int salida1 = cantSalones + 1;
    int salida2 = cantSalones + 1;
    int salida3 = cantSalones + 1;

    int posEntrada;
    int posSalida;

    // Los salones y tuneles que puedan ser recorridos desde el segundo nivel van a ser solamente los que estén a la derecha de esta salida
    for(int k = 0; k < cantTuneles; k++) {
        
        cin >> posEntrada;
        cin >> posSalida;

        tuneles[k] = {posEntrada, posSalida};

        salida1 = min(salida1, posSalida);
        
        if(posEntrada >= salida1)
            salida2 = min(salida2, posSalida);

        if(posEntrada >= salida2)
            salida3 = min(salida3, posSalida);
    }
    
    // Desplazo las salidas a sus correspondientes niveles (si existen)
    salida1 = (salida1 != cantSalones + 1) ? salida1 + 1 * cantSalones : 4 * cantSalones + 1;
    salida2 = (salida2 != cantSalones + 1) ? salida2 + 2 * cantSalones : 4 * cantSalones + 1;
    salida3 = (salida3 != cantSalones + 1) ? salida3 + 3 * cantSalones : 4 * cantSalones + 1;
    
    salidas = {1, salida1, salida2, salida3};

}

void armarAdyacencias(vector<list<pair<int, int>>>& adyacencias, int cantSalones, vector<int>& salidas, vector<pair<int,int>>& tuneles) {

    // Adyacencias[(i - 1) * cantSalones + 1, i * cantSalones + 1] es el iésimo nivel, 1 <= i <= 4

    // Agrego la fuente con costo 1
    adyacencias[0].push_back({1, 1});

    // Por cada nivel, agrego las aristas necesarias
    for(int i = 0; i <= 3; i++) {

        // Aristas entre salones
        for(int j = i * cantSalones + 1; j < (i + 1) * cantSalones; j++) 
            adyacencias[j].push_back({j + 1, 1});
        
        // Arista al sumidero
        adyacencias[(i + 1) * cantSalones].push_back({4 * cantSalones + 1, 0});

        // Tuneles
        for(int k = 0; k < tuneles.size(); k++) {
            int desde = tuneles[k].first + i * cantSalones;
            int hasta = tuneles[k].second + (i + 1) * cantSalones;
            if(hasta <  4 * cantSalones + 1)
                adyacencias[desde].push_back({hasta, 2});
            
        }
    }

    /*
    // Por cada nivel, agrego las aristas necesarias a partir de la respectiva salida
    for(int i = 0; i <= 3; i++) {

        // Aristas entre salones
        for(int j = salidas[i]; j < (i + 1) * cantSalones; j++) 
            adyacencias[j].push_back({j + 1, 1});
        
        // Arista al sumidero
        adyacencias[(i + 1) * cantSalones].push_back({4 * cantSalones + 1, 0});

        // Tuneles
        for(int k = 0; k < tuneles.size(); k++) {
            if(tuneles[k].first + i * cantSalones >= salidas[i]) {
                int desde = tuneles[k].first + i * cantSalones;
                int hasta = tuneles[k].second + (i + 1) * cantSalones;
                if(hasta <  4 * cantSalones + 1)
                    adyacencias[desde].push_back({hasta, 2});
            }
        }
    }
    

    // Mostrar adyacencias
    for(int i = 0; i < adyacencias.size(); i++) {
        if(!adyacencias[i].empty()) {
            cout << "Las aristas del nodo " << i << " van a: ";
            for(auto it = adyacencias[i].begin(); it != adyacencias[i].end(); ++it) {
                int a = it->first;
                int b = it->second;
                cout << a << " ";
            }
            cout << endl;
        }
    }
    
    // Mostrar salidas
    cout << "La salida 1 es: " << salidas[1] << endl;
    cout << "La salida 2 es: " << salidas[2] << endl;
    cout << "La salida 3 es: " << salidas[3] << endl;
    */    
}

void caminoMinimo(const vector<list<pair<int, int>>>& adyacencias) {
    
    vector<int> distancias(adyacencias.size(), INF);
    distancias[0] = 0;

    for (int u = 0; u < adyacencias.size(); u++) {
        if (distancias[u] != INF) {
            for (const auto& nodoVecino : adyacencias[u]) {
                int v = nodoVecino.first;
                int peso = nodoVecino.second;
                if (distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                }
            }
        }
    }

    cout << distancias[distancias.size() - 1] << endl;

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

        // Armo el grafo de 4 niveles (usando 0, 1, 2 y 3 pasadizos, y un nodo "fuente" y un "sumidero")
        vector<list<pair<int, int>>> adyacencias(4 * cantSalones + 2);

        vector<pair<int,int>> tuneles(cantTuneles);

        vector<int> salidas(4);

        buscarSalidas(cantSalones, cantTuneles, salidas, tuneles);

        armarAdyacencias(adyacencias, cantSalones, salidas, tuneles);

        // Y como el orden que queda ya es topológico, puedo usar el algoritmo de camino minimo en DAGs
        caminoMinimo(adyacencias);
    }

    return 0;
}
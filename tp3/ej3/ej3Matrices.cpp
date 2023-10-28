#include <iostream>
#include <vector>
#include <list>

using namespace std;

/*

IDEA

Recibimos la matriz del tablero

// { 1, 0, 0, 1},
// { 0, 0, 1, 0},
// { 1, 0, 1, 0},
// { 1, 0, 1, 1};

Armamos dos matrices más, recorriendo la primera y contando primero la cantidad de subfilas y luego la cantidad de subcolumnas
Ponemos en cada posición a qué subfila y subcolumna corresponde (que van a ser nodos en el grafo). Ponemos -1 donde no haya ninguna

// {-1, 1, 1,-1},
// { 2, 2,-1, 3},
// {-1, 4,-1, 5},
// {-1, 6,-1,-1};

// {-1, 8, 9,-1},
// { 7, 8,-1,10},
// {-1, 8,-1,10},
// {-1, 8,-1,-1};

Recorremos la matriz de subfilas, y en cada posición (x, y) distinta a -1, nos fijamos que hay en (x, y) en la matriz de subcolumnas, 
y agregamos la arista subfilas[x][y] -> subcolumnas[x][y] con capacidad 1 al grafo


*/

// { 1, 0, 0, 1},
// { 0, 0, 1, 0},
// { 1, 0, 1, 0},
// { 1, 0, 1, 1};

pair<int, int> armarMatrices(vector<vector<int>>& tablero, vector<vector<int>>& subfilas, vector<vector<int>>& subcolumnas) {

    // Ultima subfila o subcolumna considerada
    int ultimo = 1;
    int cantSubfilas = 0;
    int cantSubcolumnas = 0;
    bool ultimoFueCero = false;

    // Matriz de subfilas
    for(int fila = 0; fila < tablero.size(); fila++) {

        for(int col = 0; col < tablero.size(); col++) {

            if(tablero[fila][col] == 0) {
                subfilas[fila][col] = ultimo;
                cantSubfilas = ultimo;
                ultimoFueCero = true;
                if(col == tablero.size() - 1)
                    ultimo++;
            }

            else if(tablero[fila][col] == 1 && ultimoFueCero) {
                ultimo++;
                ultimoFueCero = false;
            }
        }
        
        ultimoFueCero = false;
    }

    // Matriz de subfilas
    for(int col = 0; col < tablero.size(); col++) {
        
        for(int fila = 0; fila < tablero.size(); fila++) {  

            if(tablero[fila][col] == 0) {
                subcolumnas[fila][col] = ultimo;
                cantSubcolumnas = ultimo;
                ultimoFueCero = true;
                if(fila == tablero.size() - 1)
                    ultimo++;
            }

            else if(tablero[fila][col] == 1 && ultimoFueCero) {
                ultimo++;
                ultimoFueCero = false;
            }
        }
        ultimoFueCero = false;
    }

    cantSubcolumnas -= cantSubfilas;
    
    return {cantSubfilas, cantSubcolumnas};

}

void armarAdyacencias(vector<vector<int>>& subfilas, vector<vector<int>>& subcolumnas, vector<list<pair<int, int>>>& adyacencias, int cantSubfilas, int cantSubcolumnas) {

    // Agrego s con aristas a todas las subfilas
    for(int i = 1; i <= cantSubfilas; i++) 
        adyacencias[0].push_back({i, 1});

    // Recorro la matriz y voy agregando las adyacencias necesarias
    for(int fila = 0; fila < subfilas.size(); fila++) {
        for(int col = 0; col < subfilas.size(); col++) {
            if(subfilas[fila][col] != -1) {
                int desde = subfilas[fila][col];
                int hasta = subcolumnas[fila][col];
                adyacencias[desde].push_back({hasta, 1});
            }
        }
    }

    // Agrego todas las subcolumnas con aristas a t
    for(int i = 1; i <= cantSubcolumnas; i++) 
        adyacencias[cantSubfilas + i].push_back({cantSubfilas + cantSubcolumnas + 1, 1});
    
}

int main() {   
    
    vector<vector<int>>tablero = {{1,0,0,1},
                                  {0,0,1,0},
                                  {1,0,1,0},
                                  {1,0,1,1}};

    int sizeTablero = tablero.size();

    vector<vector<int>> subfilas(tablero.size(), vector<int>(tablero.size(), -1));
    vector<vector<int>> subcolumnas(tablero.size(), vector<int>(tablero.size(), -1));

    // Cantidad de nodos de las subfilas y de las subcolumnas
    pair<int, int> cantNodos = armarMatrices(tablero, subfilas, subcolumnas);
    
    // cout << cantNodos.first << " " << cantNodos.second;
    
    /*
    // Mostrar matrices
    for(int i = 0; i < subfilas.size(); i++) {
        for(int j = 0; j < subfilas.size(); j++) {
            if(subfilas[i][j] != -1 && subfilas[i][j] < 10)
                cout << " " << subfilas[i][j] << " ";
            else
                cout << subfilas[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    for(int i = 0; i < subcolumnas.size(); i++) {
        for(int j = 0; j < subcolumnas.size(); j++) {
            if(subcolumnas[i][j] != -1 && subcolumnas[i][j] < 10)
                cout << " " << subcolumnas[i][j] << " ";
            else
                cout << subcolumnas[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */

    // Dejo espacio para s y t
    vector<list<pair<int, int>>> adyacencias(cantNodos.first + cantNodos.second + 2);

    armarAdyacencias(subfilas, subcolumnas, adyacencias, cantNodos.first, cantNodos.second);

    /*
    // Mostrar adyacencias
    for(int i = 0; i < adyacencias.size(); i++) {
        cout << "Las aristas del nodo " << i << " van a: ";
        for(auto it = adyacencias[i].begin(); it != adyacencias[i].end(); ++it) {
            int a = it->first;
            int b = it->second;
            cout << a << " ";
        }
        cout << endl;
    }
    */

    return 0;
}
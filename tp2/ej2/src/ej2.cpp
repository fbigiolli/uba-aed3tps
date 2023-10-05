#include <iostream>
#include <vector>
#include <queue> 

using namespace std;

int cantFilas;
int cantColumnas;

vector<vector<int>> mapa;
pair<int, int> hospital;
pair<int, int> paciente;

vector<bool> visitado;
vector<vector<int>> adyacencias;

vector<int> tiempoVisitado;

int tiempoIda;

int nodoHospital;
int nodoPaciente;
int nodoTarget;
bool esPosible = true;

int matrizANodo(int i, int j) { return cantColumnas * i + j; }

bool arrancoManifestacion(int nodoPadre, int nodoActual){

    int i = nodoActual / cantColumnas;
    int j = nodoActual % cantColumnas;

    // No va a haber nunca una manifestación en esa posición
    if(mapa[i][j] == 0)
        return false;
    
    // Segun el mapa va a haber una manifestacion
    else { 
        int tiempoActual = tiempoVisitado[nodoPadre] + 1;
       // Si el tiempo del recorrido actual es mayor o igual al de inicio de la manifestacion, devuelve true
        if(tiempoActual >= mapa[i][j])
            return true;

        // Si no, devuelve false
        else
            return false;
    }
}

void bfs(int v) {
    visitado[v] = true;
    // cout << " " << v << ",";
    queue<int> q;
    q.push(v);
    while(!q.empty()) {
        int s = q.front();
        q.pop();
        for(int u : adyacencias[s]) {
            if(u != -1 && !visitado[u] && !arrancoManifestacion(s, u)) {
                visitado[u] = true;
                tiempoVisitado[u] = tiempoVisitado[s] + 1;
                // Si llegamos al nodo target
                if(u == nodoTarget){
                    tiempoIda = tiempoVisitado[nodoTarget];
                    return;
                }
                // cout << " " << u << ",";
                q.push(u);
            }
        }
    }
    if (!visitado[nodoTarget]) 
        esPosible = false;
}


/*
cantColumnas * (i) + j  = nodo
i = (nodo - j)/cantColumnas
j = nodo - caantColumnas *

0   0   0   0   0 
P   0   0   4   0
0   0   0   0   0
0   0   0   2   0   
0   5   0   H   0
0   0   0   0   0

0 0 0 0 0 | P 0 0 4 0 | 0 0 0 0 0 | 0 0 0 2 0 | 0 5 0 H 0 | 0 0 0 0 0
c
4   3  -> Hospital
1   0  -> Paciente

 0   1   2   3   4 
 5   6   7   8   9
10  11  12  13  14
15  16  17  18  19   
20  21  22  23  24
25  26  27  28  29

*/

// Idea: llenar los bordes a mano y el resto a lo bruto

void pasarAGrafo() {
    int largoFila = cantColumnas;

    // Si tenemos una sola fila
    if (cantFilas == 1) {
        if(cantColumnas >= 2) {

            for(int i = 0; i < cantColumnas; i++) {

                // Si es el de la izquierda
                if(i == 0)
                    adyacencias[0][0] = i + 1;

                // Si es el de la derecha
                else if(i == cantColumnas - 1)
                    adyacencias[cantColumnas - 1][0] = i - 1;

                // Las del medio
                else {
                    adyacencias[i][0] = i + 1; //El de la derecha
                    adyacencias[i][1] = i - 1; //El de la izquierda
                }
            }
        }  
    }

    // Si tenemos una sola columna
    else if(cantColumnas == 1) {
        
        if(cantFilas >= 2) {

            for(int i = 0; i < cantFilas; i++) {

                // Si es el de arriba
                if(i == 0)
                    adyacencias[0][0] = i + 1;

                // Si es el de abajo
                else if(i == cantFilas - 1)
                    adyacencias[cantFilas - 1][0] = i - 1;

                // Las del medio
                else {
                    adyacencias[i][0] = i + 1; //El de la abajo
                    adyacencias[i][1] = i - 1; //El de la arriba
                }
            }
        }  
    }
    
    else{
        for (int i = 0; i < cantFilas; i++) {
            for (int j = 0; j < cantColumnas; j++) {

                // Caso primera fila
                if (i == 0) {
                    
                    // Primera columna (esquina superior izquierda)
                    if (j == 0) {
                        adyacencias[i * largoFila + j][0] = j + 1; // El de la derecha
                        adyacencias[i * largoFila + j][1] = largoFila + i * largoFila + j; // El de abajo
                    }

                    // Ultima columna (esquina superior derecha)
                    else if (j == cantColumnas - 1) {
                        adyacencias[i * largoFila + j][0] = j - 1; // El de la izquierda
                        adyacencias[i * largoFila + j][1] = largoFila + i * largoFila + j; // El de abajo
                    }

                    // Columnas del medio
                    else {
                        adyacencias[i * largoFila + j][0] = j + 1; // El de la derecha
                        adyacencias[i * largoFila + j][1] = j - 1; // El de la izquierda
                        adyacencias[i * largoFila + j][2] = largoFila + i * largoFila + j; // El de abajo
                    }
                }

                // Caso ultima fila
                else if (i == cantFilas - 1) {

                    // Primera columna (esquina inferior izquierda)
                    if (j == 0) {
                        adyacencias[i * largoFila + j][0] = i * largoFila + j + 1; // El de la derecha
                        adyacencias[i * largoFila + j][1] =  i * largoFila + j - largoFila; // El de arriba
                    }

                    // Ultima columna (esquina inferior derecha)
                    else if (j == cantColumnas - 1) {
                        adyacencias[i * largoFila + j][0] = i * largoFila + j - 1; // El de la izquierda
                        adyacencias[i * largoFila + j][1] =  i * largoFila + j - largoFila; // El de arriba
                    }

                    // Columnas del medio
                    else {
                        adyacencias[i * largoFila + j][0] = i * largoFila + j + 1; // El de la derecha
                        adyacencias[i * largoFila + j][1] = i * largoFila + j - 1; // El de la izquierda
                        adyacencias[i * largoFila + j][2] =  i * largoFila + j - largoFila; // El de arriba
                    }
                }

                // Caso filas del medio
                else {

                    // Primera columna (borde izquierdo)
                    if (j == 0) {
                        adyacencias[i * largoFila + j][0] = i * largoFila + j + 1; // El de la derecha
                        adyacencias[i * largoFila + j][1] =  i * largoFila + j - largoFila; // El de arriba
                        adyacencias[i * largoFila + j][2] = largoFila + i * largoFila + j; // El de abajo
                    }

                    // Ultima columna (borde derecho)
                    else if (j == cantColumnas - 1) {
                        adyacencias[i * largoFila + j][0] = i * largoFila + j - 1; // El de la izquierda
                        adyacencias[i * largoFila + j][1] =  i * largoFila + j - largoFila; // El de arriba
                        adyacencias[i * largoFila + j][2] = i * largoFila + j + largoFila; // El de abajo
                    }

                    // Casillas del del medio
                    else {
                        adyacencias[i * largoFila + j][0] = i * largoFila + j + 1; // El de la derecha
                        adyacencias[i * largoFila + j][1] = i * largoFila + j - 1; // El de la izquierda
                        adyacencias[i * largoFila + j][2] =  i * largoFila + j - largoFila; // El de arriba
                        adyacencias[i * largoFila + j][3] = largoFila + i * largoFila + j; // El de abajo
                    }
                }
            }
        }
    }
}

int main() {

    int cantTests;
    cin >> cantTests;
    for (int i = 0; i < cantTests; i++) {

        // Recibir los valores del test case
        cin >> cantFilas;
        cin >> cantColumnas;

        mapa = vector<vector<int>>(cantFilas, vector<int>(cantColumnas));

        visitado = vector<bool>(cantFilas * cantColumnas, false);

        for(int j = 0; j < cantFilas; j++) {
            for(int k = 0; k < cantColumnas; k++) 
                cin >> mapa[j][k];   
        }

        cin >> hospital.first;
        cin >> hospital.second;

        cin >> paciente.first;
        cin >> paciente.second;

        adyacencias = vector<vector<int>>(cantFilas * cantColumnas, vector<int>(4, -1));

        pasarAGrafo();

        nodoHospital = cantColumnas * hospital.first + hospital.second;
        nodoPaciente = cantColumnas * paciente.first + paciente.second;

        tiempoVisitado = vector<int>(cantFilas * cantColumnas, 0);

        /*
        for(int q = 0; q < cantFilas; q++) {
            for(int w = 0; w < cantColumnas; w++) {
                cout << "El nodo " << cantColumnas * q + w << " tiene vecinos: ";
                for(int u : adyacencias[cantColumnas * q + w]) {
                    cout << " " << u << " ";
                }
                cout << endl;
            }
        }
        */
       esPosible = true;

        if(nodoHospital == nodoPaciente) 
            cout << "0 0" << endl;
         
        else {

            // Call para la ida
            nodoTarget = nodoPaciente;
            bfs(nodoHospital);
            int tmp = tiempoIda;
            bool llegamosAPaciente = esPosible;

            // Reiniciamos los nodos visitados
            visitado = vector<bool>(cantFilas * cantColumnas, false);
            tiempoVisitado = vector<int>(cantFilas * cantColumnas, tiempoIda);

            // Call para la vuelta
            nodoTarget = nodoHospital;
            bfs(nodoPaciente);

            if (llegamosAPaciente && esPosible) 
                cout << tmp << " " << tiempoIda << endl;
            else
                cout << "IMPOSIBLE" << endl;

                
            /*
            for(int z = 0; z < cantFilas; z++) {
                for(int x = 0; x < cantColumnas; x++) {
                    cout << tiempoVisitado[matrizANodo(z, x)] << " ";
                }
                cout << endl;
            }
            */
        }
    }

    return 0;
}

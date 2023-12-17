#include <vector>
#include <iostream>

using namespace std;

int inf = 1e5;

void floydWarshall(vector<vector<int>>& latencias) {
    for(int k = 0; k < latencias.size(); k++) {
        for(int i = 0; i < latencias.size(); i++) {
            for(int j = 0; j < latencias.size(); j++) {

                latencias[i][j] = min(latencias[i][j], latencias[i][k] + latencias[k][j]);

            }
        }
    }
}

bool esFloydWarshall(vector<vector<int>>& latencias) {

    for(int k = 0; k < latencias.size(); k++) {
        for(int i = 0; i < latencias.size(); i++) {
            for(int j = 0; j < latencias.size(); j++) {
                // Si se cumple esta condicion, entonces hay un camino distinto con menor latencia y por lo tanto la matriz no es valida
                if (latencias[i][j] > latencias[i][k] + latencias[k][j])
                    return false;
            }
        }
    }
    // Si salimos de los 3 for sin entrar nunca al if es un camino posible, devolvemos true
    return true;
}

void recibirParametros(vector<vector<int>>& latencias){
    // Arma la matriz llenando simetricamente la parte de arriba de la diagonal de 0's con los inputs.
    for(int i = 1; i < latencias.size(); i++) {
        for(int j = 0; j < i; j++) {
            int lat;
            cin >> lat;
            latencias[i][j] = lat;
            latencias[j][i] = lat;
        }
    }
}

void reconstruirYPrintearDistancias(vector<vector<int>>& latencias) {
    // Ponemos todas las aristas posibles con los pesos de la matriz de FW.
    for(int k = 0; k < latencias.size(); k++) {
        for(int i = 0; i < latencias.size(); i++) {
            for(int j = 0; j < latencias.size(); j++) {
                // Si se cumple esta condicion, entonces hay un camino distinto con menor latencia y por lo tanto la arista no es necesaria
                if (latencias[i][j] == latencias[i][k] + latencias[k][j] && k!=i && k!=j) // nos fijamos que j sea distinto de k, e i distinto de k para no caer en distancias de un nodo a si mismo
                    latencias[i][j] = inf;
            }
        }
    }

    // Ponemos en inf todas las posiciones que no nos sirven revisar y en 1 las que si.
    for (int i = 0; i < latencias.size(); i++) {
        for (int j = 0; j < latencias.size(); j++) {
            if(latencias[i][j] == inf)
                latencias[i][j] = inf;
            else if(i != j)
                latencias[i][j] = 1;

        }
    }

    // Llamado a floyd warshall
    floydWarshall(latencias);

    // printear respuesta
    for(int i = 0; i < latencias.size(); i++) {
        for(int j = 0; j < latencias.size(); j++) {
            cout << latencias[i][j] << " ";
        }
        cout << endl;
    }

}



int main() {

    int cantTests;
    cin >> cantTests;

    for (int i = 0; i < cantTests; i++) {

        int cantPCs;
        cin >> cantPCs;
        vector<vector<int>> latencias(cantPCs, vector<int>(cantPCs, 0));
        recibirParametros(latencias);

        if(esFloydWarshall(latencias)) {
            cout << "POSIBLE" << endl;
            reconstruirYPrintearDistancias(latencias);
        }
        else
            cout << "IMPOSIBLE" << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double mod = 1e9 + 7;

long long parciales(vector<int>& tiempos, vector<int>& descontentos){
    vector<pair<float,int>> factores(tiempos.size());

    // Armar el vector de coeficientes de descontentos
    for (int i = 0; i < tiempos.size(); i++) {
        factores[i] = {descontentos[i] / tiempos[i], i};
    }

    // Ordenar el vector
    sort(factores.begin(),factores.end());

    long long res = 0;

    // Definir una variable para acumular el tiempo transcurrido en la correccion
    int tiempoAcumulado = 0;
    
    for (int i = factores.size() - 1; i >= 0; i--){
        // Obtener el indice de aquel que tiene mayor factor
        int indexActual = factores[i].second;
        // Obtener el tiempo necesario para corregir y el descontento por minuto
        int tiempoDeCorreccion = tiempos[indexActual];
        int descontento = descontentos[indexActual];

        // Aumentar el tiempo acumulado
        tiempoAcumulado += tiempoDeCorreccion;

        res += tiempoAcumulado*descontento;
        res = fmod(res,mod);
    }
    
    return res;
}


int main() {
    
    int test_cases_number;
    int n;

    cin >> test_cases_number;
    
    for(int i = 0; i < test_cases_number; i++) {
        cin >> n;

        vector<int> tiempos(n, 0);
        vector<int> descontentos(n,0);

        for(int j = 0; j < n; j++) {
            cin >> tiempos[j];
        }
        
        for(int j = 0; j < n; j++) {
            cin >> descontentos[j];
        }

        // Call a la funcion
        long long res = parciales(tiempos,descontentos);

        cout << res << endl;
    }
}
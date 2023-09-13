#include <iostream>
#include <vector>

using namespace std;

int INF = 1e9;
int cantProvesTotal = 0;

// Construye una matriz de costos en la cual cada columna representa la suma de los costos de todos los puestos respecto a la proveeduria puesta en dicha columna.
void construirMatrizCostos(vector<vector<int>>& costoRespectoAProve, vector<int>& puestos){
    for (int i = 0; i < puestos.size(); i++) {
        for (int j = 0; j < puestos.size(); j++) {
            costoRespectoAProve[i][j] = abs(puestos[i] - puestos[j]);
        }
    }
}

// Calcula la distancia efectiva de aquellos puestos que quedan entre la ultima proveeduria puesta y la que estoy poniendo ahora
int minDist(vector<vector<int>>& costoRespectoAProve, int indActual, int indUltProve, int cantProves) { 
    
    int res = 0;
    
    if(cantProves == cantProvesTotal) {
        for (int i = 0; i < indActual; i++) {
            res += costoRespectoAProve[i][indActual];
        }
    } else {
            
        // Calcular el resultado entre la prove anterior y la actual, y en caso que esta sea la ultima terminar de calcular los costos para los puestos que restan
        for (int i = indUltProve; i <= indActual; i++) {
            int costoAnterior = costoRespectoAProve[i][indUltProve];
            int costoNuevo =  costoRespectoAProve[i][indActual];
            if (costoAnterior > costoNuevo) 
                res += costoNuevo;
            else
                res += costoAnterior;
        }

        // Si es la ultima prove que tengo que poner, sumo el costo de todos los puestos que faltan para llegar al final
        if(cantProves == 1) {
            for (int i = indActual; i < costoRespectoAProve.size(); i++) {
                res += costoRespectoAProve[i][indActual];
            }
        }
    }
    return res;
}

// Hace el mismo recorrido que hizo el backtracking que construyo la matriz para determinar la posicion de los puestos.
void reconstruirVarias(vector<vector<int>>& costoRespectoAProve, vector<vector<vector<int>>>& memo, vector<int>& proves, int i, int j, int k) {

    if(k != 0) {

        int pongo = memo[i + 1][i][k - 1] + minDist(costoRespectoAProve, i, j, k);
        int noPongo = memo[i + 1][j][k];

        if(pongo <= noPongo) {
            proves.push_back(i);
            reconstruirVarias(costoRespectoAProve, memo, proves, i + 1, i, k - 1);
        } else {
            reconstruirVarias(costoRespectoAProve, memo, proves, i + 1, j, k);
        }
    }
}

int reconstruirSola(vector<vector<int>>& costoRespectoAProve, vector<int>& proves) {
    int pos = 0;
    int min = INF;
    int tmp = 0;

    for(int i = 0; i < costoRespectoAProve[0].size(); i++) {
        for(int j = 0; j < costoRespectoAProve.size(); j++) {
            tmp += costoRespectoAProve[j][i];
        }
        if(tmp < min) {
            min = tmp;
            tmp = 0;
            pos = i;
        }
    }
    proves.push_back(pos);
    return min;
}

//   Chori devuelve: "Arrancando en la posición pos, donde la última proveeduría está puesta en ultProve (0 si no existe), y la cantidad 
//  de proves restantes es cantProves, devuelve la mínima distancia necesaria para ubicar esa cantidad de proveedurías"

int chori(vector<int>& puestos, vector<vector<int>>& costoRespectoAProve, vector<vector<vector<int>>>& memo, int pos, int ultProve, int cantProves) {

    if(cantProves == 0)
        return 0;

    if(pos == puestos.size())
        return INF;

    if(memo[pos][ultProve][cantProves] == -1) { 

        int pongo = chori(puestos, costoRespectoAProve, memo, pos + 1, pos, cantProves - 1) + minDist(costoRespectoAProve, pos, ultProve, cantProves);

        int noPongo = chori(puestos, costoRespectoAProve, memo, pos + 1, ultProve, cantProves);

        memo[pos][ultProve][cantProves] = min(pongo, noPongo);
    }

    return memo[pos][ultProve][cantProves];

}

int main() {

    int test_cases_number;
    int cantPuestos;
    int cantProves;

    cin >> test_cases_number;

    for(int i = 0; i < test_cases_number; i++) {

        cin >> cantPuestos;
        cin >> cantProves;

        vector<int> puestos(cantPuestos);
        
        // Inicializar una matriz de n*n para guardar el costo de un puesto respecto a donde hay proveeduria
        vector<vector<int>> costoRespectoAProve(cantPuestos,vector<int>(cantPuestos));

        // Inicializamos memoria
        vector<vector<vector<int>>> memo(cantPuestos + 1, vector<vector<int>>(cantPuestos + 1, vector<int>(cantProves + 1, -1)));

        for(int i = 0; i < cantPuestos; i++)
            cin >> puestos[i];

        vector<int> proves = {};

        cantProvesTotal = cantProves;

        construirMatrizCostos(costoRespectoAProve, puestos);

        int res;

        if(cantProves == 1)
            res = reconstruirSola(costoRespectoAProve, proves);
        else {
            res = chori(puestos, costoRespectoAProve, memo, 0, 0, cantProves);
            reconstruirVarias(costoRespectoAProve, memo, proves, 0, 0, cantProves);
        }          

        cout << res << endl;

        for(int i = 0; i < cantProves; i++)
        cout << puestos[proves[i]] << " ";
        cout << endl;

        proves = {};
    }

    return 0;
}

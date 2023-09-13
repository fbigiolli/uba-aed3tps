#include <iostream>
#include <vector>

using namespace std;

int INF = 1e9;

int cantProvesTotal = 0;

void construirMatrizCostos(vector<vector<int>>& costoRespectoAProve, vector<int>& puestos){
    for (int i = 0; i < puestos.size(); i++) {
        for (int j = 0; j < puestos.size(); j++) {
            costoRespectoAProve[i][j] = abs(puestos[i] - puestos[j]);
        }
    }
}

int minDist(vector<vector<int>>& costoRespectoAProve, int indActual, int indUltProve, int cantProves) {

    int res = 0;
    
    // Si tenemos que poner una sola prove, hacemos la suma total
    if (cantProves == cantProvesTotal && cantProves == 1)
    {
        for (int i = 0; i < costoRespectoAProve.size(); i++)
        {
            res+= costoRespectoAProve[i][indActual];
        }
    }
    
    else
    {
        // Si estoy poniendo la primer prove ahora, pero me quedan mas para poner solo sumo desde el principio hasta esta prove
        if(cantProves == cantProvesTotal) {
            for (int i = 0; i < indActual; i++)
            {
                res+=costoRespectoAProve[i][indActual];
            }
        }
        
        else{
        // Calcular el resultado entre la prove anterior y la actual, y en caso que esta sea la ultima terminar de calcular los costos para los puestos que restan
        for (int i = indUltProve; i <= indActual; i++)
        {
                int costoAnterior = costoRespectoAProve[i][indUltProve];
                int costoNuevo =  costoRespectoAProve[i][indActual];
                if (costoAnterior > costoNuevo)
                {
                    res+=costoNuevo;
                }
                else
                {
                    res+=costoAnterior;
                }
        }

        if(cantProves == 1) {
            for (int i = indActual; i < costoRespectoAProve.size(); i++)
            {
                res += costoRespectoAProve[i][indActual];
            }
        }
        }

    }

    return res;
}

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

void reconstruirSola(vector<vector<int>>& costoRespectoAProve, vector<vector<vector<int>>>& memo, vector<int>& proves, int i, int j, int k) {
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
}

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

        int res = chori(puestos, costoRespectoAProve, memo, 0, 0, cantProves);

        if(cantProves == 1)
            reconstruirSola(costoRespectoAProve, memo, proves, 0, 0, cantProves);
        else            
            reconstruirVarias(costoRespectoAProve, memo, proves, 0, 0, cantProves);

        cout << res << endl;

        for(int i = 0; i < cantProves; i++)
            cout << puestos[proves[i]] << " ";
        cout << endl;

        proves = {};
    }

    return 0;
}

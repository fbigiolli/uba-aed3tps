#include <iostream>
#include <vector>

using namespace std;

int INF = 1e9;

/*

    Audios Facu

    Digamos que yo tengo provees para meter en los puestos. Deberíamos hacer un algoritmo que empezando en alguna posición con tal cantidad 
    de proveedurías, que pasa si la nueva que voy a poner ahora cubre una opción (puesto). Y después sumás qué pasa cuando te moves una posición y una prove menos

    El algoritmo empieza: que pasa si mi primer prove la pongo en el puesto 1 y haceme el mismo algoritmo con 1 proveeduría, que es caso base (quiso decir 1 prove menos?)

    Importante fijarse que justo el lugar donde lo haya puesto los puestos de la derecha no tengan una distancia más larga que los puestos de la izquierda

    Hacemos el mismo algoritmo pero fijandonos, que pasa si la primer proveeduría cubre 2 puestos en vez de 1? mismo algoritmo pero en vez de empezar en la posición 2
    empezas en la posición 3 con una proveeduría (otro caso base?)

    Y te moves así: estoy en tal posición, de aca puedo meter que el puesto (prove?) que voy a usar ahora mismo cubra tanta cantidad, y dame después de que yo haya puesto este
    puesto (prove?) el algoritmo este desde esa posición con una proveeduría menos 


*/


/*

    puestos = {1, 5, 15, 20}
    9
    1 15

        0    1   2    3
       ------------------
    0 |  0   4  14   19
    1 |  4   0  10   15
    2 | 14  10  0    5
    3 | 19  15  5    0



    Data Cifuentes:

    Chori devuelve: Minimo costo si estoy parado en pos, la ultima proveeduría la puse en el puesto ultProv y me queda cantProves de proveedurías 

    Nodo inicial es (1, 0, k)
    Ultimo nodo tiene la forma ( , , 0)

    Dado un estado (i, j, k)
    Pongo = (i + 1, i, k - 1)
    No pongo = (i + 1, j, k)

    El primer llamado devolvería: minima distancia si estoy parado en la posición pos = 1, la ultima proveeduría la puse en ultProv = 0 (ninguna)
    y me quedan poner cantProves = k proveedurías  

*/

void construirMatrizCostos(vector<vector<int>>& costoRespectoAProve, vector<int>& puestos){
    for (int i = 0; i < puestos.size(); i++) {
        for (int j = 0; j < puestos.size(); j++) {
            costoRespectoAProve[i][j] = abs(puestos[i] - puestos[j]);
        }
    }
}

// minDist(3, 1, 1)
/*
    puestos = {1, 5, 15, 20}
    9
    1 15

        0    1   2    3
       ------------------
    0 |  0   4  14   19
    1 |  4   0  10   15
    2 | 14  10  0    5
    3 | 19  15  5    0

*/

int minDist(vector<vector<int>>& costoRespectoAProve, int indActual, int indUltProve) {

    int res = 0;

    // Si todavia no pusimos ninguna prove, entonces solamente tenemos que sumar la columna que corresponde a la prove que estamos poniendo
    if (indUltProve == 0)
    {
        for (int i = 0; i < costoRespectoAProve.size(); i++)
        {
            res+=costoRespectoAProve[i][indActual - 1];
        }
    }
    
    else
    {    
        for (int i = indUltProve + 1; i < costoRespectoAProve.size(); i++)
        {
            int costoAnterior = costoRespectoAProve[i][indUltProve - 1];
            int costoNuevo =  costoRespectoAProve[i][indActual - 1];
            if (costoNuevo < costoAnterior) {
                res += costoNuevo;
            } else
                res += costoAnterior;
        }
    }

    return res;
}

/*
    puestos = {1, 5, 15, 20}
    9
    1 15

         0   1   2    3
       ------------------
    0 |  0   4  14   19
    1 |  4   0  10   15
    2 | 14  10  0    5
    3 | 19  15  5    0

*/

int chori(vector<int>& puestos, vector<vector<int>>& costoRespectoAProve, vector<vector<vector<int>>>& memo, int pos, int ultProve, int cantProves) {

    if(cantProves == 0)
        return 0;

    if(pos == puestos.size())
        return INF;

    if(memo[pos][ultProve][cantProves] == -1) {

        int pongo = chori(puestos, costoRespectoAProve, memo, pos + 1, pos, cantProves - 1) + minDist(costoRespectoAProve, pos, ultProve);

        int noPongo = chori(puestos, costoRespectoAProve, memo, pos + 1, ultProve, cantProves);

        memo[pos - 1][ultProve][cantProves] = min(pongo, noPongo);
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

        construirMatrizCostos(costoRespectoAProve, puestos);

        int res = chori(puestos, costoRespectoAProve, memo, 0, 0, cantProves);

        cout << res << endl;

        proves = {};
    }

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

int minPosible;
vector<int> res;

int distancia(vector<int>& puestos, vector<int>& proves) {
    
    int dist = 0;
    int maxDist = puestos[puestos.size() - 1];
    int tmp = maxDist;
    for(int i = 0; i < puestos.size(); i++) {
        for(int j = 0; j < proves.size(); j++)
            tmp = min(tmp, abs(puestos[i] - proves[j]));
        dist += tmp;
        tmp = maxDist;
    }
    return dist;
}

void chori(vector<int>& puestos, vector<int>& proves, int index) {

    // Caso base, llegamos al final de las proves
    if(index == proves.size()) {
        int dist = distancia(puestos, proves);
        if (dist < minPosible) {
            res = proves;
            minPosible = dist;
        }

    } else {
        
        // Busco la ultima posición donde haya una proveeduría, para poner la próxima una posición más adelante
        int ultPos = 0;
        for(int i = 0; i < proves.size(); i++) {
            if(proves[i] != -1)
                ultPos = proves[i];
        }
        
        // Por cada una de las posiciones disponibles entre la anterior y la posición del último puesto - cantidad de provedurías + proveduría que estamos considerando
        // (para dejar espacio para las que quedan)

        for(int i = ultPos + 1; i <= puestos[puestos.size() - 1] - (proves.size() + index); i++) {
            proves[index] = i;
            chori(puestos, proves, index + 1); 
        }
    }
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

        for(int i = 0; i < cantPuestos; i++) 
            cin >> puestos[i];
        
        vector<int> proves(cantProves, -1);

        minPosible = puestos[puestos.size() - 1];

        chori(puestos, proves, 0);

        cout << minPosible << endl;

        for(int i = 0; i < res.size(); i++) 
            cout << res[i] << " ";
        cout << endl;

    }

    return 0;
}

// {1, 2, 5}
// {0,0,0}
// ES UNA LEY PORQUE LO DIJO FACU. 
/*
3


4 2
1 5 15 20

puestos = {1, 5, 15, 20}
proves = {-1, -1}

9
1 15


*/


/*
               2*                     5*                7*                  
                                                                                       
---------------------------------------------------------------------------------------------------------------------------------------------------------
1               1                                                                              
---------------------------------------------------------------------------------------------------------------------------------------------------------
2               0                              
-------------------------------------------------------------------------------------------------------------------------------------------------------- 
3               1                             
--------------------------------------------------------------------------------------------------------------------------------------------------------  
4                                      1
--------------------------------------------------------------------------------------------------------------------------------------------------------
5                                      0
--------------------------------------------------------------------------------------------------------------------------------------------------------
6                                      1         
--------------------------------------------------------------------------------------------------------------------------------------------------------
7                                                       0
--------------------------------------------------------------------------------------------------------------------------------------------------------
8                                                       1
--------------------------------------------------------------------------------------------------------------------------------------------------------




*/

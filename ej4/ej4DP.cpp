#include <iostream>
#include <vector>


using namespace std;

int minPosible = 1e9;
vector<int> res;

/*
puestos = {1, 5, 15, 20}
proves = {-1, -1}



 2 proovedurias.
puestos = 1 5 15 20

-----------------------------------------------------
 PROVES=       0     |     1    |   2     |    3    |
---------------------|----------|---------|---------|-------------------------------------------------------------------------------------------------------
Puesto 0|0     0     |     4    |   14    |    19   |
---------------------|----------|---------|---------|-------------------------------------------------------------------------------------------------------
Puesto 1|1     4     |     0    |   10    |    15   |
---------------------|----------|---------|---------|-------------------------------------------------------------------------------------------------------
Puesto 2|2     14    |     10   |    0    |     5   |
---------------------|----------|---------|---------|-------------------------------------------------------------------------------------------------------
Puesto 3|3     19    |     15   |    5    |     0   |
---------------------|----------|---------|---------|-------------------------------------------------------------------------------------------------------
*/




void printMatriz(vector<vector<int>>& matriz) {
    cout << "   ";
    for(int k = 0; k < matriz.size(); k++)
        cout << " " << k;
    cout << endl;

    cout << "   ";
    for(int k = 0; k < matriz.size(); k++)
        cout << "--";
    cout << endl;

    for(int i = 0; i < matriz.size(); i++) {
        cout << i << " | ";
        for(int j = 0; j < matriz.size(); j++)
            cout << matriz[i][j] << " ";
        cout << endl;
    }
}


void construirMatriz(vector<vector<int>>& costoRespectoAProve, vector<int>& puestos){
    for (int i = 0; i < puestos.size(); i++) 
    {
        for (int j = 0; j < puestos.size(); j++)
        {
            costoRespectoAProve[i][j] = abs(puestos[i] - puestos[j]);
        }
    }
}

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


ultProve = 1
m[ultProve + 1][ultProve] , m[ultProve + 1][index] = 10 , 5 = 5
CostoActual = 4 + 10 + 15 =
Costo nuevo = 4 + 5 + 0 =

Ejemplo 1
Tenemos los puestos = {1, 5, 15, 20, 23}
Y tenemos para poner k = 3 proveedurías

Formamos 3 grupos de tamaño n/k (y lo que quede)

Quedan {1, 5}, {15, 20}, {23}

Empezamos a recorrer los extremos de grupos consecutivos y miramos sus limites

Entre {1, 5} y {15, 20}, vemos que la distancia entre 1 y 5 es menor a la distancia
entre 5 y 15, así que no lo modificamos

Entre {15, 20} y {23}, vemos que la distancia entre 15 y 20 es mayor a la distancia
entre 20 y 23, así que sí lo cambiamos

Los grupos quedan entonces {1, 5}, {15}, {20, 23}

Queda simplemente poner una proveeduría en cada grupo

En la primera y última, como son solo 2 puestos, la mejor proveeduría va a ir 
en el puesto de la izquierda (para respetar que la mejor solucion sea con orden lexicografico, ya que
al fijarnos en un grupo, mover a la derecha una proveeduria no afecta el costo relativo a ese grupo, y empeora
el orden lexicografico)

En el grupo del medio, hay una sola posición disponible

Luego, las proveedurías quedan en las posiciones {1, 15, 20}, y la distancia es 7


Ejemplo 2
Tenemos los puestos = {1, 3, 7, 11, 15, 20, 22}
Y tenemos para poner k = 3

Nos quedan entonces 3 grupos de n/k (y lo que nos queda lo enchufamos)

Quedan {1, 3}, {7, 11}, {15, 20, 22}

Empezamos a mirar los límites

La distancia entre 3 y 1 es menor a la distancia entre 7 y 11. No hacemos nada

La distancia entre 11 y 7 es igual a la distancia entre 11 y 15. 
Viendo lo que nos devuelve el algoritmo de BT y asumiendo que esta manera es correcta,
creemos que tiene que cambiar y pasarse al grupo de la izquierda

Los grupos quedan {1, 3}, {7, 11, 15}, {20, 22}

Volvemos a mirar los límites entre 15 y 20, vemos que no hace falta hacer más nada

Ponemos una proveeduría adentro de cada grupo. Si tiene cantidad de elementos par,
en la del "medio" a la izquierda. Si tiene cantidad de elementos impar, al medio.

Quedan entonces las proveedurías en las posiciones {1, 11, 20}, y distancia 12







*/
//{0,1} ... {0,2} ... {0,3} ... {1,2} ... {1,3} ... {2,3} ...
void calcular(vector<vector<int>>& costoRespectoAProve, vector<int>& proves, vector<int>& puestos, int index, int cantProvesRestantes, int costoActual){

    // Caso base
    if (cantProvesRestantes == 0 || index > puestos.size() - 1) {
        // Si el costo actual es menor al minimo anterior, actualizamos
        if (minPosible > costoActual && cantProvesRestantes == 0) {
            minPosible = costoActual;
            res = proves;
        }
        return;
    }

    // Si ya no es posible llegar a una solucion que ponga todas las proveedurias
    if (cantProvesRestantes > puestos.size() - index)
        return;

    // Actualizar el costo con la nueva prove que agregamos
    // Si todavia no agregamos ninguna prove, ponemos la primera y calculamos los costos respecto a esa prove
    int costoNoActualizado = costoActual;
    if (proves.size() == 0) {
        proves.push_back(index);
        for (int i = 0; i < puestos.size(); i++) {
            costoActual += costoRespectoAProve[i][index];
        }
        calcular(costoRespectoAProve, proves, puestos, index + 1, cantProvesRestantes - 1, costoActual);
        proves.pop_back();
        costoActual = costoNoActualizado;
    }

    // Si no, agregamos otra y comparamos los valores
    else {
        int ultimaProve = proves[proves.size() - 1];
        for (int i = ultimaProve + 1; i < puestos.size(); i++)
        {
            int costoAnterior = costoRespectoAProve[i][ultimaProve];
            int costoNuevo =  costoRespectoAProve[i][index];
            if (costoNuevo < costoAnterior) {
                costoActual = costoActual + costoNuevo - costoAnterior;
            }
        }

        // Llamado recursivo agregando prove en esta posicion
        proves.push_back(index);
        calcular(costoRespectoAProve, proves, puestos, index + 1, cantProvesRestantes - 1, costoActual);
        proves.pop_back();
        costoActual = costoNoActualizado;
    }

    // Llamado recursivo sin agregar prove en esta posicion
    calcular(costoRespectoAProve, proves, puestos, index + 1, cantProvesRestantes, costoActual);
}

void chori(vector<vector<int>>& costoRespectoAProve, vector<int>& puestos, vector<int>& proves, int cantProvesRestantes){

    construirMatriz(costoRespectoAProve, puestos);

    // printMatriz(costoRespectoAProve);

    calcular(costoRespectoAProve, proves, puestos, 0, cantProvesRestantes, 0);

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

        vector<int> proves = {};

        // Inicializar una matriz de n*n para guardar el costo de un puesto respecto a donde hay proveeduria
        vector<vector<int>> costoRespectoAProve(cantPuestos,vector<int>(cantPuestos));

        chori(costoRespectoAProve, puestos, proves, cantProves);

        cout << minPosible << endl;

        for(int i = 0; i < res.size(); i++)
            cout << puestos[res[i]] << " ";
        cout << endl;

        minPosible = 1e9;
        proves = {};
    }

    return 0;
}

// {1, 2, 5}
// {0,0,0}
// ES UNA LEY PORQUE LO DIJO FACU.
/*
3



puestos = {1, 5, 15, 20}
proves = {-1, -1}

9
1 15


    0    1   2    3
   ------------------
0 |  0   4  14   19
1 |  4   0  10   15
2 | 14  10  0    5
3 | 19  15  5    0


 2
puestos = 1 5 15 20

 PROVES=       0          1       2         3
        ---------------------------------------------------------------------------------------------------------------------------------------------------------
Puesto 1|0     0          4       14        19
        ---------------------------------------------------------------------------------------------------------------------------------------------------------
         1     4          0       10        15
        --------------------------------------------------------------------------------------------------------------------------------------------------------
         2     14         10       0         5
        --------------------------------------------------------------------------------------------------------------------------------------------------------
         3     19         15       5         0




                        80
      1         2*       95      4       5*       6       7*     15

---------------------------------------------------------------------------------------------------------------------------------------------------------
1     0          1       2
---------------------------------------------------------------------------------------------------------------------------------------------------------
2     1          0       1
--------------------------------------------------------------------------------------------------------------------------------------------------------
3     2          1       0
--------------------------------------------------------------------------------------------------------------------------------------------------------
4     3          2       1              1
--------------------------------------------------------------------------------------------------------------------------------------------------------
5     4          3       j              0
--------------------------------------------------------------------------------------------------------------------------------------------------------
6     5          4       3                1
--------------------------------------------------------------------------------------------------------------------------------------------------------
7     6          5       4                                0
--------------------------------------------------------------------------------------------------------------------------------------------------------
8     7          6       5                                1
--------------------------------------------------------------------------------------------------------------------------------------------------------
15


// */


//         // posUltimaProve es el indice del puesto sobre el que esta puesta la proveeduria
//         int posUltimaProve = proves[cantProvesPuestas - 1];
//         for (int j = posUltimaProve; j < puestos.size(); j++)
//         {
//             calcular(costoRespectoAProve,proves,puestos, ,cantProvesPuestas)
//         }


//         calcular()
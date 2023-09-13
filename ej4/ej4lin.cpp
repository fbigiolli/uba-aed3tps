#include <iostream>
#include <vector>

using namespace std;

int minPosible = 1e9;
vector<int> res;

/*

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


Ejemplo 3
Tenemos los puestos = {1, 2, 7, 100}
Y k = 2 proovedurías

Hacemos grupos de n/k elementos

Quedan {1, 2}, {7, 100}

Miramos los límites, vemos que la distancia entre 2 y 7 es menor a 7 y 100. 
Pasamos el 7 al primer grupo

Quedan {1, 2, 7}, {100}

Primer proveeduría al medio del primer grupo, segunda en el segundo grupo

Quedan las proveedurías en las posiciones {2, 100}, con distancia 6



Ejemplo 4
Puestos = {1, 2, 3, 4, 5, 7, 8, 9, 10, 10000}
k = 2 proveedurías 

2 grupos: {1,2,3,4,5} {7,8,9,10,10000}
 1 2 3 4 5 7 8 9 10 10000

{1,100,101,102}     {104,105,106,107,108}



*/

void printGrupos(vector<vector<int>>& grupos) {
    for(int i = 0; i < grupos.size(); i++) {
        for(int j = 0; j < grupos[i].size(); j++)
            cout << grupos[i][j] << " ";
        cout << endl;
    }
}


void armarGrupos(vector<int>& puestos, int cantProves, vector<vector<int>> grupos) {

    // Calculo el tamaño aproximado de cada grupo
    int tamanio = puestos.size() / cantProves;

    // Vector temporal
    vector<int> tmp = {}; 

    // Armo los grupos de ese tamaño
    for(int i = 0; i < puestos.size(); i++) {
        tmp.push_back(puestos[i]);
        if(tmp.size() >= tamanio) {
            grupos.push_back(tmp);
            tmp = {};
        }
    }

    // printGrupos(grupos);

    // Los recorro y me fijo si tengo que reorganizar
    for(int i = 0; i < grupos.size() - 1; i++) {

        int tamañoA = grupos[i].size();
        int tamañoB = grupos[i + 1].size();

        int primA = grupos[i][0];
        int primB = grupos[i + 1][tamañoB - 1];

        int ultA = grupos[i][tamañoA - 1];
        int ultB = grupos[i + 1][0];

        if(ultA - primA > ultA - ultB) {
            // Lo saco de A y lo pongo en B
            grupos[i].pop_back();
            grupos[i + 1].push_back(ultA);
        } 


    }

} 

void asignarProves(vector<int>& proves, vector<vector<int>>& grupos) {

} 


void chori(vector<int>& puestos, int cantProves, vector<int>& proves, vector<vector<int>> grupos){

    armarGrupos(puestos, cantProves, grupos);

    // printMatriz(costoRespectoAProve);

    asignarProves(proves, grupos);

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
        vector<vector<int>> grupos = {};

        chori(puestos, cantProves, proves, grupos);

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
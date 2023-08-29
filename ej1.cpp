#include <vector>
#include <limits>
#include <string>

using namespace std;

// Definir macros para que sea mas legible el codigo
#define ARRIBA 1
#define ABAJO 2
#define IZQ 3
#define DER 4

// Definir infinitos para comparar los min y max
const int INF = numeric_limits<int>::infinity();
const int NINF = -numeric_limits<int>::infinity();

// Definir variables globales
int min_road = INF;
int max_road = NINF;


bool tuki(vector<vector<string>>& mat,int i,int j,int prev,int suma_camino)
{
    // Calcular la cantidad de filas y columnas de la matriz (probablemente mejor afuera de la recursion, pero no como parametro de la funcion)
    int n = mat.size();
    int m = mat[0].size();

    // Llegue a la esquina inferior derecha
    if (i == n - 1 && j == m - 1)
    {
        // Actualizo minimos y maximos en caso de que haya mejores valores
        int largo_camino = suma_camino + 1;
        if (largo_camino > max_road)
        {
            max_road = largo_camino;
        }
        else if (largo_camino < min_road)
        {
            min_road = largo_camino;
        }
    }
    
    // Evaluar los distintos casos posibles segun donde venimos y hacer backtracking
    

}

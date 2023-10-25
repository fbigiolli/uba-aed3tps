#include <vector>
#include <list>

using namespace std;

vector<list<pair<int,int>>> armarSubfilas(vector<vector<int>>& tablero){
    vector<list<pair<int,int>>> subfilas(4);
    for (int fila = 0; fila < tablero.size(); fila++)
    {
        int inicioSubfila = -1;
        for (int col = 0; col < tablero.size(); col++)
        {
            if (tablero[fila][col] == 0 && inicioSubfila == -1 && col != tablero.size() - 1) // Buscamos el inicio de la subfila
            {
                inicioSubfila = col;
            }

            else if(tablero[fila][col] == 1 && inicioSubfila != -1){ // Encontramos el final de la subfila y no es el borde del tablero
                subfilas[fila].push_back({inicioSubfila, col - 1});
                inicioSubfila = -1;

            }

            else if(inicioSubfila == -1 && col == tablero.size() - 1 && tablero[fila][col] == 0) { // Hay una subfila de un solo casillero al borde del tablero
                subfilas[fila].push_back({col, col});
            }

            else if(inicioSubfila != -1 && col == tablero.size() - 1) // Llegamos al borde con una subfila ya iniciada (más de un casillero)
            {
                subfilas[fila].push_back({inicioSubfila, col});
            }
        }
    }
    return subfilas;
}

                                // {1,0,0,0},
                                // {0,0,1,0},
                                // {1,0,1,0},
                                // {1,0,1,1};

vector<list<pair<int,int>>> armarSubcolumnas(vector<vector<int>>& tablero){
    vector<list<pair<int,int>>> subcolumnas;
    for (int fila = 0; fila < tablero.size(); fila++)
    {
        int inicioSubcolumna = 0;
        for (int col = 0; col < tablero.size(); col++)
        {
            if (tablero[col][fila] == 1 || fila == tablero.size() - 1) 
            {
                if (inicioSubcolumna != fila)
                {
                    subcolumnas[col].push_back({inicioSubcolumna,fila - 1});
                } 
                inicioSubcolumna = fila + 1;
            }
        }
    return subcolumnas;
    }
}

int main(int argc, char const *argv[])
{
    vector<vector<int>>tablero = {{1,0,0,1},
                                {0,0,1,0},
                                {1,0,1,0},
                                {1,0,1,1}};

    armarSubcolumnas(tablero);
    armarSubfilas(tablero);
    return 0;
}

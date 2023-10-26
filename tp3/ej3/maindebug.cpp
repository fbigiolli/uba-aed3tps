#include <vector>
#include <list>
#include <tuple>

using namespace std;

void armarGrafo(vector<list<pair<int,int>>>& subfilas, vector<list<pair<int,int>>>& subcolumnas){
        
}

void armarSubfilas(vector<vector<int>>& tablero, vector<list<pair<int,int>>>& subfilas){
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
}



void armarSubcolumnas(vector<vector<int>>& tablero, vector<list<pair<int,int>>>& subcolumnas){
    for (int col = 0; col < tablero.size(); col++)
    {
        int inicioSubColumna = -1;
        for (int fila = 0; fila < tablero.size(); fila++)
        {
            if (tablero[fila][col] == 0 && inicioSubColumna == -1 && fila != tablero.size() - 1) // Buscamos el inicio de la subcolumnas
            {
                inicioSubColumna = fila;
            }

            else if(tablero[fila][col] == 1 && inicioSubColumna != -1){ // Encontramos el final de la subcolumna y no es el borde del tablero
                subcolumnas[col].push_back({inicioSubColumna, fila - 1});
                inicioSubColumna = -1;

            }

            else if(inicioSubColumna == -1 && fila == tablero.size() - 1 && tablero[fila][col] == 0) { // Hay una subcolumna de un solo casillero al borde del tablero
                subcolumnas[col].push_back({fila, fila});
            }

            else if(inicioSubColumna != -1 && fila == tablero.size() - 1) // Llegamos al borde con una subcolumna ya iniciada (más de un casillero)
            {
                subcolumnas[fila].push_back({inicioSubColumna, fila});
            }
        }
    }
}

int main(int argc, char const *argv[])
{   
    
    vector<vector<int>>tablero = {{1,0,0,1},
                                  {0,0,1,0},
                                  {1,0,1,0},
                                  {1,0,1,1}};

    int sizeTablero = tablero.size();

    vector<list<pair<int,int>>> subfilas(sizeTablero);
    vector<list<pair<int,int>>> subcolumnas(sizeTablero);

    armarSubcolumnas(tablero,subcolumnas);
    armarSubfilas(tablero,subfilas);
    
    return 0;
}

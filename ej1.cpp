#include <iostream>
#include <vector>
#include <limits>

char VISITADO = 'V';

using namespace std;

// const int INF = numeric_limits<int>::infinity();
// const int NINF = -numeric_limits<int>::infinity();

const int INF = 1e9;
const int NINF = -INF;


pair<int, int> tuki(vector<vector<char>> &maze, int i, int j, int a, int b);


pair<int, int> pasillo(vector<vector<char>> &maze, int i, int j, int a, int b) {

    maze[i][j] = VISITADO;

    // Si venimos desde la izquierda del pasillo
    if(i == a && j == b + 1) { 
        pair<int,int> derecha = tuki(maze, i, j + 1, i, j);   
        maze[i][j] = 'I';
        return {1 + derecha.first, 1 + derecha.second};
    }
    
    // Si venimos desde arriba del pasillo
    else if(i == a + 1 && j == b) {
        pair<int,int> abajo = tuki(maze, i + 1, j, i, j); 
        maze[i][j] = 'I';
        return {1 + abajo.first, 1 + abajo.second};
    }
               
    // Si venimos desde la derecha del pasillo
    else if(i == a && j == b - 1) {
        pair<int,int> izquierda = tuki(maze, i, j - 1, i, j) ;
        maze[i][j] = 'I';
        return {1 + izquierda.first, 1 + izquierda.second};
    }

    // Si venimos desde abajo del pasillo
    else if(i == a - 1 && j == b) {
        pair<int,int> arriba = tuki(maze, i - 1, j, i, j); 
        maze[i][j] = 'I';
        return {1 + arriba.first, 1 + arriba.second};
    }
}

pair<int, int> esquina(vector<vector<char>> &maze, int i, int j, int a, int b) {
    
    maze[i][j] = VISITADO;

    // Si venimos desde la izquierda de la esquina
    if(i == a && j == b + 1) {
        
        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, i + 1, j, i, j);
        
        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, i - 1, j, i, j);

        maze[i][j] = 'L';
        
        return {

            // Máximo entre el camino de abajo y el de arriba (para la primer componente)
            1 + max(abajo.first, arriba.first),

            // Mínimo entre el camino de abajo y el de arriba (para la segunda componente)
            1 + min(abajo.second, abajo.second)
        };
    }
        
    // Si venimos desde arriba de la esquina
    else if(i == a + 1 && j == b) {

        // Camino hacia la izquierda
        pair<int,int> izquierda = tuki(maze, i, j - 1, i, j);
    
        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, i, j + 1, i, j);
        
        maze[i][j] = 'L';

        return {
            // Máximo entre el camino de la izquierda y el de la derecha (para la primer componente)
            1 + max(izquierda.first, derecha.first),

            // Mínimo entre el camino de la izquierda y el de la derecha (para la segunda componente)
            1 + min(izquierda.second, derecha.second)
        };
    }
        
    // Si venimos desde la derecha de la esquina
    else if(i == a && j == b - 1) {

        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, i + 1, j, i, j);
    
        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, i - 1, j, i, j);

        maze[i][j] = 'L';

        return {
            // Máximo entre el camino de abajo y el de arriba (para la primer componente)
            1 + max(abajo.first, arriba.first),

            // Mínimo entre el camino de abajo y el de arriba (para la segunda componente)
            1 + min(abajo.second, arriba.second)
        };
    }
        
    // Si venimos desde abajo de la esquina
    else if(i == a - 1 && j == b) {

        // Camino hacia la izquierda
        pair<int,int> izquierda = tuki(maze, i, j - 1, i, j);
    
        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, i, j + 1, i, j);

        maze[i][j] = 'L';

        return {
            // Máximo entre el camino de la izquierda y el de la derecha (para la primer componente)
            1 + max(izquierda.first, derecha.first),

            // Mínimo entre el camino de la izquierda y el de la derecha (para la segunda componente)
            1 + min(izquierda.second, derecha.second)
        };
    }
}

pair<int, int> cruz(vector<vector<char>> &maze, int i, int j, int a, int b) {
    
    maze[i][j] = VISITADO;

    // Si venimos desde la izquierda de la cruz
    if(i == a && j == b + 1) {

        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, i - 1, j, i, j);
    
        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, i, j + 1, i, j);

        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, i + 1, j, i, j);

        maze[i][j] = '+';

        return {
            
            // Máximo entre los 3 caminos posibles (para la primer componente)
            1 + max(

                // El de arriba
                arriba.first,
                max(
                    // El de la derecha
                    derecha.first,

                    // El de abajo
                    abajo.first)
            ),

            // Mínimo entre los 3 caminos posibles (para la segunda componente)
            1 + min(
                // El de arriba
                arriba.second,

                min(
                    // El de la derecha
                    derecha.second,

                    // El de abajo
                    abajo.second)
            )
        };
    }
        
    // Si venimos desde arriba de la cruz
    else if(i == a + 1 && j == b) {

        // Camino hacia la izquierda
        pair<int,int> izquierda = tuki(maze, i, j - 1, i, j);
    
        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, i, j + 1, i, j);

        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, i + 1, j, i, j);
        
        maze[i][j] = '+';

        return {

            // Máximo entre los 3 caminos posibles (para la primer componente)
            1 + max(
                // El de la izquierda
                izquierda.first,

                max(
                    // El de la derecha
                    derecha.first,

                    // El de abajo
                    abajo.first)
            ),

            // Mínimo entre los 3 caminos posibles (para la segunda componente)
            1 + min(
                // El de la izquierda
                izquierda.second,

                min(
                    // El de la derecha
                    derecha.second,

                    // El de abajo
                    abajo.second)
            )
        };
    }
        
    // Si venimos desde la derecha de la cruz
    else if(i == a && j == b - 1) {

        // Camino hacia la izquierda
        pair<int,int> izquierda = tuki(maze, i, j - 1, i, j);
    
        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, i - 1, j, i, j);

        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, i + 1, j, i, j);
        
        maze[i][j] = '+';

        return {

            // Máximo entre los 3 caminos posibles (para la primer componente)
            1 + max(
                // El de arriba
                arriba.first,

                max(
                    // El de la izquierda
                    izquierda.first,

                    // El de abajo
                    abajo.first)
            ),

            // Mínimo entre los 3 caminos posibles (para la segunda componente)
            1 + min(
                // El de arriba
                arriba.second,

                min(
                    // El de la izquierda
                    izquierda.second,

                    // El de abajo
                    abajo.second)
            )
        };
    }
        
    // Si venimos desde abajo de la cruz
    else if(i == a - 1 && j == b) {
        
        // Camino hacia la izquierda
        pair<int,int> izquierda = tuki(maze, i, j - 1, i, j);
    
        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, i, j + 1, i, j);

        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, i - 1, j, i, j);
        
        maze[i][j] = '+';

        return {

            // Máximo entre los 3 caminos posibles (para la primer componente)
            1 + max(
                // El de arriba
                arriba.first,

                max(
                    // El de la derecha
                    derecha.first,

                    // El de la izquierda
                    izquierda.first)
            ),

            // Mínimo entre los 3 caminos posibles (para la segunda componente)
            1 + min(
                // El de arriba
                arriba.second,

                min(
                    // El de la derecha
                    derecha.second,

                    // El de la izquierda
                    izquierda.second)
            )
        };
    }
}


// (i, j) es donde estamos, (a, b) es de donde venimos
pair<int, int> tuki(vector<vector<char>> &maze, int i, int j, int a, int b) {

    // Definir los limites del maze
    int n = maze.size() - 1;
    int m = maze[0].size() - 1;

    // Si se va de rango o es una casilla vacía
    if (i < 0 || i > n || j < 0 || j > m || maze[i][j] == '#' || maze[i][j] == VISITADO)
        return {NINF, INF};

    // Si estamos en la última posición
    else if(i == n && j == m)
        return {0, 0};

    else {
        if(maze[i][j] == 'I') 
            return pasillo(maze, i, j, a, b);
        
        else if(maze[i][j] == 'L')
            return esquina(maze, i, j, a, b);
        
        else if(maze[i][j] == '+')
            return cruz(maze, i, j, a, b);
    }
}

int main() {
    
    vector<vector<char>> maze1 = {{'I', 'L', 'I'},
                                 {'#', 'I', 'L'},
                                 {'+', 'L', '+'}};

    vector<vector<char>> maze2 = {{'L', 'I', '+', 'L'},
                                  {'+', '+', 'I', 'L'},
                                  {'I', '#', '+', '#'},
                                  {'L', 'I', '+', '+'}};

    vector<vector<char>> maze3 = {{'+', '#'},
                                  {'#', 'L'}};

    // 1era solución, arrancando desde "arriba" de {0, 0}
    pair<int,int> solParc1 = tuki(maze2, 0, 0, -1, 0);
    
    // 2da solución, arrancando desde la "izquierda" de {0, 0}
    pair<int,int> solParc2 = tuki(maze2, 0, 0, 0, -1);

    pair<int,int> sol = {
        max(solParc1.first, solParc2.first),

        min(solParc1.second, solParc2.second)
    };
   
    // Se pone el rango de 120 porque por precondicion sabemos que la matriz no pasa ese numero de casillas
    if(NINF < sol.first < NINF + 120 || INF - 120 > sol.second > INF) 
        cout << "IMPOSIBLE" << endl;    
    else {
        cout << "POSIBLE" << endl;
        cout << sol.first << " " << sol.second << endl;
    }
}


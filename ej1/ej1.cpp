#include <iostream>
#include <vector>

bool VISITADO = true;

using namespace std;

const int INF = 1e9;
const int NINF = -INF;


pair<int, int> tuki(vector<vector<char>> &maze, vector<vector<bool>> &visited, int i, int j, int a, int b);


pair<int, int> pasillo(vector<vector<char>> &maze, vector<vector<bool>> &visited, int i, int j, int a, int b) {

    visited[i][j] = VISITADO;

    // Si venimos desde la izquierda del pasillo
    if(i == a && j == b + 1) {
        pair<int,int> derecha = tuki(maze, visited, i, j + 1, i, j);
        visited[i][j] = not VISITADO;
        return {1 + derecha.first, 1 + derecha.second};
    }

        // Si venimos desde arriba del pasillo
    else if(i == a + 1 && j == b) {
        pair<int,int> abajo = tuki(maze, visited, i + 1, j, i, j);
        visited[i][j] = not VISITADO;
        return {1 + abajo.first, 1 + abajo.second};
    }

        // Si venimos desde la derecha del pasillo
    else if(i == a && j == b - 1) {
        pair<int,int> izquierda = tuki(maze, visited, i, j - 1, i, j) ;
        visited[i][j] = not VISITADO;
        return {1 + izquierda.first, 1 + izquierda.second};
    }

        // Si venimos desde abajo del pasillo
    else if(i == a - 1 && j == b) {
        pair<int,int> arriba = tuki(maze, visited, i - 1, j, i, j);
        visited[i][j] = not VISITADO;
        return {1 + arriba.first, 1 + arriba.second};
    }
}

pair<int, int> esquina(vector<vector<char>> &maze, vector<vector<bool>> &visited, int i, int j, int a, int b) {

    visited[i][j] = VISITADO;

    // Si venimos desde la izquierda de la esquina
    if(i == a && j == b + 1) {

        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, visited, i + 1, j, i, j);

        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, visited, i - 1, j, i, j);

        visited[i][j] = not VISITADO;

        return {

                // Máximo entre el camino de abajo y el de arriba (para la primer componente)
                1 + max(abajo.first, arriba.first),

                // Mínimo entre el camino de abajo y el de arriba (para la segunda componente)
                1 + min(abajo.second, arriba.second)
        };
    }

        // Si venimos desde arriba de la esquina
    else if(i == a + 1 && j == b) {

        // Camino hacia la izquierda
        pair<int,int> izquierda = tuki(maze, visited, i, j - 1, i, j);

        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, visited, i, j + 1, i, j);

        visited[i][j] = not VISITADO;

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
        pair<int,int> abajo = tuki(maze, visited, i + 1, j, i, j);

        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, visited, i - 1, j, i, j);

        visited[i][j] = not VISITADO;

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
        pair<int,int> izquierda = tuki(maze, visited, i, j - 1, i, j);

        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, visited,i, j + 1, i, j);
        
        visited[i][j] = not VISITADO;

        return {
                // Máximo entre el camino de la izquierda y el de la derecha (para la primer componente)
                1 + max(izquierda.first, derecha.first),

                // Mínimo entre el camino de la izquierda y el de la derecha (para la segunda componente)
                1 + min(izquierda.second, derecha.second)
        };
    }
}

pair<int, int> cruz(vector<vector<char>> &maze,vector<vector<bool>> &visited, int i, int j, int a, int b) {

    visited[i][j] = VISITADO;

    // Si venimos desde la izquierda de la cruz
    if(i == a && j == b + 1) {

        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, visited, i - 1, j, i, j);

        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, visited, i, j + 1, i, j);

        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, visited, i + 1, j, i, j);

        visited[i][j] = not VISITADO;

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
        pair<int,int> izquierda = tuki(maze, visited, i, j - 1, i, j);

        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, visited, i, j + 1, i, j);

        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, visited, i + 1, j, i, j);

        visited[i][j] = not VISITADO;

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
        pair<int,int> izquierda = tuki(maze, visited, i, j - 1, i, j);

        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, visited, i - 1, j, i, j);

        // Camino hacia abajo
        pair<int,int> abajo = tuki(maze, visited, i + 1, j, i, j);

        visited[i][j] = not VISITADO;

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
        pair<int,int> izquierda = tuki(maze, visited, i, j - 1, i, j);

        // Camino hacia la derecha
        pair<int,int> derecha = tuki(maze, visited, i, j + 1, i, j);

        // Camino hacia arriba
        pair<int,int> arriba = tuki(maze, visited, i - 1, j, i, j);

        visited[i][j] = not VISITADO;

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
pair<int, int> tuki(vector<vector<char>> &maze,vector<vector<bool>> &visited, int i, int j, int a, int b) {

    // Definir los limites del maze
    int n = maze.size() - 1;
    int m = maze[0].size() - 1;

    // Si se va de rango o es una casilla vacía
    if (i < 0 || i > n || j < 0 || j > m || maze[i][j] == '#' || visited[i][j] == VISITADO)
        return {NINF, INF};

    // Si estamos en la última posición
    else if(i == n && j == m)
        return {0, 0};

    else {
        if(maze[i][j] == 'I')
            return pasillo(maze, visited,i, j, a, b);

        else if(maze[i][j] == 'L')
            return esquina(maze, visited,i, j, a, b);

        else if(maze[i][j] == '+')
            return cruz(maze, visited, i, j, a, b);
    }
}

int main() {
    
    int test_cases_number;
    int n;
    int m;
    vector<vector<char>> maze;

    cin >> test_cases_number;

    for(int i = 0; i < test_cases_number; i++) {
        cin >> n;
        cin >> m;

        vector<vector<bool>> visited(n,vector<bool>(m, false));
        vector<vector<char>> maze(n, vector<char>(m, 'a'));

        for (int j = 0; j < n; j++) {
            for(int k = 0; k < m; k++) {
                cin >> maze[j][k];
            }
        }
        
        // 1era solución, arrancando desde "arriba" de {0, 0}
        pair<int,int> solParc1 = tuki(maze, visited, 0, 0, -1, 0);
    
        // 2da solución, arrancando desde la "izquierda" de {0, 0}
        pair<int,int> solParc2 = tuki(maze, visited, 0, 0, 0, -1);

        pair<int,int> sol ;
        sol.first= max(solParc1.first, solParc2.first);
        sol.second = min(solParc1.second, solParc2.second);

        if ((NINF - 121 <= sol.first && sol.first < NINF + 121) || (INF - 121 <= sol.second && sol.second < INF + 121)) {
            cout << "IMPOSIBLE" << endl;
        }
        else {
            cout << "POSIBLE" << " " << sol.second << " " << sol.first << endl;
        }

    }

}
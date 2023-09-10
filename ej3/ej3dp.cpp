#include <iostream>
#include <vector>

using namespace std;

int balanceFinalEsperado;

// Funcion para calcular el size que va a requerir la matriz.
int sumaElementos(vector<int>& s) {
    int suma = 0;
    for(int i = 0; i < s.size(); i++) {
        suma += s[i];
    }
    return suma;
}

/*                            
            0 0 1 0 0 0 1 0 0 
            0 1 0 1 0 1 0 1 0  
            1 0 1 0 1 0 1 0 1
*/

bool sePuede(vector<int>& libro, vector<vector<bool>>& m, vector<char>& signos, int index, int balanceActual) {

    // "Cortafuegos" para no salir de rango de la matriz
    if (balanceActual > m[0].size() - 1 || balanceActual < 0){
        return false;
    }
    
    // Caso base, llegamos al final de la matriz, o sea, recorrimos todo el libro
    if(index == m.size() - 1) {
        return balanceActual == balanceFinalEsperado && m[index][balanceActual];
    } else if(m[index][balanceActual]) {

        bool suma = sePuede(libro, m, index + 1, balanceActual + libro[index + 1]);

        bool resta = sePuede(libro, m, index + 1, balanceActual - libro[index + 1]);

        return suma || resta;

    }
    return false;
}

void afip(vector<int>& libro, vector<char>& signos, int index, int balanceFinal) {
    // Caso base
    if (index == libro.size()) {
        if (balanceFinal == 0) {
            for(char c : signos){
                cout << c;
            }
            encontrado = true;
            cout << endl;
        }
        return; 
    }

    // Recursión usando el signo ? para el actual
    signos.push_back('?');
    afip(libro, signos, index + 1, balanceFinal);
    signos.pop_back();
    
    if (!encontrado) {
        // Recursión usando el signo + para el actual
        signos.push_back('+');
        afip(libro, signos, index + 1, balanceFinal - libro[index]);
        signos.pop_back();

        // Recursión usando el signo - para el actual
        signos.push_back('-');
        afip(libro, signos, index + 1, balanceFinal + libro[index]);
        signos.pop_back();

    }
}



void afip(vector<int>& libro, vector<char>& signos, vector<vector<bool>>& m, int index, int balanceFinal) {
    
    // Calcular el offset para encontrar la posicion en la que nuestro balance es 0
    int offset =  m[0].size()/2;
    
    // Setear las dos primeras posibilidades
    m[0][offset + libro[0]] = true;
    m[0][offset - libro[0]] = true;

    // Construir la matriz con todos los posibles caminos
    for (int i = 1; i < libro.size(); i++)
        {
            for (int j = 0; j < m[0].size() ; j++)
            {
                bool valorIzquierda = false;
                bool valorDerecha = false; 
                if (j - libro[i] >= 0)
                {
                    valorIzquierda = m[i - 1][j - libro[i]];
                }

                if (j + libro[i] < offset * 2)
                {
                    valorDerecha = m[i - 1][j + libro[i]];
                }
                
                m[i][j] = m[i][j] || valorDerecha || valorIzquierda ;
            }
        }

        // Print para testear la matriz
        for(int i = 0; i < m.size(); i++) {
            for(int j = 0; j < m[0].size(); j++) {
                cout << m[i][j] << " ";
            }
        cout << endl;
        }

    
        // Calcular para la primer posicion si existe un camino posible

        bool suma = sePuede(libro, m, 0,  libro[0] + offset);
        bool resta = sePuede(libro, m, 0, - libro[0] + offset);

        int balanceAcumuladoSuma = 0;
        int balanceAcumuladoResta = 0;

        if(suma && resta)
            signos[0] = '?';

        else if(suma)
            signos[0] = '+';

        else
            signos[0] = '-';

        bool sumaSuma;
        bool sumaResta;
        bool restaSuma;
        bool restaResta;

        for(int i = 1; i < libro.size(); i++) {

            if (suma)
            {
                balanceAcumuladoSuma += libro[i-1];

                bool sumaSuma = sePuede(libro, m, i, balanceAcumuladoSuma + libro[i] + offset);

                bool sumaResta = sePuede(libro, m, i, balanceAcumuladoSuma - libro[i] + offset);
            }

            if (resta)
            {
                balanceAcumuladoResta -= libro[i - 1];

                bool restaSuma = sePuede(libro, m, i, balanceAcumuladoResta + libro[i] + offset);

                bool restaResta = sePuede(libro, m, i, balanceAcumuladoResta - libro[i] + offset);

            }
            
            suma = sumaSuma || sumaResta;
            resta = restaSuma || restaResta;
/*                            
            0 0 1 0 0 0 1 0 0 
            0 1 0 1 0 1 0 1 0  
            1 0 1 0 1 0 1 0 1
*/

            if(suma && resta)
                signos[i] = '?';

            else if(suma)
                signos[i] = '+';

            else
                signos[i] = '-';

        }

}

int main() {
    
    int test_cases_number;
    int n;
    int balanceFinal;

    cin >> test_cases_number;
    
    for(int i = 0; i < test_cases_number; i++) {
        cin >> n;
        cin >> balanceFinal;
        balanceFinal = balanceFinal / 100;
                
        vector<int> libro(n);
        vector<char> signos(n);
        
        for (int i = 0; i < n; i++) {
            cin >> libro[i];
            libro[i] = libro[i] / 100;
        }

        int sizeMatriz = sumaElementos(libro);
        
        vector<vector<bool>> m(n, vector<bool>(2 * sizeMatriz + 1, false));

        int offset =  m[0].size()/2;

        balanceFinalEsperado = balanceFinal + offset;
        
        afip(libro, signos, m, 0, balanceFinal);


        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << signos[i];
        }

        cout << endl;

    }
    return 0;
}
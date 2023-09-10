#include <iostream>
#include <vector>

using namespace std;

int balanceFinalEsperado;
vector<char> res = {};

// Funcion para calcular el size que va a requerir la matriz.
int sumaElementos(vector<int>& s) {
    int suma = 0;
    for(int i = 0; i < s.size(); i++) {
        suma += s[i];
    }
    return suma;
}

void resolver(vector<int>& libro, vector<char>& signos, vector<vector<int>>& m) {

    int offset = m[0].size() / 2;       int cont2;
    bool primer2Resta = false; bool primer2Suma = false; bool segundo2Resta = false; bool segundo2Suma = false;

    for(int i = m.size() - 1; i > 0; i--) {

        cont2 = 0;
        for(int j = 0; j < m[0].size(); j++) {

            if(m[i][j] == 2) {
                cont2++;
                if(cont2 == 1) {

                    primer2Resta = (j - libro[i] >= 0) ? (m[i - 1][j - libro[i]] == 2) : false;
                    primer2Suma =  (j + libro[i] < m[0].size()) ? (m[i - 1][j + libro[i]] == 2) : false;

                } else if(cont2 == 2) {

                    segundo2Resta = (j - libro[i] >= 0) ? (m[i - 1][j - libro[i]] == 2) : false;
                    segundo2Suma =  (j + libro[i] < m[0].size()) ? (m[i - 1][j + libro[i]] == 2) : false;

                }
            }
        }

        if((primer2Suma && segundo2Resta) || (primer2Resta && primer2Suma))
            signos[i] = '?';

        else if(primer2Suma && segundo2Suma)
            signos[i] = '-';

        else if(primer2Resta && segundo2Resta)
            signos[i] = '+';

        else if(primer2Suma)
            signos[i] = '-';

        else if(primer2Resta)
            signos[i] = '+';
    }

    cont2 = 0;       int tmp;
    for(int j = 0; j < m[0].size(); j++) {
        if(m[0][j] == 2) {
            tmp = j;
            cont2++;
        }
    }

    if(cont2 == 1) {
        if(tmp > offset)
            signos[0] = '+';
        else
            signos[0] = '-';

    } else if(cont2 == 2)
        signos[0] = '?';
}


// 4 400
// 500 700 100 700 
// + ? - ?
// balance = 5
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
// 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 2 0 0 0 1 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 
// 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 2 0 1 0 1 0 1 0 0 0 0 0 0 0 2 0 1 0 0 0 0 0 0 0 
// 1 0 1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0 2 0 1 0 1 0 1 0 0 0 0 0 0 0 1 0 1 

// para cada 2 en una fila
// me voy a la de arriba
// busco los 2 que hay
// desde los 2 que hay tengo que poder llegar sumando y restando para poner signo de pregunta, si no pongo el que corresponde

// 4 400
// 500 700 700 100 
// + ? ? -
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
// 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 2 0 0 0 1 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 
// 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 2 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 
// 1 0 1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0 2 0 1 0 1 0 1 0 0 0 0 0 0 0 1 0 1

void interseccion(vector<int>& libro, vector<vector<int>>& m, int index, int balanceActual) {

    if(index >= 0 && balanceActual >= 0 && balanceActual < m[0].size() && m[index][balanceActual]) {
        m[index][balanceActual] = 2;
        interseccion(libro, m, index - 1, balanceActual - libro[index]);
        interseccion(libro, m, index - 1, balanceActual + libro[index]);
    }

}

void construir(vector<int>& libro, vector<vector<int>>& m, int index, int balanceActual){

    if((index < libro.size()) && (balanceActual >= 0) && (balanceActual < m[0].size())){
        m[index][balanceActual] = 1;
        construir(libro, m, index + 1, balanceActual - libro[index + 1]);
        construir(libro, m, index + 1, balanceActual + libro[index + 1]);
    }
}

void afip(vector<int>& libro, vector<char>& signos, vector<vector<int>>& m, int index, int balanceFinal) {

    // Calcular el offset para encontrar la posicion en la que nuestro balance es 0
    int offset =  m[0].size()/2;

    // Construir la matriz con todos los posibles caminos
    construir(libro, m, 0, offset + libro[0]);
    construir(libro, m, 0, offset - libro[0]);

    // Calcular interseccion
    interseccion(libro, m, m.size() - 1, balanceFinal + offset);

    // Dar el resultado
    resolver(libro, signos, m);

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

        vector<vector<int>> m(n, vector<int>(2 * sizeMatriz + 1, false));

        int offset =  m[0].size()/2;

        balanceFinalEsperado = balanceFinal + offset;

        afip(libro, signos, m, 0, balanceFinal);

        for (int i = 0; i < n; i++) {
            cout << signos[i];
        }

        cout << endl;

    }
    return 0;
}
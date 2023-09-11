#include <iostream>
#include <vector>

using namespace std;

int balanceTotalEsperado;

// Funcion para calcular el size que va a requerir la matriz.
int sumaElementos(vector<int>& s) {
    int suma = 0;
    for(int i = 0; i < s.size(); i++) {
        suma += s[i];
    }
    return suma;
}

void interseccion(vector<int>& libro, vector<vector<int>>& m, int index, int balanceActual,vector<char>& signos,int indicead,int balanceAnterior,vector<int>& filas) {

    if(index >= 0 && balanceActual >= 0 && balanceActual < m[0].size() && m[index][balanceActual]) {
        m[index][balanceActual] = 2;
        filas[index]++;
        if (indicead < m.size()){

            bool primer2Resta = false;
            bool primer2Suma = false;
            bool segundo2Resta = false;
            bool segundo2Suma = false;

            if (m[indicead][balanceAnterior] == 2) {
                if (filas[indicead] == 1) {

                    primer2Resta = (balanceAnterior - libro[indicead] >= 0) && (m[index][balanceAnterior - libro[indicead]] == 2);
                    primer2Suma = (balanceAnterior + libro[indicead] < m[0].size()) && (m[index][balanceAnterior + libro[indicead]] == 2);

                } else if (filas[indicead] == 2) {

                    segundo2Resta = (balanceAnterior - libro[indicead] >= 0) && (m[index][balanceAnterior - libro[indicead]] == 2);
                    segundo2Suma = (balanceAnterior + libro[indicead] < m[0].size()) && (m[index][balanceAnterior + libro[indicead]] == 2);

                }
            }

            if ((primer2Suma && segundo2Resta) || (primer2Resta && primer2Suma))
                signos[indicead] = '?';

            else if (primer2Suma && segundo2Suma)
                signos[indicead] = '-';

            else if (primer2Resta && segundo2Resta)
                signos[indicead] = '+';

            else if (primer2Suma)
                signos[indicead] = '-';

            else if (primer2Resta)
                signos[indicead] = '+';

        }
        interseccion(libro, m, index - 1, balanceActual - libro[index],signos,indicead - 1,balanceActual,filas);
        interseccion(libro, m, index - 1, balanceActual + libro[index],signos,indicead - 1,balanceActual,filas);
    }
    return;

}

void construir(vector<int>& libro, vector<vector<int>>& m, int index, int balanceActual){
    // 0 .
    // maximoPos =700.
    // 500 y -500
    // balanceTotalEsperado = -200

    // 500 - 700 >= -200 entonces false  o 500 + 700 <= -200 entonces false
    // -500 - 700 >= -200 entonces false o -500 + 700 <= -200 entonces false

    // balanceActual - maximoPos >= balanceTotalEsperado && balance

    int maximoPosible =0 ;
    int offset = m[0].size()/2;
    bool esPosibleLlegar = true;
    for (int i = index + 1; i < libro.size(); i++)
    {
        maximoPosible += libro[i];
    }

    if (balanceActual - maximoPosible - offset > balanceTotalEsperado || balanceActual  + maximoPosible - offset < balanceTotalEsperado )
    {
        esPosibleLlegar = false;
    }

    if(esPosibleLlegar && (index < libro.size()) && (balanceActual >= 0) && (balanceActual < m[0].size())){
        m[index][balanceActual] = 1;
        construir(libro, m, index + 1, balanceActual - libro[index + 1]);
        construir(libro, m, index + 1, balanceActual + libro[index + 1]);
    }
    return;
}

void afip(vector<int>& libro, vector<char>& signos, vector<vector<int>>& m, int index, int balanceFinal) {

    // Calcular el offset para encontrar la posicion en la que nuestro balance es 0
    int offset =  m[0].size()/2;
    
    // Setear las dos primeras posibilidades
    m[0][offset + libro[0]] = 1;
    m[0][offset - libro[0]] = 1;

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
                
                m[i][j] = m[i][j] || valorDerecha || valorIzquierda;
            }
        }


    // Calcular interseccion y armar vector de signos desde la ultima hasta la segunda posicion
    int indiceAd=m.size();
    int balanceAnterior = 0;
    vector<int> filas(m.size());
    interseccion(libro, m, m.size() - 1, balanceFinal + offset,signos,indiceAd,balanceAnterior,filas);

    // Definir el valor del primer signo
    if (m[0][libro[0] + offset] == 2 && m[0][-libro[0]+offset] == 2)
    {
        signos[0] = '?';
    }

    else if(m[0][libro[0]+offset] == 2)
    {
        signos[0] = '+';
    }

    else
        signos[0] = '-';
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

        vector<vector<int>> m(n, vector<int>(2 * sizeMatriz + 1, 0));

        balanceTotalEsperado = balanceFinal;

        int offset =  m[0].size()/2;

        afip(libro, signos, m, 0, balanceFinal);

        for (int i = 0; i < n; i++) {
            cout << signos[i];
        }

        cout << endl;

    }
    return 0;
}
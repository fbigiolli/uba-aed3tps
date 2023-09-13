
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<char> res = {};
int sumaElementos(vector<int>& s) {
    int suma = 0;
    for(int i = 0; i < s.size(); i++) {
        suma += s[i];
    }
    return suma;
}

void reconstruir(vector<int>& libro, vector<char>& signos, vector<vector<bool>>& m, int index, int balanceFinal) {


    int offset =  m[0].size()/2 ;

    for (int i = libro.size() - 1; i > 0; i--) {

        bool valorResta = m[i - 1][balanceFinal - libro[i] + offset];
        bool valorSuma = m[i - 1][balanceFinal + libro[i]  + offset];

            if (valorResta) {
            signos[i] = '+';
            balanceFinal-=libro[i];
        }
        else {
            signos[i] = '-';
            balanceFinal+=libro[i];
        }

    }

    if(libro[0] > 0) {
        signos[0] = '+';
    } else
        signos[0] = '-';
}

std::vector<int> eliminarRepetidosYObtenerIndices(std::vector<int> &originalVector) {
    std::vector<int> duplicateIndices;
    std::map<int, int> elementCount;

    for (int i = 0; i < originalVector.size(); ++i) {
        int element = originalVector[i];
        if (elementCount.find(element) == elementCount.end()) {
            // Este elemento no se ha encontrado antes
            elementCount[element] = i; // Guardar el índice del elemento
        } else {
            // Este elemento se ha encontrado antes
            if (elementCount[element] != -1) {
                duplicateIndices.push_back(elementCount[element]); // Guardar el índice duplicado
                elementCount[element] = -1; // Marcar como procesado
            }
            duplicateIndices.push_back(i); // Guardar el índice duplicado
        }
    }

    // Modificar el vector original con los elementos únicos
    std::vector<int> uniqueVector;
    for (int element : originalVector) {
        if (elementCount[element] != -1) {
            uniqueVector.push_back(element);
            elementCount[element] = -1; // Marcar como procesado
        }
    }

    originalVector = uniqueVector;

    return duplicateIndices;
}


void afip(vector<int>& libro, vector<char>& signos, vector<vector<bool>>& m, int index, int balanceFinal) {
    if (libro.size() == 0) {
        return;
    }
    int offset =  m[0].size()/2;

    m[0][offset + libro[0]] = true;
    m[0][offset - libro[0]] = true;

    for (int i = 1; i < libro.size(); i++)
    {
        for (int j = 0; j < m[0].size() && j + libro[i] < offset * 2; j++)

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
/*
    for(int i = 0; i < m.size(); i++) {
        for(int j = 0; j < m[0].size(); j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    */

    reconstruir(libro, signos, m, index, balanceFinal + offset);
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


        for (int i = 0; i < n; i++) {
            cin >> libro[i];
            libro[i] = libro[i] / 100;
        }
        vector<int> duplicados = eliminarRepetidosYObtenerIndices(libro);
        vector<char> signos(libro.size());

        int sizeMatriz = sumaElementos(libro);

        vector<vector<bool>> m(libro.size(), vector<bool>(2 * sizeMatriz + 1, false));

        afip(libro, signos, m, 0, balanceFinal);


        for (int j = 0; j < duplicados.size(); ++j) {
            signos.insert(signos.begin() + duplicados[j],'?');
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << signos[i];
        }


        cout << endl;
    }
    return 0;
}


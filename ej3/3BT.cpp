#include <iostream>
#include <vector>
#include <set>

using namespace std;

int sumaRestantes(vector<int>& libro, int index, int ignorarElem) {
    int suma = 0;
    for(int i = index; i < libro.size(); ++i) {
        if(i != ignorarElem)
            suma += libro[i];
    }
    return suma;
}

/*


400
    500  700  100  700 

    1             5    7
    ------------------------------------------
 +  f              t    t
    ------------------------------------------
 -  t            f    t

*/

bool sePuede(vector<int>& libro, int index, int ignorarElem, int balanceFinal) {

    // Caso base, ya consideré todos los elementos
    if(index == libro.size()) {
        if(balanceFinal == 0)
            return true;
        else
            return false;

    } else {

        int sumaRest = sumaRestantes(libro, index, ignorarElem);

        if((balanceFinal > 0 && sumaRest < balanceFinal) || (balanceFinal < 0 && -sumaRest > balanceFinal))
            return false;

        bool suma;
        bool resta;

        if (index != ignorarElem) {

            suma = sePuede(libro, index + 1, ignorarElem, balanceFinal - libro[index]);
            resta = sePuede(libro, index + 1, ignorarElem, balanceFinal + libro[index]);

        } else {

            suma = sePuede(libro, index + 1, ignorarElem, balanceFinal);
            resta = sePuede(libro, index + 1, ignorarElem, balanceFinal);

        }
        return (suma || resta);

    }
}

void afip(vector<int>& libro, vector<char>& signos, int balanceFinal) {

    int balance = balanceFinal;

    // Buscar el maximo elemento para determinar el size de la matriz
    int max = 0;
    for(int i = 0; i < libro.size(); i++) {
        if(libro[i] > max)
            max = libro[i];
    }

    // La primer fila de memo representa la suma, la segunda la resta de ese numero
    vector<vector<int>> memo (2, vector<int>(max + 1, -1));

    for(int i = 0; i < libro.size(); i++) {

            // Si en memo no tenemos precalculado el valor para la entrada del libro, la calculamos
            if(memo[0][libro[i]] == -1) {

                memo[0][libro[i]] = sePuede(libro, 0, i, balance - libro[i]);
                memo[1][libro[i]] = sePuede(libro, 0, i, balance + libro[i]);
            
            }
                
            bool suma = memo[0][libro[i]];
            bool resta = memo[1][libro[i]];
            
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
    
    for(int k = 0; k < test_cases_number; k++) {
        cin >> n;
        cin >> balanceFinal;
        balanceFinal = balanceFinal / 100;
                
        vector<int> libro(n);
        vector<char> signos(n);

        
        for (int i = 0; i < n; i++) {
            cin >> libro[i];
            libro[i] = libro[i] / 100;
        }
        
        afip(libro, signos, balanceFinal);

        for (int i = 0; i < n; i++) {
            cout << signos[i];
        }
        cout << endl;

    }

    return 0;
}

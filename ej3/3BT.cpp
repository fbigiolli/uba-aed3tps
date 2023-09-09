#include <iostream>
#include <vector>
#include <set>

using namespace std;

int sumaRestantes(vector<int>& libro, int index) {
    int suma = 0;
    for(int i = index; i < libro.size(); ++i)
        suma += libro[i];
    return suma;
}

bool sePuede(vector<int>& libro, vector<char>& signos, int balanceFinal) {
    // Caso base, ya llené todos los signos
    if(signos.size() == libro.size()) {
        if(balanceFinal == 0)
            return true;
        else
            return false;

    } else {

        // Suma de todos los elementos que todavía no tienen signo
        int sumRestantes = sumaRestantes(libro, signos.size());

        // Si no tienen posibilidad de llegar al balance restante, corto antes
        if(balanceFinal > 0 && sumRestantes < balanceFinal || balanceFinal < 0 && -sumRestantes > balanceFinal)
            return false;

        else {

            // Recursión usando el signo + para el actual
            signos.push_back('+');
            bool suma = sePuede(libro, signos, balanceFinal - libro[signos.size() - 1]);
            signos.pop_back();

            // Recursión usando el signo - para el actual
            signos.push_back('-');
            bool resta = sePuede(libro, signos, balanceFinal + libro[signos.size() - 1]);
            signos.pop_back();

            return (suma || resta);
        }
    }
}

void afip(vector<int>& libro, vector<char>& signos, int balanceFinal, set<int>& pendientes) {

    int balance = balanceFinal;

    for(int i = 0; i < libro.size(); i++) {

        // Si el valor del libro está en pendientes, lo saco, pongo un ? y aumento el balance
        if(pendientes.count(libro[i])) {
            pendientes.erase(libro[i]);
            signos.push_back('?');
            balance += libro[i];
        } else {
            signos.push_back('+');
            bool suma = sePuede(libro, signos, balance - libro[i]);
            signos.pop_back();

            signos.push_back('-');
            bool resta = sePuede(libro, signos, balance + libro[i]);
            signos.pop_back();

            // Si puedo llegar por ambos caminos, lo agrego a pendientes y disminuye el balance
            if(suma && resta) {
                signos.push_back('?');
                pendientes.insert(libro[i]);
                balance -= libro[i];
            }
            else if(suma) {
                signos.push_back('+');
                balance -= libro[i];
            } else {
                signos.push_back('-');
                balance += libro[i];
            }

        }
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
        vector<char> signos = {};
        set<int> pendientes = {};
        
        for (int i = 0; i < n; i++) {
            cin >> libro[i];
            libro[i] = libro[i] / 100;
        }
        
        afip(libro, signos, balanceFinal, pendientes);

        for (int i = 0; i < n; i++) {
            cout << signos[i];
        }
        cout << endl;

    }

    return 0;
}

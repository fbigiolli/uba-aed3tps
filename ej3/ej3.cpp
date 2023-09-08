#include <iostream>
#include <vector>

using namespace std;

bool encontrado = false;

/*
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
*/

vector<char> res = {};

bool sePuede(vector<int>& libro, vector<char>& signos, int index, int balanceFinal) {
    // Caso base
    if(index == libro.size()) {
        if(balanceFinal == 0)
            return true;
    } else {
        // Recursión usando el signo + para el actual
        signos.push_back('+');
        bool suma = sePuede(libro, signos, index + 1, balanceFinal - libro[index]);
        signos.pop_back();

        // Recursión usando el signo - para el actual
        signos.push_back('-');
        bool resta = sePuede(libro, signos, index + 1, balanceFinal + libro[index]);
        signos.pop_back();

        return suma || resta;
    }
}

void afip(vector<int>& libro, vector<char>& signos, int index, int balanceFinal) {

    int balance = balanceFinal;
    for(int i = 0; i < signos.size(); i++) {
        signos[i] = '+';
        bool suma = sePuede(libro, signos, i + 1, balance  - libro[index]);

        signos[i] = '-';
        bool resta = sePuede(libro, signos, i + 1, balance + libro[index]);

        if(suma && resta) 
            signos[i] = '?';
        else if(suma) {
            signos[i] = '+';
            balance -= libro[index];
        }
        else {
            balance += libro[index];
            signos[i] = '-';
        }
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
        
        afip(libro, signos, 0, balanceFinal);

        for (int i = 0; i < n; i++) {
            cout << signos[i];
        }
        cout << endl;
        encontrado = false;    
    }
    return 0;
}

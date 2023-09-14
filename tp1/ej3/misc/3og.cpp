#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool encontrado = false;

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

        for (int i = 0; i < n; i++) {
            cin >> libro[i];
            libro[i] = libro[i] / 100;
        }
        
        afip(libro, signos, 0, balanceFinal);

        encontrado = false;

    }

    return 0;
}

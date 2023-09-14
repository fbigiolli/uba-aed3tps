#include <iostream>
#include <vector>
#include <algorithm>    

using namespace std;

int sumaRestantes(vector<pair<int,int>>& libro, int index, int ignorarElem) {
    int suma = 0;
    for(int i = index; i < libro.size(); ++i) {
        if(i != ignorarElem)
            suma += libro[i].first;
    }
    return suma;
}

bool sePuede(vector<pair<int,int>>& libro, int index, int ignorarElem, int balanceFinal) {

    // Caso base, ya llené consideré todos los elementos
    if(index == libro.size()) {
        if(balanceFinal == 0)
            return true;
        else
            return false;

    } else {

        int sumaRest = sumaRestantes(libro, index, ignorarElem);

        if(balanceFinal > 0 && sumaRest < balanceFinal || balanceFinal < 0 && -sumaRest > balanceFinal)
            return false;

        bool suma;
        bool resta;
        if (index != ignorarElem) {

            suma = sePuede(libro, index + 1, ignorarElem, balanceFinal - libro[index].first);
            resta = sePuede(libro, index + 1, ignorarElem, balanceFinal + libro[index].first);

        } else {

            suma = sePuede(libro, index + 1, ignorarElem, balanceFinal);
            resta = sePuede(libro, index + 1, ignorarElem, balanceFinal);

        }
        return (suma || resta);

    }
}

void afip(vector<pair<int,int>>& libro, vector<pair<char,int>>& signos, int balanceFinal) {

    int balance = balanceFinal;

    for(int i = 0; i < libro.size(); i++) {

            bool suma = sePuede(libro, 0, i, balance - libro[i].first);

            bool resta = sePuede(libro, 0, i, balance + libro[i].first);

            if(suma && resta)
                signos[i] = {'?', libro[i].second};

            else if(suma)
                signos[i] = {'+', libro[i].second};

            else
                signos[i] = {'-', libro[i].second};

    }
}

bool primerCompInv(pair<int, int> a, pair<int, int> b) { return (a.first > b.first); }

bool segundaComp(pair<char, int> a, pair<char, int> b) { return (a.second < b.second); }

int main() {
    
    int test_cases_number;
    int n;
    int balanceFinal;

    cin >> test_cases_number;
    
    for(int k = 0; k < test_cases_number; k++) {
        cin >> n;
        cin >> balanceFinal;
        balanceFinal = balanceFinal / 100;
                
        vector<pair<int,int>> libro(n);
        vector<pair<char,int>> signos(n);

        
        for (int i = 0; i < n; i++) {
            cin >> libro[i].first;
            libro[i].first = libro[i].first / 100;
            libro[i].second = i;
        }
        
        sort(libro.begin(), libro.end(), primerCompInv);

        afip(libro, signos, balanceFinal);

        sort(signos.begin(), signos.end(), segundaComp);

        for (int i = 0; i < n; i++) {
            cout << signos[i].first;
        }
        cout << endl;

    }

    return 0;
}


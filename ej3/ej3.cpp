#include <iostream>
#include <vector>

using namespace std;

/*
           
500 700        -200

*/
bool afip(vector<int>& libro, vector<char>& signos, int index, int balanceFinal) {
    // Caso base
    if (index == libro.size())
    {
        if (balanceFinal == 0)
        {
            return true;
        }
        
        else
        {
            return false;
        }
        
    }
    
    // Recursion usando el signo + para el actual
    signos[index] = '+';
    afip(libro, signos, index + 1, balanceFinal - libro[index]);
    
    // Recursion usando el signo - para el actual
    signos[index] = '-';
    afip(libro, signos, index + 1, balanceFinal + libro[index]);

    // Recursion usando el signo ? para el actual
    signos[index] = '?';
    afip(libro, signos, index + 1, balanceFinal);


    return false;
}

int main() {
    
    int test_cases_number;
    int n;
    int balanceFinal;

    cin >> test_cases_number;
    
    for(int i = 0; i < test_cases_number; i++) {
        cin >> n;
        cin >> balanceFinal;
                
        vector<int> libro(n);
        vector<char> signos(n);
        
        for (int i = 0; i < n; i++) {
            cin >> libro[i];
        }
        
        afip(libro, signos, 0, balanceFinal);

        for (int i = 0; i < n; i++)
        {
            cout << signos[i] << " ";
        }
        cout << endl;
    }
}

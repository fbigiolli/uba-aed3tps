#include <iostream>
#include <vector>

using namespace std;

bool encontrado = false;

/*
           
500 700        -200

*/
bool afip(vector<int>& libro, vector<char>& signos, int index, int balanceFinal) {
    // Caso base
    if (index == libro.size())
    {
        if (balanceFinal == 0)
        {
            for(char c:signos){
                cout << c;
            }
            encontrado = true;
            cout << endl;
            return true;
        }
        
        else
        {
            return false;
        }
        
    }

    // Recursion usando el signo ? para el actual
    signos.push_back('?');
    bool pregunta=afip(libro, signos, index + 1, balanceFinal);
    signos.pop_back();
    
    if(!encontrado) {
    // Recursion usando el signo + para el actual
    signos.push_back('+');
    bool suma=afip(libro, signos, index + 1, balanceFinal - libro[index]);
    signos.pop_back();

    // Recursion usando el signo - para el actual
    signos.push_back('-');
    bool resta=afip(libro, signos, index + 1, balanceFinal + libro[index]);
    signos.pop_back();

    return false;
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
                
        vector<int> libro(n);
        vector<char> signos(n);
        
        for (int i = 0; i < n; i++) {
            cin >> libro[i];
        }
        
        bool booleano= afip(libro, signos, 0, balanceFinal);

        encontrado = false;
            
    }
}

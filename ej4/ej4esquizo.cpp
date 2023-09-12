#include <iostream>
#include <vector>


using namespace std;

int costo = 0;

vector<vector<int>> choriV(vector<int>& elementos, int k,vector<int> &proves ) {
    vector<vector<int>> grupos;
    int tamanoGrupo = elementos.size() / k; // tamano de cada grupo
    int indiceElemento = 0;

    for (int i = 0; i < k; i++) {
        vector<int> grupo;
        for (int j = 0; j < tamanoGrupo && indiceElemento < elementos.size(); j++) {
            grupo.push_back(elementos[indiceElemento]);
            indiceElemento++;
        }

        grupos.push_back(grupo);
    }

    while (indiceElemento < elementos.size()) {
        grupos[k - 1].push_back(elementos[indiceElemento]);
        indiceElemento++;
    }


    for (auto i = 0; i < grupos.size() - 1 ; i++) {
        int j = grupos[i].size() - 1;
        while (j > 0) {
            if (abs(grupos[i][j] -  grupos[i][j - 1]) > abs(grupos[i][j] -  grupos[i + 1][0]) ) {
                grupos[i + 1].insert(grupos[i + 1].begin(),grupos[i][j]);
                grupos[i].pop_back();
            }else {
                break;
            }
        }
    }

    for (auto i = grupos.size()-1; i >= 1 ; i--) {
        int j = 0;
        while (j < grupos[i].size()) {
            if (abs(grupos[i][j] - grupos[i][grupos[i].size() - 1]) > abs( grupos[i][j] - grupos[i - 1][grupos[i-1].size() - 1]) || abs(grupos[i][0] -  grupos[i][grupos[i].size() - 1]) > abs(grupos[i][0] -  grupos[i - 1][grupos[i-1].size()-1])) {
                grupos[i - 1].push_back(grupos[i][j]);
                grupos[i].erase(grupos[i].begin());
            }else {
                break;
            }
        }
    }

    for (auto i = 0; i < grupos.size(); ++i) {
        if (grupos[i].size() == 1) {
            proves.push_back(grupos[i][0]);
        } else {
            if ((grupos[i].size() % 2) == 1) {
                proves.push_back(int(grupos[i][grupos[i].size() / 2]));
            } else {
                proves.push_back(int(grupos[i][grupos[i].size() / 2 - 1]));
            }
        }
    }


    for (auto i = 0; i < grupos.size() ; ++i) {
        for (int j = 0; j < grupos[i].size(); ++j) {
            costo += abs(grupos[i][j] - proves[i]);
        }
    }

    return grupos;
}

int main() {

    int test_cases_number;
    int cantPuestos;
    int cantProves;

    cin >> test_cases_number;

    for(int i = 0; i < test_cases_number; i++) {

        cin >> cantPuestos;
        cin >> cantProves;

        vector<int> puestos(cantPuestos);

        for(int i = 0; i < cantPuestos; i++)
            cin >> puestos[i];

        vector<int> proves = {};
        choriV(puestos,cantProves,proves);

        cout << costo << endl;

        for (int i = 0; i < proves.size(); ++i) {
            cout<<proves[i]<< " ";
        }
        cout << endl;

        proves = {};
        costo = 0;
    }

    return 0;
}


#include <iostream>
#include <vector>

using namespace std;

// Funcion para calcular el size que va a requerir la matriz.
int sumaElementos(vector<int>& s) {
    int suma = 0;
    for(int i = 0; i < s.size(); i++) {
        suma += s[i];
    }
    return suma;
}

bool definirSigno(bool resta, bool suma, vector<char>& signos,int index){

    // Establecer el valor del signo que nos entra
    char signo;

    // Si tanto suma como resta son true, pongo signo de pregunta
    if (suma && resta) {
        signos[index] = '?';
        return false;
    }
    if(suma)
        signo = '-';

    if(resta)
        signo = '+';

    // Si el signo ya estaba previamente definido, o sea, no es el primer 2 de la fila
    if (signos[index] != '/') {
        // Si es el mismo signo del que veniamos seguimos con la iteracion del for
        if ((signos[index] == '+' && signo == '+') || (signos[index] == '-' && signo == '-')) {
            return true;
        }

        // Si el signo del que veniamos es distinto al que esta puesto, seteamos el signo de pregunta y cortamos la iteracion de la fila
        else if ((signos[index] == '+' && signo == '-') || (signo == '+' && signos[index] == '-')) {
            signos[index] = '?';
            return false;
        }
    }

    // Si el signo no estaba definido, lo definimos
    else {
       signos[index] = signo;
       return true;
    }   
}

void resolver(vector<int>& libro, vector<char>& signos, vector<vector<int>>& m) {
    
    int offset = m[0].size() / 2;
    
    bool resta = false;
    bool suma = false;

    // Recorrer toda la matriz de abajo hacia arriba 
    for(int i = m.size() - 1; i > 0; i--) {

        for(int j = 0; j < m[0].size(); j++) {
            
            // Si encontramos un 2 en la posicion actual
            if(m[i][j] == 2) {

                // Nos fijamos si hay un camino valido revisando las posiciones de arriba
                resta = (j - libro[i] >= 0) ? (m[i - 1][j - libro[i]] == 2) : false;
                suma =  (j + libro[i] < m[0].size()) ? (m[i - 1][j + libro[i]] == 2) : false;
                
                // Llamamos a la funcion que define el signo que corresponde y nos guardamos el bool que retorna para cortar la iteracion en caso de que ya haya un signo de pregunta.
                bool sigueIteracion = definirSigno(resta,suma,signos,i);
                if (!sigueIteracion)
                    break;
            }
        }
    }

    // Definir el primer signo dependiendo de la cantidad de 2 que encontremos en la primer fila
    int cont2 = 0;
    int tmp;
    for(int j = 0; j < m[0].size(); j++) {
        if(m[0][j] == 2) {
            tmp = j;
            cont2++;
        }
    }
            
    if(cont2 == 1) {
        if(tmp > offset)
            signos[0] = '+';
        else
            signos[0] = '-';
    } 
    
    else if(cont2 == 2) 
        signos[0] = '?';
}

void interseccion(vector<int>& libro, vector<vector<int>>& m, int index, int balanceActual) {

    if(index >= 0 && balanceActual >= 0 && balanceActual < m[0].size() && m[index][balanceActual] == 1) {
        m[index][balanceActual] = 2;

        if (index > 0) {
            if (m[index - 1][balanceActual - libro[index]] != 2) {
                interseccion(libro, m, index - 1, balanceActual - libro[index]);
            }

            if (m[index - 1][balanceActual + libro[index]] != 2) {
                interseccion(libro, m, index - 1, balanceActual + libro[index]);
            }   
        }
        
        else {
            interseccion(libro, m, index - 1, balanceActual - libro[index]);
            interseccion(libro, m, index - 1, balanceActual + libro[index]);
        }
    }
}

void construir(vector<int>& libro, vector<vector<int>>& m, int index, int balanceActual){

    int offset = m[0].size()/2;

    if((index < libro.size()) && (balanceActual >= 0) && (balanceActual < m[0].size()) && m[index][balanceActual] != 1) {
        
        m[index][balanceActual] = 1;

        if (index < libro.size() - 1) {

            if (m[index + 1][balanceActual - libro[index + 1]] != 1) {
                construir(libro, m, index + 1, balanceActual - libro[index + 1]);
            }

            if (m[index + 1][balanceActual + libro[index + 1]] != 1) {      
                construir(libro, m, index + 1, balanceActual + libro[index + 1]);
            }
        }

        else {
            construir(libro, m, index + 1, balanceActual - libro[index + 1]);
            construir(libro, m, index + 1, balanceActual + libro[index + 1]);
        }
    }
}

void afip(vector<int>& libro, vector<char>& signos, vector<vector<int>>& m, int index, int balanceFinal) {

    // Calcular el offset para encontrar la posicion en la que nuestro balance es 0
    int offset =  m[0].size()/2;

    // Construir la matriz con todos los posibles caminos
    construir(libro, m, 0, offset + libro[0]);
    construir(libro, m, 0, offset - libro[0]);

    // Calcular interseccion y armar vector de signos desde la ultima hasta la segunda posicion
    interseccion(libro, m, m.size() - 1, balanceFinal + offset);

    // Llamar a la funcion que resuelve el problema
    resolver(libro, signos, m);

    // En caso de haber encontrado ceros, poner signos de pregunta en esas posiciones
    for (int i = 0; i < libro.size(); i++) {
        if (libro[i] == 0) {
            signos[i] = '?';
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
        vector<char> signos(n, '/');

        for (int i = 0; i < n; i++) {
            cin >> libro[i];
            libro[i] = libro[i] / 100;
        }

        //Definimos el tamaño de la Matriz sumando todos sus elementos para hallar el rango
        int sizeMatriz = sumaElementos(libro);

        vector<vector<int>> m(n, vector<int>(2 * sizeMatriz + 1, 0));
        
        int offset =  m[0].size()/2;

        afip(libro, signos, m, 0, balanceFinal);

        for (int i = 0; i < n; i++) {
            cout << signos[i];  
        }

        cout << endl;

    }
    return 0;
}
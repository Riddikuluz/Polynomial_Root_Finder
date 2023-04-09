#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <math.h>

#define MAX 64
using namespace std;

//g++ main.cpp -o main
//main.exe "3x**3 + x"
//main.exe "-6x**5 + 4x**3 + 2x**1 + 7"
//main.exe "-9x**9 + 8x**8 - 7x**7 + 6x**6 + 5x**5 + 4x**4 + 3x**3 + 2x**2 + x**1 - 2"
// todo[n][0] -> coeficiente
// todo[n][1] -> grado
// todo[n][2] -> negativo

int main(int argc, char *argv[]) {
    char *token = strtok(argv[1], " ");
    char *terminos[MAX];
    int todo[MAX][3], cont = 0;

    for (int i = 0; i < MAX; i++) {//inicializa la matriz
        for (int j = 0; j < 3; j++) {
            todo[i][j] = 0;
        }
    }

    while (token != NULL) {//Obliviate
        terminos[cont] = token;
        token = strtok(NULL, " ");
        cont++;
    }
    int con = 0;//N de terminos
    for (int i = 0; i < cont; i++) {//malo
        token = strtok(terminos[i], "**");
        int d = 0;
        if (token != NULL) {
            while (token != NULL) {
                todo[con][d] = abs(atoi(token));
                if (*token == 88 || *token == 120) {
                    todo[con][0] = 1;
                    todo[con][1] = 1;
                }
                if (*token == 45) {
                    todo[con][2] = 1;
                }
                if (*token == 43 || *token == 45 && i != 0)
                    con--;
                token = strtok(NULL, "x**");
                d++;
            }
            con++;
        }
    }

    for (int i = 0; i < con; i++) {//Revisa si el coef deberia ser negativo
        if (todo[i][2])
            todo[i][0] = todo[i][0] * -1;
        cout << " " << todo[i][0] << " " << "X ^" << todo[i][1] << " "
             << endl;;//muestra el arreglo con los coefs y grados
    }

    int gra = 0;// Grado del polinomio
    for (int i = 0; i < con; i++) {
        if (gra < todo[i][1])
            gra = todo[i][1];
    }
    //cout << "Grado: " << gra << endl;

    int consta = 0;// Constante
    for (int i = 0; i < con; i++) {
        if (todo[i][1] == 0)
            consta = todo[i][0];
    }
    //cout << "Constante: " << consta << endl;

    //ruffini
    vector<int> div_consta;
    vector<int> Roots;
    if (consta != 0) {
        for (int i = 1; i <= abs(consta); i++) {
            if (abs(consta) % i == 0) {
                div_consta.push_back(i);
                div_consta.push_back(-i);
            }
        }
        for (int i = 0; i < div_consta.size(); i++){
            int aux=0;
            for (int j = 0; j < con; j++) {
                aux=aux+todo[j][0]*pow(div_consta[i], todo[j][1]);
            }
            if(aux==0)
            Roots.push_back(div_consta[i]);
        }
        for (int i = 0; i < Roots.size(); i++)
            cout << "Root: " << Roots[i] << endl;
    }
    return 0;
}
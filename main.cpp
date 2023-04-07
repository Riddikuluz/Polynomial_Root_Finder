#include <iostream>
#include <string>
#include <sstream>
#define MAX 8
using namespace std;

//g++ main.cpp -o main
//main.exe "6x**5 + 4x**3 + 2x**1"
//main.exe "-6x**5 + 4x**3 + 2x**1"
//main.exe "3x**3 + x"
//main.exe "-6x**5 + 4x**3 + 2x**1 + 7"

int main(int argc, char *argv[]) {
    string Parametro, terminos[MAX];
    int todo[MAX], neg = 0;
    for (int i = 0; i < MAX; i++) {
        todo[i] = 0;
    }

    int n = 0;
    cout << "Polinomio: " << argv[1] << endl;
    stringstream input_stringstream(argv[1]);// Convertir la cadena a un stream
    while (getline(input_stringstream, Parametro, ' ')) {
        terminos[n] = Parametro;
        //cout << "termino: " << terminos[n] << endl;
        n++;
    }

    for (int i = 0; i < MAX; i++) {// https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
        if (terminos[i][0] == 88 || terminos[i][0] == 120) {// x
            if (terminos[i].length() == 1) {
                todo[1] = 1;
            } else {
                int grad = terminos[i][terminos[i].length() - 1] - 48;
                todo[grad] = 1;
            }
        } else if (terminos[i][0] == 45 && terminos[i][1] < 58 && terminos[i][1] > 47) {// sale signo - en el primer termino
            int coef = terminos[i][1] - 48;
            int grad = terminos[i][terminos[i].length() - 1] - 48;
            todo[grad] = coef * -1;
        } else if (terminos[i][0] < 58 && terminos[i][0] > 47) {// coef entero
            if (neg) {// coef negativo
                int coef = terminos[i][0] - 48;
                int grad = terminos[i][terminos[i].length() - 1] - 48;
                todo[grad] = coef * -1;
                neg = 0;
            }
            else if(terminos[i].length() == 1) {// termino independiente
                int coef = terminos[i][0] - 48;
                todo[0] = coef;
            }else {//coef entero
                int coef = terminos[i][0] - 48;
                int grad = terminos[i][terminos[i].length() - 1] - 48;
                todo[grad] = coef;
            }

        } else if (terminos[i][0] == 45 && terminos[i].length() == 1) {// sale signo -
            neg = 1;
        }
    }
    for (int i = 0; i < MAX; i++) {
        cout << "Grado " << i << " --> Coeficientes " << todo[i] << endl;
    }
    return 0;
}
#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "FUN.h"

#define MAX 64
using namespace std;

//g++ main.cpp -o main
//main.exe "3x**3 + x"
//main.exe "-6x**5 + 4x**3 + 2x**1 + 7"
//main.exe "-9x**9 + 8x**8 - 7x**7 + 6x**6 + 5x**5 + 4x**4 + 3x**3 + 2x**2 + x**1 - 2"
//main.exe "x**3 - x**2 - 4x**1 + 4"-> x=-1,x=2,x=-2
//main.exe "2x**3 - 3x**2 - 11x**1 + 6" -> x=-2,x=1/2,x=3
//main.exe "-2x**4 + 10x**2 - 9"
//main.exe "2x**5 + x**4 - 8x**3 - x**2 + 6x"
// todo[n][0] -> coeficiente
// todo[n][1] -> grado
// todo[n][2] -> negativo

int main(int argc, char *argv[]) {

    cout  << endl<< "Polinomio: " << argv[1] << endl << endl;

    char *token = strtok(argv[1], " ");
    vector<char *> terminos;
    vector<double> div_consta, div_coef, Roots, Roots_ri, Roots_pi;
    double todo[MAX][3];


    init(todo);

    for (int i = 0; token != NULL; i++) {// agrega cada cadena separada por un espacio al array
        terminos.push_back(token);
       // cout << "Token: " << token << endl;
        token = strtok(NULL, " ");
    }

    int con = 0;//N de terminos
    for (int i = 0; i < terminos.size(); i++) {//Obliviate
        token = strtok(terminos[i], "**");
        int indice = 0;
        for (int i = 0; i < sizeof(token); i++)
            if (token[i] == 88 || token[i] == 120)
                indice = 1;

        int d = 0;
        if (token != NULL) {
            while (token != NULL) {
                todo[con][d] = abs(atoi(token));
                if (indice) {//solo x
                    if (todo[con][0] == 0) {
                        todo[con][0] = 1;
                        todo[con][1] = 1;

                    } else if (todo[con][1] == 0)
                        todo[con][1] = 1;
                }
                if (*token == 45) {//negativo
                    todo[con][2] = 1;
                }
                if (*token == 43 || *token == 45 && i > 0)// + -
                    con--;
                else if (todo[con][0] == 0 && todo[con][1] == 0)
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
        //cout << " " << todo[i][0] << " " << "X ^" << todo[i][1] << " " << endl;
    }

    int gra = 0, ind = 0;
    gra_coef(todo, &gra, &ind, con);//busca el grado y coef

    double consta = find_cons(todo, con);//busca el termino independiente

    if (consta == 0) {//factoriza polinomio
        Roots.push_back(0);
        for (int i = 0; i < con; i++) {
            todo[i][1] = todo[i][1] - 1;
            //cout << "Termino factorizado -> "<< todo[i][0] << " " << "X ^" << todo[i][1] << " " <<endl<<endl;
        }
        //cout <<endl;
        //actualiza el coef, grado y constante
        gra_coef(todo, &gra, &ind, con);
        consta = find_cons(todo, con);
    }

    //Revisa que metodo ocupar para resolver el polinomio
    if(gra==1)
        Roots.push_back(-consta / ind);
    else if (gra == 2)
        Qua_Equa(todo, con, &Roots, &Roots_ri, &Roots_pi);
    else if (consta != 0 && ind > 1) //Gauss
        Gauss(todo, gra, ind, con, consta, &Roots);
    else if (consta != 0) //ruffini
        ruffini(todo, con, consta, &Roots);

    mostrar_raices(Roots, Roots_ri, Roots_pi);

    los_mejores_guerreros_de_dios();

    return 0;
}

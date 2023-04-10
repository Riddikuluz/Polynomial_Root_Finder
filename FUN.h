
#ifndef POLYNOMIAL_ROOT_FINDER_FUN_H
#define POLYNOMIAL_ROOT_FINDER_FUN_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <math.h>
#include <algorithm>

#define MAX 64
using namespace std;

void init(double todo[][3]);

int find_cons(double todo[][3], int con);

void gra_coef(double todo[][3], int *gra, int *ind, int con);

void Gauss(double todo[][3], int gra, int ind, int con, int consta, vector<double> *Roots);

void ruffini(double todo[][3], int con, int consta, vector<double> *Roots);

void Qua_Equa(double todo[][3], int con, vector<double> *Roots, vector<double> *Roots_i);

void mostrar_raices(vector<double> Roots, vector<double> Roots_i);


void init(double  todo[][3]) {//inicializa la matriz
    for(int f=0; f<MAX; f++)
        for(int c=0; c<3; c++)
        {
                *(*(todo + c) + f)= 0;
        }
}

int find_cons(double todo[][3], int con) {//busca el termino independiente
    int consta = 0;// Constante
    for (int i = 0; i < con; i++) {
        if (todo[i][1] == 0)
            consta = todo[i][0];
    }
    cout << "Constante: " << consta << endl;
    return consta;
}

void gra_coef(double todo[][3], int *gra, int *ind, int con) {// Grado del polinomio
    for (int i = 0; i < con; i++) {
        if (*gra < todo[i][1]) {
            *gra = todo[i][1];
            *ind = todo[i][0];
        }
    }
    cout << "Grado: " << *gra << endl;
    cout << "coef: " << *ind << endl;
}

void Gauss(double todo[][3], int gra, int ind, int con, int consta, vector<double> *Roots) {// Grado del polinomio
    vector<double> div_consta, div_coef, P_roots;
    cout << "Entro GAUSS " << endl;
    for (int i = 1; i <= abs(consta); i++) {
        if (abs(consta) % i == 0) {
            div_consta.push_back(i);
            div_consta.push_back(-i);
        }
    }
    for (int i = 1; i <= gra; i++) {
        if (ind % i == 0) {
            div_coef.push_back(i);
            div_coef.push_back(-i);
        }
    }
    for (int i = 0; i < div_consta.size(); i++) {
        for (int j = 0; j < div_coef.size(); j++) {
            double key = div_consta[i] / div_coef[j];
            if (find(P_roots.begin(), P_roots.end(), key) == P_roots.end())
                P_roots.push_back(div_consta[i] / div_coef[j]);//posibles raices
        }
    }
    for (int i = 0; i < P_roots.size(); i++) {
        float aux = 0;
        for (int j = 0; j < con; j++) {
            if (j == 0) {
                aux = todo[j][0] * P_roots[i];
            } else {

                aux = aux + todo[j][0];
                aux = aux * P_roots[i];
            }
        }
        if (aux == 0)
            Roots->push_back(P_roots[i]);
    }
}

void ruffini(double todo[][3], int con, int consta, vector<double> *Roots) {// Grado del polinomio
    vector<double> div_consta, div_coef, P_roots;
    cout << "Entro Ruffini " << endl;
    for (int i = 1; i <= abs(consta); i++) {
        if (abs(consta) % i == 0) {//posibles raices
            div_consta.push_back(i);
            div_consta.push_back(-i);
        }
    }
    for (int i = 0; i < div_consta.size(); i++) {
        double aux = 0;
        for (int j = 0; j < con; j++) {
            aux = aux + todo[j][0] * pow(div_consta[i], todo[j][1]);
        }
        if (aux == 0)
            Roots->push_back(div_consta[i]);
    }
}

void Qua_Equa(double todo[][3], int con, vector<double> *Roots, vector<double> *Roots_i) {// Grado del polinomio
    double a, b, c, discriminant, realPart, imaginaryPart;
    for (int i = 0; i < con; i++) {
        if (todo[i][1] == 0)
            c = todo[i][0];
        else if (todo[i][1] == 1)
            b = todo[i][0];
        else if (todo[i][1] == 2)
            a = todo[i][0];
    }
    discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        Roots->push_back((-b + sqrt(discriminant)) / (2 * a));
        Roots->push_back((-b - sqrt(discriminant)) / (2 * a));
    } else if (discriminant == 0)
        Roots->push_back(-b / (2 * a));

    else {
        Roots->push_back(-b / (2 * a));
        Roots_i->push_back(sqrt(-discriminant) / (2 * a));
    }
}

void mostrar_raices(vector<double> Roots, vector<double> Roots_i) {// Grado del polinomio
    if (Roots.size() && Roots_i.size()) {
        for (int i = 0; i < Roots.size(); i++) {
            cout << "Las raices son complejas." << endl;
            cout << "raiz: "<< Roots[i] << " + "<< Roots_i[i]<<" i "<< endl;
            cout << "raiz: "<< Roots[i] << " - "<< Roots_i[i] <<" i "<< endl;
        }
    } else if (Roots.size())
        for (int i = 0; i < Roots.size(); i++)
            cout << "raiz: " << Roots[i] << endl;
    else
        cout << "No tiene soluciones o raices." << endl;
}

#endif //POLYNOMIAL_ROOT_FINDER_FUN_H
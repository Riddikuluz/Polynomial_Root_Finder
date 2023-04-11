
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



void init(double todo[][3]) {//inicializa la matriz
    for (int f = 0; f < MAX; f++)
        for (int c = 0; c < 3; c++) {
            *(*(todo + c) + f) = 0;
        }
}

double find_cons(double todo[][3], int con) {//busca el termino independiente
    double consta = 0;// Constante
    for (int i = 0; i < con; i++) {
        if (todo[i][1] == 0)
            consta = todo[i][0];
    }
    //cout << "Constante: " << consta << endl;
    return consta;
}

void gra_coef(double todo[][3], int *gra, int *ind, int con) {// Grado del polinomio
    *gra = 0;
    for (int i = 0; i < con; i++) {
        if (*gra < todo[i][1]) {
            *gra = todo[i][1];
            *ind = todo[i][0];
        }
    }
    //cout << "Grado: " << *gra << endl;
    //cout << "coef: " << *ind << endl;
}

void Gauss(double todo[][3], int gra, int ind, int con, int consta, vector<double> *Roots) {//metodo ruffini
    vector<double> div_consta, div_coef, P_roots;
    //cout << "Entro GAUSS " << endl;
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
        double aux = 0;
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

void ruffini(double todo[][3], int con, int consta, vector<double> *Roots) {//metodo ruffini
    vector<double> div_consta, div_coef, P_roots;
    //cout << "Entro Ruffini " << endl;
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

void Qua_Equa(double todo[][3], int con, vector<double> *Roots, vector<double> *Roots_ri,
              vector<double> *Roots_pi) {// solucion cuadratica
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
        Roots_ri->push_back(-b / (2 * a));
        Roots_pi->push_back(sqrt(-discriminant) / (2 * a));
    }
}

void mostrar_raices(vector<double> Roots, vector<double> Roots_ri, vector<double> Roots_pi) {//Muestra las raices
    if (Roots_ri.size() || Roots_pi.size() || Roots.size())
        if (Roots_ri.size() + Roots_pi.size() + Roots.size() == 1)
            cout << "Posee una raiz." << endl << endl;
        else
            cout << "Posee " << Roots_ri.size() + Roots_pi.size() + Roots.size() << " raices." << endl << endl;

    if (Roots_ri.size() && Roots_pi.size()) {
        for (int i = 0; i < Roots_ri.size(); i++) {
            cout << endl << "Posee 2 raices complejas." << endl << endl;
            cout << "raiz: " << Roots_ri[i] << " + " << Roots_pi[i] << " i " << endl << endl;
            cout << "raiz: " << Roots_ri[i] << " - " << Roots_pi[i] << " i " << endl << endl;
        }
    }
    if (Roots.size()) {
        if (Roots.size() == 1){
            cout << endl << "Posee una raiz Reales." << endl << endl;
        cout << "raiz: " << Roots[0] << endl << endl;
        }
        else {
            cout << endl << "Posee raices Reales." << endl << endl;
            for (int i = 0; i < Roots.size(); i++)
                cout << "raiz: " << Roots[i] << endl << endl;
        }
    }
    if (!Roots_ri.size() && !Roots_pi.size() && !Roots.size())
        cout << "No tiene soluciones 0 raices." << endl << endl;

}

void los_mejores_guerreros_de_dios() {
    cout << endl << endl;
    cout << "<<<Integrantes>>>" << endl << endl;
    printf("%c Romina Araya", 206);
    cout << endl << endl;
    printf("%c Brian Ponce", 206);
    cout << endl << endl;
    printf("%c Francisco Robledo", 206);
    cout << endl << endl;
    cout << "Traido a usted, gracias al fin de semana santo. " << endl << endl;
}

#endif //POLYNOMIAL_ROOT_FINDER_FUN_H

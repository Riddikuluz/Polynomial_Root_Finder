#include "FUN.h"
void init(double todo[][3]);

double find_cons(double todo[][3], int con);

void gra_coef(double todo[][3], int *gra, int *ind, int con);

void Gauss(double todo[][3], int gra, int ind, int con, int consta, vector<double> *Roots);

void ruffini(double todo[][3], int con, int consta, vector<double> *Roots);

void Qua_Equa(double todo[][3], int con, vector<double> *Roots, vector<double> *Roots_ri, vector<double> *Roots_pi);

void mostrar_raices(vector<double> Roots, vector<double> Roots_ri, vector<double> Roots_pi);

void los_mejores_guerreros_de_dios();
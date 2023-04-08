#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>

#define MAX 64
using namespace std;


//g++ main.cpp -o main
//main.exe "3x**3 + x"
//main.exe "-6x**5 + 4x**3 + 2x**1 + 7"
//main.exe "-9x**9 + 8x**8 - 7x**7 + 6x**6 + 5x**5 + 4x**4 + 3x**3 + 2x**2 + x**1 - 2"
// todo[n][0] -> coeficiente
// todo[n][1] -> grado
// todo[n][2] -> negativo
template<typename T, size_t n>
void print_array(T const(&arr)[n]) {
    for (size_t i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    char *token = strtok(argv[1], " ");
    char *terminos[MAX];
    int todo[MAX][3], cont = 0;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < 3; j++) {
            todo[i][j] = 0;
        }
    }
    while (token != NULL) {
        terminos[cont] = token;
        token = strtok(NULL, " ");
        cont++;
    }

    int con = 0;
    for (int i = 0; i < cont; i++) {//malo
        token = strtok(terminos[i], "**");
        int d = 0;
        if (token != NULL) {
            while (token != NULL) {
                todo[con][d] = abs(atoi(token));
                if (*token == 88 || *token ==120){
                    todo[con][0]=1;
                    todo[con][1]=1;
                }
                if (*token == 45 ) {
                    todo[con][2] = 1;
                }
                if (*token == 43 || *token == 45&& i != 0)
                    con--;
                token = strtok(NULL, "x**");
                d++;
            }
            con++;
        }
    }
/*Pruebas*/
    print_array(todo[0]);
    print_array(todo[1]);
    print_array(todo[2]);
    print_array(todo[3]);
    print_array(todo[4]);
    print_array(todo[5]);
    print_array(todo[6]);
    print_array(todo[7]);
    print_array(todo[8]);
    print_array(todo[9]);
    print_array(todo[10]);

    return 0;
}
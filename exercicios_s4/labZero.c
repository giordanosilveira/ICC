#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

#define TAM_COEFICIENTES 100


int main () {

    int grau;
    double raiz;
    Polinomio *p;
    string_t coeficentes = (string_t)alocarVetor(TAM_COEFICIENTES, sizeof(char));
    void (*calc_polinomio)(Polinomio, double, double, double);


    fprintf(stderr, "Entre com o grau do polinômio:\n");
    scanf("%d", &grau);

    printf("Entre com os coeficientes da equação.\n");
    printf("Entre com todos os coeficientes de uma só vez, separados por espaço.\nCaso algum dos coeficientes não esteja presente, coloque '0' no lugar:\n");

    getchar();
    fgets(coeficentes, TAM_COEFICIENTES - 2, stdin);
    p = initPolinomio(&grau, coeficentes);
    prnPolinomio(p);
    calcPolinomio_lento(*p, 1, &raiz, &raiz);
    //calc_polinomio = &calcPolinomio_rapido;
    //newtonRaphson(*p, 0, EPS, MAXIT, &raiz, calc_polinomio);




    return 0;
}


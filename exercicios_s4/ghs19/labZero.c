#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

#define TAM_COEFICIENTES 100


int main () {

    int grau, nIt;
    double raiz, x0, x1, erro, tempo;

    Polinomio *p;
    string_t coeficentes = (string_t)alocarVetor(TAM_COEFICIENTES, sizeof(char));
    void (*calc_polinomio)(Polinomio, double, double*, double*);


    fprintf(stdout, "Entre com o grau do polinômio:\n>");
    scanf("%d", &grau);

    fprintf(stdout, "Entre com os coeficientes da equação.\n");
    fprintf(stdout, "Entre com todos os coeficientes de uma só vez, separados por espaço.\nCaso algum dos coeficientes não esteja presente, coloque '0' no lugar:\n>");

    getchar();
    fgets(coeficentes, TAM_COEFICIENTES - 2, stdin);
    p = initPolinomio(&grau, coeficentes);
    prnPolinomio(p);


    fprintf(stdout, "Para o método de newton-raphson, digite um ponto inicial\n>");
    scanf("%g", &x0);

    
    fprintf(stderr, "Metodo\t\t\t n_it\t\t raiz\t\t erro\t\t tempo\n");
    calc_polinomio = &calcPolinomio_rapido;

    tempo = timestamp();
    erro = newtonRaphson(*p, x0, EPS, &nIt, &raiz, calc_polinomio);
    tempo = timestamp() - tempo;

    prnTabela("Newton Raphson rápido", nIt, raiz, erro, tempo);
    

    calc_polinomio = &calcPolinomio_lento;
    tempo = timestamp();
    erro = newtonRaphson(*p, x0, EPS, &nIt, &raiz, calc_polinomio);
    tempo = timestamp() - tempo;

    prnTabela("Método Raphson lento", nIt, raiz, erro, tempo);

    fprintf(stdout, "\n\nPara o método da Secante, digite dois pontos iniciais\n>");
    scanf("%lg %lg", &x0, &x1);
    //fprintf(stderr, "%lg %lg", x0, x1);

    fprintf(stderr, "Metodo\t\t\t n_it\t\t raiz\t\t erro\t\t tempo\n");
    
    calc_polinomio = &calcPolinomio_rapido;
    tempo = timestamp();
    erro = secante(*p, x0, x1, EPS, &nIt, &raiz, calc_polinomio);
    tempo = timestamp() - tempo;
    prnTabela("Método Secante rápido", nIt, raiz, erro, tempo);

    calc_polinomio = &calcPolinomio_lento;
    tempo = timestamp();
    erro = secante(*p, x0, x1, EPS, &nIt, &raiz, calc_polinomio);
    tempo = timestamp() - tempo;
    prnTabela("Método Secante lento", nIt, raiz, erro, tempo);

    

    return 0;
}


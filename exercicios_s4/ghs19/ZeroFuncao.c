#include <stdio.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "ZeroFuncao.h"


double calcularErro(double x, double x0) {
    return ABS((x-x0)/x0)*100;
}


double newtonRaphson (Polinomio p, double x0, double eps, int *it, double *raiz, void (*func)(Polinomio, double, double*, double*)) {

    int i = 0;
    double x, px, dpx, erro;

    //Enquanto for menor que o número de iterações.
    while (i < MAXIT) {

        // Calcula do polinomio e da derivada para um valor x0 e os coloca em px e dpx respectivamente
        func(p, x0, &px, &dpx);

        x = x0 - px/dpx;            //Proxima possível raiz

        //calcula o erro e verifica se ele é menor que o tolerável, se sim, retorna esse erro
        erro = calcularErro(x, x0); 
        if (erro < eps) {
            *it = i;
            *raiz = x;
            return erro;
        }

        x0 = x;
        ++i;        
    }

    *it = MAXIT;
    *raiz = x0;
    return erro;

}


double secante (Polinomio p, double x0, double x1, double eps, int *it, double *raiz, void (*func)(Polinomio, double, double*, double*)) {


    double x, px1, px0, dpx, erro;
    
    int i = 0;
    while (i < MAXIT) {

        //Calculo da derivada no ponto anterior e no próximo
        func(p, x0, &px0, &dpx);
        func(p, x1, &px1, &dpx);

        //Calcula da próxima raíz
        x = x1 - (px1*(x1 - x0))/(px1 - px0);

        erro = calcularErro(x, x1); 
        if (erro < eps) {
            *raiz = x;
            *it = i;
            return erro;
        }

        x0 = x1;
        x1 = x;

        ++i;
    }

    *raiz = x1;
    *it = i;
    
    return erro;

}


void calcPolinomio_rapido(Polinomio p, double x, double *px, double *dpx) {

    double soma_px = 0.0, soma_dpx = 0.0;
    for (int i = p.grau; i > 0; --i){
        soma_px = soma_px*x + p.p[i];
        soma_dpx = soma_dpx*x + soma_px; 
    }
    soma_px = soma_px*x + p.p[0];
    
    //fprintf(stderr, "Rapido, %lg %lg\n", soma_px, soma_dpx);
    *px = soma_px;
    *dpx = soma_dpx;
}


void calcPolinomio_lento(Polinomio p, double x, double *px, double *dpx) {

    double soma_px = 0.0, soma_dpx = 0.0;
    for (int i = 1; i < p.grau + 1; ++i) {
        soma_px = soma_px + p.p[i]*pow(x, i);
        soma_dpx = soma_dpx + i*p.p[i]*pow(x, i - 1);
    }
    soma_px = soma_px + p.p[0]*1;

    //fprintf(stderr, "Lento, %lg %lg\n", soma_px, soma_dpx);
    *px = soma_px;
    *dpx = soma_dpx;
}


void prnPolinomio(Polinomio *p) {

    fprintf(stderr, "Grau do polinômio\n");
    fprintf(stderr, "%d\n\n", p->grau);

    fprintf(stderr, "Coeficientes da equação:");
    prnVetor(p->p, p->grau+1);

}

Polinomio * initPolinomio(int *grau, string_t coeficientes) {

    char separador[2] = " ";
    string_t token;
    Polinomio *ptr = (Polinomio *)alocarVetor(1, sizeof(Polinomio));
    
    if (!ptr ){
        fprintf(stderr, "Não foi possível alocar espaço para o polinômio\n");
        exit(1);
    }

    ptr->p = (double *)alocarVetor((*grau) + 1, sizeof(double));
    if (! ptr->p) {
        fprintf(stderr, "Não foi possível alocar espaço para o vetor\n");
        free(ptr);
        exit(1);
    }    
    ptr->grau = *(grau);


    token = strtok(coeficientes, separador);
    int i = *grau;
    while (token != NULL && i >= 0) {
        sscanf(token, "%lg", &ptr->p[i]);
        token = strtok(NULL, separador);
        --i;
    }
    if (token != NULL) {
        fprintf(stderr, "Número de coeficientes maior que o grau do polinômio\n");
        free(ptr->p);
        free(ptr);
        exit(1);
    }

    return ptr;
}

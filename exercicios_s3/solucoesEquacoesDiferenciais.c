
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define INTERVALO_INICIAL 0
#define INTERVALO_FINAL 1
#define CONDICAO_CONTORNO_INICIAL -1
#define CONDICAO_CONTORNO_FINAL 0
#define MAX_IT 50

typedef struct {

    double *D, *DI, *DS, *B;
    int n;

} SLTridiagonal_t;

typedef struct {
    int n;                              //número de pontos internos na malha
    double a, b;                        //intervalo
    double ya, yb;                      //condições contorno
    double (*p)(double), (*q)(double), (*r)(double);
} Edo_t;


double p (double x) {
    return x + 1;
}

double q (double x) {
    return -2;
}

double r (double x) {
    return (1 - pow(x, 2))*exp(-x);
}

void inicializarEdo(Edo_t *edo, int n_pontos) {

    edo->n = n_pontos;
    edo->a = INTERVALO_INICIAL;
    edo->b = INTERVALO_FINAL;
    edo->ya = CONDICAO_CONTORNO_INICIAL;
    edo->yb = CONDICAO_CONTORNO_FINAL;

}

SLTridiagonal_t *alocarSistLin(int n) {

    SLTridiagonal_t *SL;

    SL = malloc(sizeof(SLTridiagonal_t));
    if (SL) {
        
        SL->n = n;

        SL->D = (double *)calloc(n, sizeof(SLTridiagonal_t));
        if (!SL->D) {
            fprintf(stderr, "Não foi possível alocar espaço o vetor\n");
            free(SL->D);
            exit(0);
        }

        SL->DS = (double *)calloc(n, sizeof(SLTridiagonal_t));
        if (!SL->DS) {
            fprintf(stderr, "Não foi possível alocar espaço o vetor\n");
            free(SL->DS);
            exit(0);
        }

        SL->DI = (double *)calloc(n, sizeof(SLTridiagonal_t));
        if (!SL->DI) {
            fprintf(stderr, "Não foi possível alocar espaço o vetor\n");
            free(SL->DI);
            exit(0);
        }

        SL->B = (double *)calloc(n, sizeof(SLTridiagonal_t));
        if (!SL->B) {
            fprintf(stderr, "Não foi possível alocar espaço o vetor\n");
            free(SL->B);
            exit(0);
        }

    }

    return SL;

}


void gerarTridiagonal(Edo_t *edo, SLTridiagonal_t *SL) {

    double xi, h;
    h = (edo->b - edo->a) / (edo->n+1.0);

    for (int i = 0; i < edo->n; ++i) {
        xi = edo->a + (i+1)*h;
        SL->DI[i] = 1 - h * edo->p(xi)/2.0;         //diagonal inferior
    
    }

}

int main () {

    int n_pontos[3] = {5, 10, 100};


    for (int i = 0; i < 3; ++i) {
        Edo_t edo;
        SLTridiagonal_t *SL;

        double *x = (double *)calloc(n_pontos[i], sizeof(double));

        SL = alocarSistLin(n_pontos);
        inicializarEdo(&edo, n_pontos[i]);

        gerarTridiagonal(Edo_t *edo, SLTridiagonal_t *SL);

        //gaussSeidelSimplificado();
        //gaussSeidelSemVetores();
        


    }





    return 0;
}


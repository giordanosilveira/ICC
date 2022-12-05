#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>

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


double timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (double) tp.tv_sec*1.0e3 + (double) tp.tv_nsec*1.0e-6 );
}


void inicializarEdo(Edo_t *edo, int n_pontos) {

    edo->n = n_pontos;
    edo->a = INTERVALO_INICIAL;
    edo->b = INTERVALO_FINAL;
    edo->ya = CONDICAO_CONTORNO_INICIAL;
    edo->yb = CONDICAO_CONTORNO_FINAL;
    edo->p = &p;
    edo->q = &q;
    edo->r = &r;

}


void prnVetor(double *v, unsigned int n) {

    fprintf(stderr, "\n");
    for (int i = 0; i < n; ++i)
        fprintf(stderr, "%10g ", v[i]);
    fprintf(stderr, "\n\n");

}


void liberarSisLin(SLTridiagonal_t *SL) {


    if (SL) {
        if (SL->D)
            free(SL->D);
        if (SL->DI)
            free(SL->DI);
        if (SL->DS)
            free(SL->DS);
        if(SL->B)
            free(SL->B);
        
        free(SL);
    }

}


void prnSisLin(SLTridiagonal_t *SL) {

    fprintf(stderr, "N -> %d\n", SL->n);

    fprintf(stderr, "Diagonal superior:");
    prnVetor(SL->DS, SL->n);
    
    fprintf(stderr, "Diagonal principal:");
    prnVetor(SL->D, SL->n);
    
    fprintf(stderr, "Diagonal inferior:");
    prnVetor(SL->DI, SL->n);

    fprintf(stderr, "Termos independentes:");
    prnVetor(SL->B, SL->n);

    
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
            free(SL->D);
            free(SL->DS);
            exit(0);
        }

        SL->DI = (double *)calloc(n, sizeof(SLTridiagonal_t));
        if (!SL->DI) {
            fprintf(stderr, "Não foi possível alocar espaço o vetor\n");
            free(SL->D);
            free(SL->DS);
            free(SL->DI);
            exit(0);
        }

        SL->B = (double *)calloc(n, sizeof(SLTridiagonal_t));
        if (!SL->B) {
            fprintf(stderr, "Não foi possível alocar espaço o vetor\n");
            free(SL->D);
            free(SL->DS);
            free(SL->DI);
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
        SL->DI[i] = 1 - h * edo->p(xi)/2.0; //diagonal inferior
        SL->D[i] = -2 + h*h*edo->q(xi);     //diagonal principal
        SL->DS[i] = 1 + h*edo->p(xi)/2.0;   //diagonal superior
        SL->B[i] = h*h*edo->r(xi);          //termo independente        
    }
    SL->B[0] -= edo->ya * (1 - h*edo->p(edo->a+h)/2.0);
    SL->B[edo->n-1] -= edo->yb * (1 + h*edo->p(edo->b-h)/2.0);

}


void gaussSeidelSemVetores(Edo_t *edo, double *x, double *tempo) {

    double xi, h;
    double xi_anterior;

    h = (edo->b - edo->a)/(edo->n+1.0);

    int i = 0;
    *(tempo) = timestamp();
    while (i < MAX_IT) {

        double soma = 0.0;
        xi = edo->a + (0 + 1)*h;    
        soma = (1 + h*h*edo->p(xi)/2.0)*x[1];   //DS*X[1]   
        x[0] = ((h*h*edo->r(xi) - edo->ya*(1 - h*edo->p(edo->a+h)/2.0)) - soma)/(-2 + h*h*edo->q(xi));  //(B - soma)/D

        for (int j = 1; j < edo->n-1; ++j) {
            xi = edo->a + ((j + 1)+1)*h;
            xi_anterior = edo->a + ((j - 1)+1)*h;
            soma = (1 + h*edo->p(xi)/2.0)*x[j + 1] + (1 - h*edo->p(xi_anterior)/2.0)*x[j - 1];          //DS*X[j + 1] + DI*X[j - 1]
            x[j] = ((h*h*edo->r(edo->a + (j + 1)*h)) - soma)/(-2 + h*h*edo->q(edo->a + (j + 1)*h));     //X[j] = (B[j]- soma)/D[j]
        }

        xi = edo->a + ((edo->n-2)+1)*h;         
        soma = (1 - h*edo->p(xi)/2.0)*x[edo->n - 2];    //DI[n-2]*x[n-2]

        //X[n-1] = (B[n-1] - soma)/D[n - 1]
        x[edo->n-1] = ((h*h*edo->r(edo->a + ((edo->n-1) + 1)*h) - edo->yb*(1 + h*edo->p(edo->b-h)/2.0))-soma)/(-2 + h*h*edo->q(edo->a + (edo->n-1+1)*h));

        ++i;
    }
    (*tempo) = timestamp() - (*tempo);

}


void gaussSeidelSimplificado(SLTridiagonal_t *SL, double *x, double *tempo) {

    int i = 0;
    *(tempo) = timestamp();

    //Enquanto for menor que o número máximo de interações
    while (i < MAX_IT) {

        double soma = 0.0;

        // Primeiro elemento
        soma = SL->DS[0]*x[1];              
        x[0] = (SL->B[0] - soma)/SL->D[0];

        // Segundo elemento até o penúltimo
        for (int j = 1; j < SL->n - 1; ++j) {
            //Leva em consideração as soluções calculadas anteriormente
            soma = SL->DS[j + 1]*x[j + 1] + SL->DI[j - 1]*x[j - 1];
            x[j] = (SL->B[j] - soma)/SL->D[j];
        }

        // Último elemento
        soma = SL->DI[SL->n-2]*x[SL->n-2];
        x[SL->n-1] = (SL->B[SL->n-1] - soma)/SL->D[SL->n-1];

        ++i;
    }
    *(tempo) = timestamp() - *(tempo);

}


double calcularNormaL2(double *x, int n) {

    double norma = 0.0;

    //Percorre o vetor de incógnitas, soma os quadrados dos elementos do vetor e 
    for (int i = 0; i < n; ++i){
        norma = norma + x[i]*x[i];
    }

    //tira a raiz.
    return sqrt(norma);
}


int main () {

    int n_pontos[3] = {5, 10, 100};


    for (int i = 1; i < 2; ++i) {

        double tempo;
        Edo_t edo;
        SLTridiagonal_t *SL;

        double *x = (double *)calloc(n_pontos[i], sizeof(double));
        double *x2 = (double *)calloc(n_pontos[i], sizeof(double));

        SL = alocarSistLin(n_pontos[i]);
        inicializarEdo(&edo, n_pontos[i]);

        gerarTridiagonal(&edo, SL);
        prnSisLin(SL);

        gaussSeidelSimplificado(SL, x, &tempo);
        double norma = calcularNormaL2(x, SL->n);

        fprintf(stderr, "\nGauss-Seidel utilizando vetores\n");
        fprintf(stderr, "\nVetor das incógnitas:");    
        prnVetor(x, SL->n);
        fprintf(stderr, "Norma: %g\n\n", norma);
        fprintf(stderr, "Tempo: %g\n\n", tempo);


        gaussSeidelSemVetores(&edo, x2, &tempo);
        norma = calcularNormaL2(x2, edo.n);

        fprintf(stderr, "\nGauss-Seidel sem utilizar vetores\n");
        fprintf(stderr, "\nVetor das incógnitas:");    
        prnVetor(x2, SL->n);
        fprintf(stderr, "Norma: %g\n\n", norma);
        fprintf(stderr, "Tempo: %g\n\n", tempo);

        liberarSisLin(SL);
        free(x);
        free(x2);
    }





    return 0;
}


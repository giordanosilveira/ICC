#include <stdio.h>
#include <math.h>
#include <float.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"
//#include "geral.h"

void testarIncognitas(SistLinear_t *SL_original, real_t *x) {

    int i = 0; 
    // Roda o laço 5 vezes
    while(i < 5) {

        // Escolhe linhas aleatórias
        int linha = rand() % SL_original->n;
        real_t soma = 0.0;

        // Resolve a linha
        for (int j = 0; j < SL_original->n; ++j) {
            soma = soma + SL_original->A[linha][j]*x[j];
        }

        printf("Resultado original da %dº linha -> %lf, resultado calculado -> %lf\n",linha, SL_original->b[linha], soma);
        ++i;
    }

}


void testarEliminacaoGauss(SistLinear_t *SL, SistLinear_t * SL_original, real_t *residuo, real_t *x, double *tTotal) {
        
        printf("Eliminação de Gauss:\n\n");

        switch (eliminacaoGauss(SL, x, tTotal)) {
        case -1 :
            fprintf(stderr, "Sistema impossível\n");
            return;
        
        case -2 :
            fprintf(stderr, "Sistema Possível e indeterminado\n");
            return;
        }

        *(residuo) = normaL2Residuo(SL, x);
        // printf("Vetor das incógnitas:\n\n");
        // prnVetor(x, SL->n);


        // printf("Testando o resultado de algumas linhas\n");
        // testarIncognitas(SL_original, x);
        // printf("\n\n");

}


void testarGaussSeidel(SistLinear_t *SL, SistLinear_t * SL_original, real_t *residuo, real_t *x, double *tTotal, int *nIntGs){

        printf("Gauss-Seidel:\n\n");
        cpySisLin(SL, SL_original);
        *(nIntGs) = gaussSeidel(SL, x, ERRO, tTotal);
        *(residuo) = normaL2Residuo(SL, x);
        
        // printf("Vetor das incógnitas:\n");
        // prnVetor(x, SL->n);

        // printf("Testando o resultado de algumas linhas\n");
        // testarIncognitas(SL_original, x);
        // printf("\n\n");

}


void testarRefinamento(SistLinear_t *SL, SistLinear_t * SL_original, real_t *residuo, real_t *x, real_t erro, double *tTotal, int *nIntRef){

        printf("Refinamento:\n\n");

        *(nIntRef) = refinamento(SL, x, erro, tTotal);
        *(residuo) = normaL2Residuo(SL, x);

        // printf("Vetor das incógnitas:\n");
        // prnVetor(x, SL->n);

        // testarIncognitas(SL_original, x);
        // printf("\n\n");

}

int main ()
{
  // inicializa gerador de números aleatóreos
    srand(202202);
    int tamanhos[6] = {10, 30, 50, 128, 256, 512}, nIntGs, nIntRef;
    real_t residuos[3] = {0, 0, 0};
    double tempos[3] = {0.0, 0.0, 0.0};

    SistLinear_t *SL, *SL_original;

    for (int i = 0; i < 3; ++i) {
        real_t *x = alocarVetor(tamanhos[i], sizeof(real_t));

        SL = alocaSisLin(tamanhos[i]);
        iniSisLin(SL, diagDominante, COEF_MAX);
        
        SL_original = alocaSisLin(tamanhos[i]);
        cpySisLin(SL_original, SL);
 
        // printf("Sistema Linear:\n");
        // prnSisLin(SL);

        
        testarEliminacaoGauss(SL, SL_original, &residuos[0], x, &tempos[0]);
        cpySisLin(SL, SL_original);

        testarRefinamento(SL, SL_original, &residuos[1], x, ERRO, &tempos[1], &nIntRef);
        cpySisLin(SL, SL_original);

        testarGaussSeidel(SL, SL_original, &residuos[2], x, &tempos[2], &nIntGs);
        
        prnTabela(tamanhos[i], nIntRef, nIntGs, tempos, residuos);
        liberaSisLin(SL);
        free(x);
        //liberaSisLin(SL_original);
    }

    return 0;
    
}


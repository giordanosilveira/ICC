#include "geral.h"
#include "sislin.h"
#include "utils.h"
#include "Metodos.h"

#include <stdio.h>

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

        printf("Resultado original da linha -> %lf, resultado calculado -> %lf\n", SL_original->b[linha], soma);
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
        printf("Vetor das incógnitas:\n\n");
        prnVetor(x, SL->n);


        printf("Testando o resultado de algumas linhas\n");
        testarIncognitas(SL_original, x);

}


void testarGaussSeidel(SistLinear_t *SL, SistLinear_t * SL_original, real_t *residuo, real_t *x, double *tTotal, int *nIntGs){

        printf("Gauss-Sidel:\n\n");
        cpySisLin(SL, SL_original);
        *(nIntGs) = gaussSeidel(SL, x, ERRO, tTotal);
        
        if (*(nIntGs) < 0)
            return;
        
        *(residuo) = normaL2Residuo(SL, x);
        printf("Vetor das incógnitas:\n");
        prnVetor(x, SL->n);
        printf("Resposta Segunda linha (aproximada):\n");

        printf("Testando o resultado de algumas linhas\n");
        testarIncognitas(SL_original, x);

}


void testarRefinamento(SistLinear_t *SL, SistLinear_t * SL_original, real_t *residuo, real_t *x, real_t erro, double *tTotal, int *nIntRef){

        printf("Refinamento:\n\n");

        *(nIntRef) = refinamento(SL, x, erro, tTotal);
        *(residuo) = normaL2Residuo(SL, x);

        printf("Vetor das incógnitas:\n");
        prnVetor(x, SL->n);

        printf("Resposta Segunda linha (aproximada):\n");
        testarIncognitas(SL_original, x);

}
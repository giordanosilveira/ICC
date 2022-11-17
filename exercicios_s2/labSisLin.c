#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

int main ()
{
  // inicializa gerador de números aleatóreos
    srand(202202);
    int tamanhos[6] = {10, 30, 50, 128, 256, 512}, nIntGs, nIntRef;
    real_t residuos[3] = {0, 0};
    double tempos[3] = {0.0, 0.0, 0.0};
    
    SistLinear_t *SL, *SL_original;

    for (int i = 1; i < 2; ++i) {
        real_t *x = alocarVetor(tamanhos[i], sizeof(real_t));

        SL = alocaSisLin(tamanhos[i]);
        iniSisLin(SL, diagDominante, COEF_MAX);
        
        SL_original = alocaSisLin(tamanhos[i]);
        cpySisLin(SL_original, SL);
 
        printf("Sistema Linear:\n");
        prnSisLin(SL);

        printf("Eliminação de Gauss:\n\n");
        eliminacaoGauss(SL, x, &tempos[0]);
        residuos[0] = normaL2Residuo(SL, x);
        printf("Vetor das incógnitas:\n\n");
        prnVetor(x, tamanhos[i]);
        printf("Resposta Segunda linha (aproximada):\n");

        real_t soma = 0.0;
        for (int i = 0; i < SL_original->n; ++i) {
          soma = soma + SL_original->A[5][i]*x[i];
        }
        printf("%lf\n", soma);


        cpySisLin(SL, SL_original);
        printf("Refinamento:\n\n");
        nIntRef = refinamento(SL, x, ERRO, &tempos[1]);
        residuos[1] = normaL2Residuo(SL, x);
        printf("Vetor das incógnitas:\n");
        prnVetor(x, tamanhos[i]);
        printf("Resposta Segunda linha (aproximada):\n");

        soma = 0.0;
        for (int i = 0; i < SL_original->n; ++i) {
          soma = soma + SL_original->A[5][i]*x[i];
        }
        printf("%lf\n", soma);
        

        printf("Gauss-Sidel:\n\n");
        cpySisLin(SL, SL_original);
        nIntGs = gaussSeidel(SL, x, ERRO, &tempos[2]);
        residuos[2] = normaL2Residuo(SL, x);
        printf("Vetor das incógnitas:\n");
        prnVetor(x, tamanhos[i]);
        printf("Resposta Segunda linha (aproximada):\n");

        soma = 0.0;
        for (int i = 0; i < SL_original->n; ++i) {
          soma = soma + SL_original->A[5][i]*x[i];
        }
        printf("%lf\n", soma);


        prnTabela(tamanhos[i], nIntRef, nIntGs, tempos, residuos);
        liberaSisLin(SL);
        free(x);
        //liberaSisLin(SL_original);
    }

    return 0;
    
}


//Giordano Henrique Silveira GRR20197154

#include <stdio.h>
#include <math.h>
#include <float.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"
/*
    É possível estimar as condições em que o método EGP é mais vantajoso que o método GS?

    R: Para matrizes generícas o método EGP é mais vantajoso. O método GS para esse tipo de matriz, não convergiu para um 
    resultado correto, exceto para matrizes menores. Para matrizes maiores sempre parou antes o método pois deu números 
    infinitos. Enquanto, o método EGP deu um resultado correto (isso na maioria das vezes). É claro, os tempos do método EGP,
    à medida que a matriz cresce de tamanho, cresce muito rápido. Para matrizes maiores talvez seja melhor procurar outros mé
    todos de resolução de sistemas Lineares. Porém, para matrizes diagonalmente dominantes, principalmente, o método GS 
    convergiu para a solução mais rapidamente que o método EGP, visto que para estes tipos de matrizes o método GS sempre 
    converge para uma solução. Ou seja, são mais eficazes, Para matrizes de Hilbelt, o método GS consegue convergir para uma 
    solução, cuja a norma máxima do erro absoluto é menor que o erro em Metodos.h .
    
*/



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
        
        //printf("Eliminação de Gauss:\n\n");

        switch (eliminacaoGauss(SL, x, tTotal)) {
            case -1:
                *(residuo) = 0;
                fprintf(stderr, "Eliminação de Gauss: Número infinito\n");
                return;
            case -2:
                *(residuo) = 0;
                fprintf(stderr, "Eliminação de Gauss: NaN\n");
                return;
            case -3:
                *(residuo) = 0;
                fprintf (stderr, "Eliminação de Gauss: O Sistema Linear é impossível\n");
                return;
            case -4:
                *(residuo) = 0;
                fprintf(stderr, "Eliminação de Gauss: O Sistema Linear é possível e indeterminado\n");
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

        //printf("Gauss-Seidel:\n\n");
        cpySisLin(SL, SL_original);
        *(nIntGs) = gaussSeidel(SL, x, ERRO, tTotal);
        *(residuo) = normaL2Residuo(SL, x);
        switch (*(nIntGs)) {
            case -1:
                fprintf(stderr, "GaussSeidel: Número infinito\n");
                return;
            case -2:
                fprintf(stderr, "GaussSeidel: NaN\n");
                return;
        }
        // printf("Vetor das incógnitas:\n");
        // prnVetor(x, SL->n);

        // printf("Testando o resultado de algumas linhas\n");
        // testarIncognitas(SL_original, x);
        // printf("\n\n");

}


void testarRefinamento(SistLinear_t *SL, SistLinear_t * SL_original, real_t *residuo, real_t *x, real_t erro, double *tTotal, int *nIntRef){

        //printf("Refinamento:\n\n");

        *(nIntRef) = refinamento(SL, x, erro, tTotal);
        *(residuo) = normaL2Residuo(SL, x);

        switch (*(nIntRef)) {
            case -1:
                fprintf(stderr, "Refinamento: Número infinito\n");
                return;
            case -2:
                fprintf(stderr, "Refinamento: NaN\n");
                return;
            case -3:
                fprintf (stderr, "Refinamento: O Sistema Linear é impossível\n");
                return;
            case -4:
                fprintf(stderr, "Refinamento: O Sistema Linear é possível e indeterminado\n");
                return;
        }
        
}

int main ()
{
  // inicializa gerador de números aleatóreos
    srand(202202);
    int tamanhos[9] = {10, 30, 50, 128, 256, 512, 1000, 2000, 3000}, nIntGs, nIntRef;
    real_t residuos[3] = {0, 0, 0};
    double tempos[3] = {0.0, 0.0, 0.0};

    SistLinear_t *SL, *SL_original;

    
    for (int matriz = 2; matriz >= 0; --matriz) {
        printf("O tipo de matriz é: ");
        switch (matriz) {
            case 2:
                printf("diagonalmente dominante.\n");
                break;
            case 1:
                printf("hilbert\n");
                break;
            case 0:
                printf("generico\n");
                break;
            
        }
        printf("n\t| t_egp:\t| normaResiduo_egp:\t| t_gs:\t\t\t| it_gs:\t| normaResiduo_gs:\t|  t_ref:\t\t| it_ref:\t| normaResiduo_ref\n");
        for (int i = 0; i < 9; ++i) {
            real_t *x = alocarVetor(tamanhos[i], sizeof(real_t));

            SL = alocaSisLin(tamanhos[i]);
            iniSisLin(SL, matriz, COEF_MAX);
            
            SL_original = alocaSisLin(tamanhos[i]);
            cpySisLin(SL_original, SL);
    
            // printf("Sistema Linear:\n");
            //prnSisLin(SL);

            
            testarEliminacaoGauss(SL, SL_original, &residuos[0], x, &tempos[0]);
            cpySisLin(SL, SL_original);

            //prnSisLin(SL);
            testarRefinamento(SL, SL_original, &residuos[1], x, ERRO, &tempos[1], &nIntRef);
            cpySisLin(SL, SL_original);

            //prnSisLin(SL);
            testarGaussSeidel(SL, SL_original, &residuos[2], x, &tempos[2], &nIntGs);
            
            prnTabela(tamanhos[i], nIntRef, nIntGs, tempos, residuos);
            liberaSisLin(SL);
            //free(x);
            //liberaSisLin(SL_original);
        }
    }

    return 0;
    
}


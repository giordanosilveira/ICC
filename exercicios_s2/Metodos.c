#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"


real_t somarColunas(real_t * linha, int i, int n, real_t *x) {

    real_t soma = 0.0;
    
    // Percorre as colunas da linha indo de 'i' até 'n'
    for (int j = i; j <= n; ++j){

        // Soma as colunas da linha * sua incóginita de solução.
        soma = soma + linha[j]*x[j];
    }
    return soma;

}


void retroSubstituicao(SistLinear_t *SL, real_t *x) {

    // Percorre o vetor das incógnitas da última para a primeira
    for (int i = SL->n-1; i >= 0; --i){
        real_t soma = 0.0;

        // Soma os elementos da linha i
        soma = somarLinhas(SL->A[i], i + 1, SL->n, x);

        // Descobre a incognita daquela linha
        x[i] = (SL->b[i] - soma)/SL->A[i][i];   // (termo independete - soma da linha)/coeficiente do x que ainda não foi descoberto
    }

}


void trocarLinhas(SistLinear_t* SL, int i, int max_pivo){

    real_t aux;
    
    //Percorre todas as colunas das linhas do pivô e da linha que você vai trocar
    for (int coluna = 0; SL->n; coluna++) {

        //Troca os valores das linhas
        aux = SL->A[max_pivo][coluna];
        SL->A[max_pivo][coluna] = SL->A[i][coluna];
        SL->A[i][coluna] = aux;
    }

    //Troca os valores das colunas dos termos independentes
    aux = SL->b[max_pivo];
    SL->b[max_pivo] = SL->b[i];
    SL->b[i] = aux;

}


int encontrarPivoMax(SistLinear_t *SL, int comeco) {

    // Inicializa com os primeiros valores
    real_t maior = SL->A[comeco][comeco];
    int maior_idx = comeco;

    // Percorre a coluna do pivo
    for (int j = comeco + 1; j < SL->n; j++) {

        // Verifica se o maior valor absoluto é maior que o valor maior antigo, se for troca os valores
        if (ABS(SL->A[j][comeco]) > maior) {
            maior = ABS(SL->A[comeco][j]);
            maior_idx = j;
        }
    }
}


int eliminacaoGauss (SistLinear_t *SL, real_t *x, double *tTotal) {

    // Percorre as linhas da Matriz de coeficientes
    for (int i = 0; i < SL->n; ++i) {
        int max_pivo = encontrarPivoMax(SL, i); // Encontra o maior pivô para fazer o pivoteamento
        if (i != max_pivo)  // Se o maior pivô for diferente de i (mesma linha)
            trocarLinhas(SL, i, max_pivo);  // Troca as linhas.

        // Percorrer as linhas abaixo do pivô (linha inicial i)
        for (int k = i + 1; k < SL->n; ++k){

            // Calcula o m
            real_t m = SL->A[k][i] / SL->A[i][i];
            
            // Zera o elemento na linha abaixo do pivô
            SL->A[k][i] = 0.0;

            // Percorre o restante da linha k e atualiza o restante dos seu elementos.
            for (int j = i + 1; j < SL->n; ++j)
                SL->A[k][j] -= SL->A[i][j] * m;

            // Atualiza o restante dos coeficientes
            SL->b[k] -= SL->b[i] * m;
        }
        
    }

    retroSubstituicao(SL, x);

    return 0;
}


/*!
  \brief Essa função calcula a norma L2 do resíduo de um sistema linear 

  \param SL Ponteiro para o sistema linear
  \param x Solução do sistema linear
*/
real_t normaL2Residuo(SistLinear_t *SL, real_t *x)
{
    
}


/*!
  \brief Método de Gauss-Seidel

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
  */
int gaussSeidel (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal)
{

    int n_interacoes = 0;

    real_t *aux = alocarVetor(SL->n, sizeof(real_t));
    memset(x, 0.0, (SL->n)*sizeof(real_t)); //Pode dar seg fault aqui
    
    // Enquanto o número máximo de interações não foi atingido e a norma máxima do erro é maior que o erro, executa esse método.
    while ((n_interacoes < MAXIT) && (calcularNormaMaxErroAbsoluto(aux, x) > ERRO)) {
        
        copiarVetor(aux, x, SL->n);

        // Percorrer os vetores de incognitas (serve também para as linhas do matriz de coeficientes)
        for (int i = 0; i < SL->n; ++i){
            real_t soma = SL->b[i];
            
            // Percorre as colunas da linha i 
            for (int j = 0; j < SL->n; ++j) {
                
                // Se não foi a coluna da diagonal principal
                if (j != i)

                    // Faz a soma levando em conta os valores das incógnitas já calculado
                    soma -= SL->A[i][j]*x[j]; 
            }
            // Calcula a incógnita 'i'
            x[i] = (1/SL->A[i][i])*soma;
        }
        // Incrementa o número de interações
        ++n_interacoes;
    }

}


/*!
  \brief Método de Refinamento

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
  */
int refinamento (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal)
{

}



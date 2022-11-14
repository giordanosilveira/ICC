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

real_t normaL2Residuo(SistLinear_t *SL, real_t *x)
{

    real_t soma = 0.0;
    // Pecorre o vetor de soluções
    for (int i = 0; i < SL->n; ++i) {

        // Soma o quadrado dos elementos das soluções
        soma = soma + pow(x[i], 2);
    }

    // Retorna a raíz quadrada da soma.
    return sqrt(soma);

}



real_t calcularNormaMaxErroAbsoluto(real_t *aux, real_t *x, int tam) {


    real_t max = ABS(x[0]-aux[0]);

    //Percorre todos os termos
    for (int i = 1; i < tam; ++i) {

        // Se o módulo da subtração é maior que max
        if (ABS(x[i]-aux[i]) > max) {
            max = ABS(x[i]-aux[i]);
        }
    }
    return max;

}


int gaussSeidel (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal)
{

    int n_interacoes = 0;

    real_t *aux = alocarVetor(SL->n, sizeof(real_t));
    memset(x, 0.0, (SL->n)*sizeof(real_t)); //Pode dar seg fault aqui
    
    // Enquanto o número máximo de interações não foi atingido e a norma máxima do erro é maior que o erro, executa esse método.
    while ((n_interacoes < MAXIT) && (calcularNormaMaxErroAbsoluto(aux, x, SL->n) > ERRO)) {
        
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

int refinamento (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal)
{

    int i = 0;
    double tempo;
    real_t *residuo = alocarVetor(SL->n, sizeof(real_t));   //Vetor de resíduo

    // Enquanto o número de interações for menor que tTotal
    while ((i < tTotal)) {
        
        // Percorre a matriz
        for (int j = 0; j < SL->n; ++j){
            real_t soma = 0.0;
            for (int k = 0; k < SL->n; ++k){
                // Realiza a soma das colunas da linha 'j' com suas respctivas soluções
                soma = soma + SL->A[j][k]*x[k]; 
            
            }
            // Calcula o resíduo
            residuo[j] = SL->b[j] - soma;
        }

        // Verifica se a norma L2 do residuo calculado é menor que o erro, se sim, para o programa e retorna i
        if (normaL2Residuo(SL, residuo) < erro) {
            return i;
        }

        ++i;    // Incrementa o número de interações.

        // Se não for, calcula novamente a eliminação de Gauss com o resíduo como termo independente.
        //Aqui eu tenho que passar o resíduo no SL->b, 
        // também tenho que mandar uma cópia do Sistema Linear
        if (eliminacaoGauss(SL, x, &tempo) < 0 ) {
            perror("Deu algum erro na eliminação de Gauss");
            return -1;
        }

    }


}



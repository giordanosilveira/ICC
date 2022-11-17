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
        soma = somarColunas(SL->A[i], i + 1, SL->n-1, x);

        // Descobre a incognita daquela linha
        x[i] = (SL->b[i] - soma)/SL->A[i][i];   // (termo independete - soma da linha)/coeficiente do x que ainda não foi descoberto
    }

}


void trocarLinhas(SistLinear_t* SL, int i, int max_pivo){

    real_t aux;
    
    //Percorre todas as colunas das linhas do pivô e da linha que você vai trocar
    for (int coluna = 0; coluna < SL->n; coluna++) {

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
    real_t maior = ABS(SL->A[comeco][comeco]);
    int maior_idx = comeco;

    // Percorre a coluna do pivo
    for (int j = comeco + 1; j < SL->n; ++j) {

        // Verifica se o maior valor absoluto é maior que o valor maior antigo, se for troca os valores
        if (ABS(SL->A[j][comeco]) > maior) {
            maior = ABS(SL->A[j][comeco]);
            maior_idx = j;
        }
    }
    return maior_idx;
}


int eliminacaoGauss (SistLinear_t *SL, real_t *x, double *tTotal) {

    // Percorre as linhas da Matriz de coeficientes
    double t_inicio, t_fim;

    t_inicio = timestamp();
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
    t_fim = timestamp();

    (*tTotal) = t_fim - t_inicio;

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

    SistLinear_t *SL_original = alocaSisLin(SL->n);
    cpySisLin(SL_original, SL);

    int n_interacoes = 0;
    double t_inicial, t_final;

    real_t *aux = alocarVetor(SL->n, sizeof(real_t));
    memset(x, 0.0, (SL->n)*sizeof(real_t)); //Pode dar seg fault aqui
    

    t_inicial = timestamp();
    // Enquanto o número máximo de interações não foi atingido e a norma máxima do erro é maior que o erro, executa esse método.
    while ((n_interacoes < MAXIT)) {
        
        copiarVetor(aux, x, SL->n);

        // Percorrer os vetores de incognitas (serve também para as linhas do matriz de coeficientes)
        for (int i = 0; i < SL->n; ++i){
            real_t soma = SL->b[i];
            
            // Percorre as colunas da linha i 
            for (int j = 0; j < SL->n; ++j) {
                
                // Se não foi a coluna da diagonal principal
                if (j == i) {
                    continue;
                } 
                // Faz a soma levando em conta os valores das incógnitas já calculado
                soma = soma - SL->A[i][j]*x[j];
            }
           // Calcula a incógnita 'i'
           x[i] = (1/SL->A[i][i])*soma;
        }
        
        if (calcularNormaMaxErroAbsoluto(aux, x, SL->n) < ERRO) {
            return n_interacoes;
        }

       // Incrementa o número de interações
       ++n_interacoes;
       cpySisLin(SL, SL_original);
    }
    t_final = timestamp();
    (*tTotal) = t_final - t_inicial;
    return n_interacoes;

}

int refinamento (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal)
{

    int i = 0;
    double t_inicial, t_final, lixo;                        //Tempo inicial, final, lixo (eliminação de gauss interna)

    real_t *w = alocarVetor(SL->n, sizeof(real_t));         //erro.
    real_t *x0 = alocarVetor(SL->n, sizeof(real_t));        //Vetor com as soluções anteriores.
    real_t *residuo = alocarVetor(SL->n, sizeof(real_t));   //Vetor de resíduo.

    SistLinear_t *SL_original = alocaSisLin(SL->n);         //Sistema Linear original
    
    cpySisLin(SL_original, SL);
    t_inicial = timestamp();

    // Enquanto o número de interações for menor que tTotal
    while ((i < MAXIT)) {
        
        // Percorre as 'linhas' da sistema linear
        for (int j = 0; j < SL->n; ++j){
            real_t soma = 0.0;

            for (int k = 0; k < SL->n; ++k){

                // Realiza a soma das colunas da linha 'j' com suas respectivas soluções
                soma = soma + SL->A[j][k]*x[k]; 
            
            }

            // Calcula o resíduo
            residuo[j] = SL->b[j] - soma;
        }

        // Verifica se a norma L2 do residuo calculado é menor que o erro, se sim
        real_t retorno = normaL2Residuo(SL, residuo);
        if ( retorno < erro) {
            fprintf(stderr, "Norma L2 do resíduo é menor que o erro\n");

            //calcula o tempo do método,
            t_final = timestamp();              //tempo final do método
            (*tTotal) = t_final - t_inicial;    //Tempos total do método
    
            //libera as estruturas usadas internamente.
            free(x0);
            free(w);
            free(residuo);

            //retorna o número de interações.
            return i;
        }


        // Se não, calcula novamente a eliminação de Gauss com o resíduo como termo independente e w (erro) como
        // as incóginitas.
        cpySisLin(SL, SL_original);
        SL->b = residuo;

        //Verifica se a eliminação de gauss deu errado, se deu errado, 
        if (eliminacaoGauss(SL, w, &lixo) < 0 ) {
            fprintf(stderr, "Deu algum erro na eliminação de Gauss");

            //Calcula o tempo final do método.
            t_final = timestamp();           //tempo final do método
            (*tTotal) = t_final - t_inicial; //Calcula o tempo final do método

            // libera as estruturas usadas internamente
            free(x0);
            free(w);
            free(residuo);
            
            // e retorna um código de erro.
            return -1;
        }

        // Se não deu errado, w está com o erro das variáveis, então, é preciso descobrir a nova solução.
        // Logo, percorre o vetor de soluções,
        for (int j = 0; j < SL->n; ++j) {
            x0[j] = x[j];       //guarda a solução antiga e
            x[j] = x[j] + w[j]; //calcula a solução nova. (antiga + erro)
        }

        // Calcula a norma máxima do erro Absoluto. Se for menor que um erro tolerável, 
        if (calcularNormaMaxErroAbsoluto(x, x0, SL->n) < erro) {
            fprintf(stderr, "Norma Máxima do erro Absoluto é menor que o erro\n");

            //calcula o tempo final do método,
            t_final = timestamp();           //tempo final do método
            (*tTotal) = t_final - t_inicial; //Tempos total do método

            // libera as estruturas usadas internamente,
            free(x0);
            free(w);
            free(residuo);

            // e retorna o número de interações.
            return i;
        }

        ++i;    // incrementa o número de interações.
    }
    
    // Se terminou as interações,
    // libera as estruturas usadas internamente
    free(x0);
    free(w);
    free(residuo);

    //calcula o tempo do método,
    t_final = timestamp();           //tempo final do método
    (*tTotal) = t_final - t_inicial; //Calcula o tempo final do método
    
    //retorna o numero de interações (MAXIT)
    return i;

}



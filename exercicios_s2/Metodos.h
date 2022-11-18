#ifndef __METODOS_H__
#define __METODOS_H__

// Parâmetros para teste de convergência
#define MAXIT 100     // número máximo de iterações para métodos iterativos
#define ERRO 1.0e-10  // Tolerância para critérios de parada em métodos iterativos


/**
 * @brief Soma as colunas da linha passada. Indo de 'i' até 'n'.
 * 
 * @param linha (real_t*) : linha cujas as colunas de 'i' até 'n' serão somadas.
 * @param i (int) : Índice do começo da soma.
 * @param n (int) : Tamanho total da linha.
 * @param x (real_t*) : Vetor das incoginitas
 * @return (real_t) : soma das colunas da 'linha' de 'i' até 'n'. 
 */
real_t somarColunas(real_t * linha, int i, int n, real_t *x);


/**
 * @brief Método da retrosubistituição.
 * 
 * @param SL (SistLinear_t*) : O Sistema Linear
 * @param x (real_t *) : vetor das incógnitas do Sistema Linear.
 */
void retroSubstituicao(SistLinear_t *SL, real_t *x);


/**
 * @brief Troca os elementos da linha i com a linha do max_pivô
 * 
 * @param SL (SistLinear_t*) : O sistema linear
 * @param i (int) : Linha que será trocada pela linha do maior pivô.
 * @param max_pivo (int) : Linha que contém o maior pivõ.
 */
void trocarLinhas(SistLinear_t* SL, int i, int max_pivo);


/**
 * @brief Encontra o maior número absoluto para o pivoteamento parcial
 * 
 * @param SL (SistLinear_t*) : Sistema Linear completo
 * @param comeco (int) : Da onde começa a procurar
 * @return int : 
 */
int encontrarPivoMax(SistLinear_t *SL, int comeco);


/*!
  \brief Essa função calcula a norma L2 do resíduo de um sistema linear 

  \param SL (SistLinear_t) : Ponteiro para o sistema linear
  \param x (real_t *) : Solução do sistema linear
  \return (real_t) : Norma L2.
*/
real_t normaL2Residuo(SistLinear_t *SL, real_t *x);


/**
 * @brief Calcula a norma máxima do erro absoluto.
 * 
 * @param aux (real_t *) : Vetor com os valores das incógnitas anteriores.
 * @param x (real_t*) : Vetor com os valores das incóginitas atuais.
 * @param tam (int) : tamanho do vetor.
 * @return (real_t) : Norma maxima do erro absoluto. 
 */
real_t calcularNormaMaxErroAbsoluto(real_t *aux, real_t *x, int tam);


/*!
  \brief Método da Eliminação de Gauss

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. 0 em caso de sucesso.
*/
int eliminacaoGauss (SistLinear_t *SL, real_t *x, double *tTotal);


/*!
  \brief Método de Refinamento

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
  */
int refinamento (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal);


/*!
  \brief Método de Gauss-Seidel

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
*/
int gaussSeidel (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal);


/**
 * @brief Testa para ver se o Sistema Linear é impossível ou indeterminado
 * ou SPD.
 * 
 * @param SL (SistLinear_t *) : Sistema Linear 
 * @return (int) : 0 se é um SPD, -1 se é um sistema impossível ou indeterminado.
 */
int testarSL(SistLinear_t *SL);


#endif // __METODOS_H__


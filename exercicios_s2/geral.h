#ifndef GERAL_H
#define GERAL_H


/**
 * @brief Testa a eliminação de Gauss.
 * 
 * @param SL (SistLinear_t *) : Sistema Linear.
 * @param SL_original (SistLinear_t *) : Sistema Linear original.
 * @param residuo (real_t*) : residuo
 * @param x (real_t *) : Vetor de incógnitas.
 * @param tTotal (double) : Tempo do método.
 * @return (int) : O se der tudo certo, -1 se der algo errado. 
 */
void testarEliminacaoGauss(SistLinear_t *SL, SistLinear_t *SL_original, real_t *residuo, real_t *x, double *tTotal);


/**
 * @brief Testa a eliminação de Gauss.
 * 
 * @param SL (SistLinear_t *) : Sistema Linear.
 * @param SL_original (SistLinear_t *) : Sistema Linear original.
 * @param residuo (real_t*) : residuo
 * @param x (real_t *) : Vetor de incógnitas.
 * @param tTotal (double) : Tempo do método.
 * @param nIntGs (int*) : Retorno do número de interações do Gauss-Seidel. 
 * @return (int) : O se der tudo certo, -1 se der algo errado. 
 */
void testarGaussSeidel(SistLinear_t *SL, SistLinear_t *SL_original, real_t *residuo, real_t *x, double *tTotal, int *nIntGs);

/**
 * @brief Testa a eliminação de Gauss.
 * 
 * @param SL (SistLinear_t *) : Sistema Linear.
 * @param SL_original (SistLinear_t *) : Sistema Linear original.
 * @param residuo (real_t*) : residuo
 * @param x (real_t *) : Vetor de incógnitas.
 * @param erro (real_t) : erro.
 * @param tTotal (double) : Tempo do método.
 * @param nRefInt (int*) : Retorno do número de interações do refinamento.
 * @return (int) : O se der tudo certo, -1 se der algo errado. 
 */
void testarRefinamento(SistLinear_t *SL, SistLinear_t *SL_original, real_t *residuo, real_t *x, real_t erro, double *tTotal, int *nRefInt);

#endif
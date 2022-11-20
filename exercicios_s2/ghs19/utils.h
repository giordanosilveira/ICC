#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// Valor absoluto de um número. Alternativa ao uso da função 'fabs()'
#define ABS(num)  ((num) < 0.0 ? -(num) : (num))

// real_t: tipo usado para representar valores em ponto flutuante
typedef double real_t;

// rtime_t: tipo usado para representar valores de tempo em ponto flutuante
typedef double rtime_t;

// Funções
double timestamp(void);

/**
 * @brief Aloca um vetor de tamanho tam*sizeof
 * 
 * @param tam (int) : tamanho total do vetor.
 * @param size (int) : tamanho dos elementos do vetor.
 * @return (real_t*) : ponteiro para esse vetor.
 */
real_t *alocarVetor(int tam, int size);

/**
 * @brief Copia o vetor origem para o vetor destino.
 * 
 * @param dest (real_t*) : Vetor destino.
 * @param orig (real_t*) : Vetor origem.
 * @param tam (int) : Tamanho do vetor.
 */
void copiarVetor(real_t *dest, real_t *orig, int tam);

#endif // __UTILS_H__


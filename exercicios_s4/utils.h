#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>


typedef double real_t;
typedef double rtime_t;
typedef char * string_t;

double timestamp(void);

/**
 * @brief Printa um vetor na saída de erro.
 * 
 * @param v (double*) : vetor.
 * @param tam (int) : tamanho do vetor.
 */
void prnVetor(double *v, int tam);


/**
 * @brief Aloca espaço na memória para um vetor genérico.
 * 
 * @param tam (int) : Quantidade de elementos do vetor.
 * @param tam_elementos (int) : Tamanho dos elementos do vetor.
 * @return (void*) : Ponteiro genérico para essa região de memória. 
 */
void *alocarVetor(int tam, int tam_elementos);

#endif // __UTILS_H__


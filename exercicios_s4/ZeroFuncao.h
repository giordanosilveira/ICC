#ifndef __ZEROFUNCAO_H__
#define __ZEROFUNCAO_H__

#include <float.h>

// Aproximação aceitável como valor zero
#define ZERO DBL_EPSILON

// Parâmetros para teste de convergência
#define MAXIT 500
#define EPS 1.0e-8

typedef struct {
  double *p;
  int grau;
} Polinomio;

/**
 * @brief Calculo do método newton Raphson para o cálculo de 0 de função
 * 
 * @param p (Polinomio) : O Polinômio.
 * @param x0 (double) : Chute inicial.
 * @param eps (double) : Erro.
 * @param it (*int) : Número de interações
 * @param raiz (double*) : Raiz calculada.
 * @param func (function pointer) : Função usada para o cálculo do polinômio. Pode ser o rapído ou o lento.
 * @return (double) : Erro obtido para o valor final calculado para a raiz. 
 */
double newtonRaphson (Polinomio p, double x0, double eps, int *it, double *raiz, void (*func)(Polinomio, double, double*, double*));


/**
 * @brief Método da secante para o cálculo de 0 de função
 * 
 * @param p (Polinomio) : O Polinômio.
 * @param x0 (double) : Chute inicial. 
 * @param x1 (double) : Chute inicial.
 * @param eps (double) : Erro.
 * @param it (*int) : Variável onde será guardado o número de interações 
 * @param raiz (double*) : Variável onde será guardada a raiz calculada.
 * @param func (function pointer) : Função usada para o cálculo do polinômio. Pode ser o rapído ou o lento.
 * @return (double) : Erro obtido para o valor final calculado para a raiz.  
 */
double secante (Polinomio p, double x0, double x1, double eps, int *it, double *raiz, void (*func)(Polinomio, double, double*, double*));

// Cálculo de Polinômios
void calcPolinomio_rapido(Polinomio p, double x, double *px, double *dpx );
void calcPolinomio_lento(Polinomio p, double x, double *px, double *dpx );


/**
 * @brief Printa na saída de erro um polinômio p.
 * 
 * @param p (Polinomio *) : Um polinômino.
 */
void prnPolinomio(Polinomio *p);

/**
 * @brief Aloca espaço na memória e inicializa o polinômino.
 * 
 * @param grau (int) : Grau do polinômio.
 * @param coeficientes (strint_t) : Coefiecientes digitados pelo usuário.
 * @return Polinomio* 
 */
Polinomio * initPolinomio(int *grau, string_t coeficientes);


#endif // __ZEROFUNCAO_H__


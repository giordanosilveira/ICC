#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"

/*  Retorna tempo em milisegundos

    Forma de uso:
 
    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/

double timestamp(void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return((double)(tp.tv_sec*1.0e3 + tp.tv_nsec*1.0e-6));
}


void prnVetor(double *v, int tam) {

    fprintf(stderr, "\n");
    for (int i = 0; i < tam; ++i){
        fprintf(stderr, "%10g " ,v[i]);
    }
    fprintf(stderr, "\n\n");
}


void *alocarVetor(int tam, int tam_elementos) {

    void *ptr;

    ptr = calloc(tam, tam_elementos);
    if (! ptr) {
        fprintf(stderr, "Não foi possível alocar espaço para o vetor na memória\n");
        exit(1);
    }

    return ptr;

}

void prnTabela(string_t metodo, int iteracao, double raiz, double erro, double tempo) {

    
    fprintf(stderr, "%s\t %d\t\t %g\t %4g\t\t %g\n", metodo, iteracao, raiz, erro, tempo);

}
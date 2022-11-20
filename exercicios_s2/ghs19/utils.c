//Giordano Henrique Silveira GRR20197154

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"

/*  Retorna tempo em milisegundos desde EPOCH

    Forma de uso:
 
    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/

double timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (double) tp.tv_sec*1.0e3 + (double) tp.tv_nsec*1.0e-6 );
}

real_t *alocarVetor (int tam, int size) {

    real_t *v;

    v = (real_t *)calloc(tam, sizeof(real_t));
    if (! v) {
        perror("Não foi possível alocar espaço para o vetor");
        return NULL;
    }

    for (int i = 0; i < tam; ++i) {
        v[i] = 0.0;
    }

    return v;

}

void copiarVetor(real_t *dest, real_t *orig, int tam) {

    for (int i = 0; i < tam; ++i) {
        dest[i] = orig[i];
    }


}

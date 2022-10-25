/*
Exercício 1 - Representação numérica.
A) 
    * somaSequencia(float *dados, unsigned int tam): soma todos os dados do vetor.
    * somaPar(float *dados, unsigned int tam): soma todos os elementos do vetor, porém usando
    * divisão e conquista.
B)
    O resultado de somaPar é mais preciso.
    o somaSequencia() vai somando os números sequencialmente o que vai gerando números com expoentes diferentes, 
    o que vai gerando erros a medida que a soma vai evoluindo. Enquanto isso, o somaPar() soma números dois a dois com expoentes iguais
    ou números com expoentes suficientemente perto, fazendo com que a precisão seja melhor.

C) 
    A medida que o NUM_elementos vai aumentando a soma perdendo precisão. Isso ocorre porque a precisão de um float são 7 digitos (24 bit), então
    a partir de um certo momento, será somado um número com um expoente muito grande com um muito pequeno. A parte muito pequena será ignorada
    (ou truncada) e ficará somento os primeiros dígitos do float. 

*/

#include <stdio.h>
#include <stdlib.h>

#define VALOR 0.6f
#define NUM_ELEMENTOS 100000000

float somaSequencia( float *dados, unsigned int tam ) {
    float soma = 0.0;
    while ( tam-- ) {
        //printf("soma -> %1.15f, dados[tam] -> %1.15f\n", soma, dados[tam]);
        soma += dados[tam];
    }
    return soma;
}
float somaPar( float *dados, unsigned int tam ) {
    if (tam == 2)
        //printf("dados[0] -> %1.15f, dados[1] -> %1.15f, dados[0] + dados[1 -> %1.15f\n", dados[0], dados[1], dados[0]+dados[1]);
        return dados[0] + dados[1];
    if (tam == 1)
        return dados[0];
    
    unsigned int div = tam / 2;
    return somaPar(dados, div) + somaPar(dados+div, tam-div);
}
void main() {
// Preenche um vetor
    //printf("%f", VALOR);
    float *dados = (float*) malloc(NUM_ELEMENTOS * sizeof(float));
    for (unsigned int i = 0; i < NUM_ELEMENTOS; ++i)
        dados[i] = VALOR;

    float soma1 = somaSequencia( dados, NUM_ELEMENTOS );
    printf("Soma sequencia: %1.15f\n", soma1);

    float soma2 = somaPar( dados, NUM_ELEMENTOS );
    printf("Soma par: %1.15f\n", soma2);

    free (dados);
}
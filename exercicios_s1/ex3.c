#include <stdio.h>
#include <stdlib.h>

typedef struct erro_float_t {
  
    float num;
    float erro;

} erro_float_t;

void soma(erro_float_t A, erro_float_t B){

    erro_float_t soma_minima;
    soma_minima.num = (A.num - A.erro) + (B.num - B.erro);
    printf("O menor valor de A é %1.2f e o de B é %1.2f\n", A.num - A.erro, B.num - B.erro);
    printf("Portanto, A + B = %1.2f + %1.2f = %1.2f\n", A.num - A.erro, B.num - B.erro, soma_minima.num);

    erro_float_t soma_maxima;
    soma_maxima.num = (A.num + A.erro) + (B.num + B.erro);
    printf("O máximo valor de A é %1.2f e o de B é %1.2f\n", A.num + A.erro, B.num + B.erro);
    printf("Portanto, A + B = %1.2f + %1.2f = %1.2f\n", A.num + A.erro, B.num + B.erro, soma_maxima.num);

    printf("Assim, %1.2f <= A + B <= %1.2f -> X + Y = %1.2f +- %1.2f\n", soma_minima.num, soma_maxima.num, soma_maxima.num - (soma_maxima.num - soma_minima.num)/2,(soma_maxima.num - soma_minima.num)/2);
}
// void produto(erro_float_t A, erro_float_t B){

// }
// void potencia(erro_float_t A, erro_float_t B){

// }
// void divisao(erro_float_t A, erro_float_t B){

// }

int main () {

    erro_float_t A, B;
    printf("Entre com o primeiro número e o erro:\n>");
    scanf("%f %f", &A.num, &A.erro);

    printf("Entre com o primeiro número e o erro:\n>");
    scanf("%f %f", &B.num, &B.erro);

    soma(A, B);
    // produto(A, B);
    // potencia(A, B);
    // divisao(A, B);

}
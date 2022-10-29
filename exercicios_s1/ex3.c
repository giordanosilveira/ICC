#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct erro_float_t {
  
    float num;
    float erro;

} erro_float_t;

void soma(erro_float_t A, erro_float_t B){

    erro_float_t soma_minima;
    soma_minima.num = (A.num - A.erro) + (B.num - B.erro);
    printf("O menor valor de A é %1.6f e o de B é %1.6f\n", A.num - A.erro, B.num - B.erro);
    printf("Portanto, A + B = %1.6f + %1.6f = %1.6f\n", A.num - A.erro, B.num - B.erro, soma_minima.num);

    erro_float_t soma_maxima;
    soma_maxima.num = (A.num + A.erro) + (B.num + B.erro);
    printf("O máximo valor de A é %1.6f e o de B é %1.6f\n", A.num + A.erro, B.num + B.erro);
    printf("Portanto, A + B = %1.6f + %1.6f = %1.6f\n", A.num + A.erro, B.num + B.erro, soma_maxima.num);

    printf("Assim, %1.6f <= A + B <= %1.6f -> X + Y = %1.6f +- %1.6f\n", soma_minima.num, soma_maxima.num, soma_maxima.num - (soma_maxima.num - soma_minima.num)/2,(soma_maxima.num - soma_minima.num)/2);
}
void produto(erro_float_t A, erro_float_t B){

    erro_float_t produto_minima;
    produto_minima.num = (A.num - A.erro) * (B.num - B.erro);
    printf("O menor valor de A é %1.6f e o de B é %1.6f\n", A.num - A.erro, B.num - B.erro);
    printf("Portanto, A * B = %1.6f * %1.6f = %1.6f\n", A.num - A.erro, B.num - B.erro, produto_minima.num);

    erro_float_t produto_maxima;
    produto_maxima.num = (A.num + A.erro) * (B.num + B.erro);
    printf("O máximo valor de A é %1.6f e o de B é %1.6f\n", A.num + A.erro, B.num + B.erro);
    printf("Portanto, A * B = %1.6f * %1.6f = %1.6f\n", A.num + A.erro, B.num + B.erro, produto_maxima.num);

    printf("Assim, %1.6f <= A * B <= %1.6f -> X * Y = %1.6f +- %1.6f\n", produto_minima.num, produto_maxima.num, produto_maxima.num - (produto_maxima.num - produto_minima.num)/2,(produto_maxima.num - produto_minima.num)/2);
}
void potencia(erro_float_t A, erro_float_t B){
    erro_float_t potencia_minima;
    potencia_minima.num = pow((A.num - A.erro), (B.num - B.erro));
    printf("O menor valor de A é %1.6f e o de B é %1.6f\n", A.num - A.erro, B.num - B.erro);
    printf("Portanto, A^B = %1.6f^%1.6f = %1.6f\n", A.num - A.erro, B.num - B.erro, potencia_minima.num);

    erro_float_t potencia_maxima;
    potencia_maxima.num = pow((A.num + A.erro), (B.num + B.erro));
    printf("O máximo valor de A é %1.6f e o de B é %1.6f\n", A.num + A.erro, B.num + B.erro);
    printf("Portanto, A^B = %1.6f^%1.6f = %1.6f\n", A.num + A.erro, B.num + B.erro, potencia_maxima.num);

    printf("Assim, %1.6f <= A^B <= %1.6f -> X^Y = %1.6f +- %1.6f\n", potencia_minima.num, potencia_maxima.num, potencia_maxima.num - (potencia_maxima.num - potencia_minima.num)/2,(potencia_maxima.num - potencia_minima.num)/2);
}
void divisao(erro_float_t A, erro_float_t B){
    
    erro_float_t divisao_minima;
    divisao_minima.num = (A.num - A.erro)/(B.num - B.erro);
    printf("O menor valor de A é %1.6f e o de B é %1.6f\n", A.num - A.erro, B.num - B.erro);
    printf("Portanto, A/B = %1.6f/%1.6f = %1.6f\n", A.num - A.erro, B.num - B.erro, divisao_minima.num);

    erro_float_t divisao_maxima;
    divisao_maxima.num = (A.num + A.erro)/(B.num + B.erro);
    printf("O máximo valor de A é %1.6f e o de B é %1.6f\n", A.num + A.erro, B.num + B.erro);
    printf("Portanto, A/B = %1.6f/%1.6f = %1.6f\n", A.num + A.erro, B.num + B.erro, divisao_maxima.num);

    printf("Assim, %1.6f <= A/B <= %1.6f -> X/Y = %1.6f +- %1.6f\n", divisao_minima.num, divisao_maxima.num, divisao_maxima.num - (divisao_maxima.num - divisao_minima.num)/2,(divisao_maxima.num - divisao_minima.num)/2);

}

int main () {

    erro_float_t A, B;
    printf("Entre com o primeiro número e o erro:\n>");
    scanf("%f %f", &A.num, &A.erro);

    printf("Entre com o segundo número e o erro:\n>");
    scanf("%f %f", &B.num, &B.erro);

    printf("Soma:\n");
    soma(A, B);
    printf("\n");
    printf("Produto:\n");
    produto(A, B);
    printf("\n");
    printf("Potência:\n");
    potencia(A, B);
    printf("\n");
    printf("Divisão:\n");
    divisao(A, B);
    printf("\n");

}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <math.h>

typedef union {

    int32_t i;
    float f;
    struct 
    {
        uint32_t mantissa : 23;
        uint32_t expoent : 8;
        uint32_t sign : 1;   
    } parts;
    
} Float_t;
void printFloat_t(Float_t num) {
    printf("f: %1.9e, ix:0x%08X, s:%d, e:%d, ve: %d, mx:0x%06X\n", num.f, num.i, num.parts.sign, num.parts.expoent, num.parts.expoent - 127, num.parts.mantissa);
}

int AlmostEqualRelative(Float_t A, Float_t B)
{
    // Calculate the difference.
    Float_t diff, largest, relEpsilon;
    diff.f = fabs(A.f - B.f);
    A.f = fabs(A.f);
    B.f = fabs(B.f);
    // Find the largest
    largest.f = (B.f > A.f) ? B.f : A.f;
    relEpsilon.f = largest.f * FLT_EPSILON;

    printf("\tThe difference: ");
    printFloat_t(diff);
    
    printf("\trel. Epsilon:   ");
    printFloat_t(relEpsilon);
    
    if (diff.f <= relEpsilon.f)
        return 1;
    return 0;
}


int main () {

    Float_t numOriginal, num, nexta;

    printf("Entre com um número real:\n>");
    scanf("%f", &numOriginal.f);

    printf("Número original:\n");
    printFloat_t(numOriginal);
    printf("\n");


    nexta.f = nextafterf(numOriginal.f,numOriginal.f + 1);
    printf("Proximo número dado pela função nextafterf():\n");
    printFloat_t(nexta);
    printf("\n");

    num.f = numOriginal.f;
    num.parts.mantissa = num.parts.mantissa + 1;
    printf("Minha implementação (mantissa + 1):\n");
    printFloat_t(num);
    printf("\n\n");

    if (AlmostEqualRelative(nexta, num))
        printf("São iguais\n\n");
    else
        printf("Não são iguais\n\n");

    nexta.f = nextafterf(numOriginal.f,numOriginal.f - 1);
    printf("Número anterior dado pela função nextafterf():\n");
    printFloat_t(nexta);
    printf("\n");

    num.f = numOriginal.f;
    num.parts.mantissa = num.parts.mantissa - 1;
    printf("Minha implementação (mantissa - 1):\n");
    printFloat_t(num);
    printf("\n");
    

    if (AlmostEqualRelative(nexta, num))
        printf("São iguais\n\n");
    else
        printf("Não são iguais\n\n");

    return 0;
}
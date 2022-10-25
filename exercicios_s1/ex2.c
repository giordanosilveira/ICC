#include <stdio.h>
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

void inicializar_float_t(Float_t *a_float){
    a_float[0].f = 0.0;
    a_float[1].f = 0.2;
    a_float[2].f = 1.0;
    a_float[3].f = 1.5;
    a_float[4].f = 1.75;
    a_float[5].f = 1.99999988;
    a_float[6].f = 2.0;
    a_float[7].f = 16777215;
     a_float[8].f = 1.410129846*pow(10,-45);
} 

int main() {

    Float_t array[12];

    inicializar_float_t(array);
    for (int i = 0; i < 9; i++) {
        printFloat_t(array[i]);
    }
    printf("\nEpsilon: %1.15f\n", FLT_EPSILON);
    return 0;
}
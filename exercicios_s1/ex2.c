#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <math.h>


/*B)
        Para números não normalizados, o expoente vai para 0, porém a mantissa é um número diferente
    de 0. Além disso, para números muito pequenos não a distinção de um para outro. Eles atingem um número
    mínimo e permanecem neste número, ou seja, precisão dos números diminui bruscamente.
        Para números normalizados a precisão aumenta. Há muito mais números entre 1.0e-38 e 2.0e-38 do que 1.0e-45 e 2.0e-45 que são número
    não normalizados. Ou seja, quando os números são normalizados e possível representar muito mais números
    entre dois floats perto do zero do que quando os números são denormalizados. 

*/

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
    a_float[1].f = 1.410129846*pow(10,-45);
    a_float[2].f = 1.4101298465444444*pow(10,-45);
    a_float[3].f = 1.41012*pow(10,-45);
    a_float[4].f = 3.41012*pow(10,-45);
    a_float[5].f = 3.0*pow(10,-45);
    a_float[6].f = 5.2*pow(10,-45);
    a_float[7].f = 10.41012*pow(10,-45);
    a_float[8].f = 100.41012*pow(10,-45);
    a_float[9].f = 1.41012984*pow(10,-44);
    a_float[10].f = 4.1012984*pow(10,-44);
    a_float[11].f = 10.41012984*pow(10,-44);
    a_float[12].f = 20.41012984*pow(10,-44);
    a_float[13].f = 100.41012984*pow(10,-43);
    //a_float[2].f = 1.410129847*pow(10,-45);
    a_float[14].f = 1.410129850*pow(10,-38);
    a_float[15].f = 1.41012985012345*pow(10,-38);
    a_float[16].f = 1.4101*pow(10,-38);
    a_float[17].f = 2.4101*pow(10,-38);
    a_float[18].f = 3.4101*pow(10,-38);
    a_float[19].f = 10000.4101*pow(10,-38);
    a_float[20].f = 100.4101*pow(10,-38);
    a_float[21].f = 10000.4101*pow(10,-38);
    a_float[22].f = 20.4101*pow(10,-38);
    a_float[23].f = 50.4101*pow(10,-38);
    a_float[24].f = 38.4101*pow(10,-38);
    a_float[25].f = 45.4101*pow(10,-38);
    a_float[26].f = 100000.4101*pow(10,-37);
    a_float[27].f = 1.4101*pow(10,-37);
    a_float[28].f = 0.2;
    a_float[29].f = 1.0;
    a_float[30].f = 1.5;
    a_float[31].f = 1.75;
    a_float[32].f = 1.99999988;
    a_float[33].f = 2.0;
    a_float[34].f = 16777215;
    a_float[35].f = (3.40282347*pow(10, 38));
    a_float[36].f = (1.410129846*pow(10, 10))/0;
    a_float[37].f = (-1.410129846*pow(10, 10))/0;
    a_float[38].f = 0.0/0;
} 

int main() {

    Float_t array[40];

    inicializar_float_t(array);
    for (int i = 0; i < 40; i++) {
        printFloat_t(array[i]);
    }
    printf("\nEpsilon: %1.15f\n", FLT_EPSILON);
    return 0;
}
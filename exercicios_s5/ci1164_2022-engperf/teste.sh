#!/bin/bash

METRICA="FLOPS_DP L2CACHE"

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

gcc ${CFLAGS} teste.c -o teste ${LFLAGS}
for k in $METRICA
do
    likwid-perfctr -C 1 -g ${k} -m ./teste >${k}_SemOtimiz.log
done

rm -f teste
gcc ${CFLAGS} -O3 teste.c -o teste ${LFLAGS}
for k in $METRICA
do
    likwid-perfctr -C 1 -g ${k} -m ./teste >${k}_Otimiz.log
done


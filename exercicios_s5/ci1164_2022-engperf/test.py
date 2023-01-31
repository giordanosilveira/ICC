import os

os.system("make")

params_likwid = ["FLOPS_DP", "L2CACHE", "L3"]
tam = [64, 100, 128, 1024, 2000, 2048]

grupos = [("FLOPS_DP","\nDP MFLOP/s"), ("L2CACHE","\nL2 miss ratio"), ("L3","\nL3 bandwidth [MBytes/s]")]
tamanhos = [64, 100, 128, 1024, 2000, 2048]

for tam in tamanhos:
    for grupo in grupos:
        os.system(f"likwid-perfctr -O -C 3 -g {grupo[0]} -m ./matmult -n {tam} > {tam}_{grupo[0]}.csv")


for grupo in grupos:
    lista = list()
    lista_tempo = list()
    for tam in tamanhos:
        with open(f"{tam}_{grupo[0]}.csv", "r") as arq:
            f = arq.read()
            f = f.split(',')
            lista.append([f[i + 1] for i, elemento in enumerate(f) if elemento == grupo[1]])

        lista[len(lista) - 1].insert(0, f"{tam}")

    with open(f"{grupo[0]}.csv", 'w') as arq2:
            arq2.write("Tamanho,t_matvet,t_matmat\n")
            for m in lista:
                arq2.write(f"{','.join(m)}\n")


lista = list()
for tam in tamanhos:
    with open(f"{tam}_{grupo[0]}.csv", "r") as arq:
        f = arq.read()
        f = f.split(',')
        lista.append([f[i + 1] for i, elemento in enumerate(f) if elemento == "\nRuntime (RDTSC) [s]"])

    lista[len(lista) - 1].insert(0, f"{tam}")

    with open(f"TIME.csv", 'w') as arq2:
            arq2.write("Tamanho,t_matvet,t_matmat\n")
            for m in lista:
                arq2.write(f"{','.join(m)}\n")


import pandas as pd
import matplotlib.pyplot as plt

arquivos = [("FLOPS_DP", "DP MFLOPS/s"), ("TIME", "TEMPO"), ("L3", "L3 bandwidth [MBytes/s]"), ("L2CACHE", "L2 miss ratio")]
for arq in arquivos:

    df = pd.read_csv(f"{arq[0]}.csv")

    plt.figure(figsize=(10, 3.7))
    plt.plot(df["Tamanho"], df["t_matmat"], 'r', label="ColunaMatrizxMatriz")
    plt.plot(df["Tamanho"], df["t_matvet"], 'g', label="ColunaMatrizxVetor")
    plt.xlabel('Tamanho')
    plt.ylabel(f'{arq[1]}')
    plt.legend(loc='upper left', frameon=False)
    plt.title(f"{arq[0]}",loc='left')

    plt.savefig(f'{arq[0]}.png')

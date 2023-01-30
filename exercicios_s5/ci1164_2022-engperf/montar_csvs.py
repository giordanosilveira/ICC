
grupos = [("FLOPS_DP","\nDP MFLOP/s"), ("L2CACHE","\nL2 miss ratio"), ("L3","\nL3 bandwidth [MBytes/s]")]
tamanhos = [64, 100, 128, 1024, 2000, 2048]

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


    


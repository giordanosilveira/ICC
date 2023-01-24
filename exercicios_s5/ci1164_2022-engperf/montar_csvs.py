
saida_csv = f"L2CACHE.csv"

tamanhos = [64, 100, 128, 1024, 2000, 2048]
lista = list()
for tam in tamanhos:
    with open(f"{tam}_L2CACHE.csv", "r") as arq:
        f = arq.read()
        f = f.split(',')
        lista.append([f[i + 1] for i, elemento in enumerate(f) if elemento == '\nRuntime (RDTSC) [s]'])
    lista[len(lista) - 1].insert(0, f"{tam}")

with open(saida_csv, 'w') as arq2:
        arq2.write("Tamanho,t_matvet,t_matmat\n")
        for m in lista:
            arq2.write(f"{','.join(m)}\n")


    


    


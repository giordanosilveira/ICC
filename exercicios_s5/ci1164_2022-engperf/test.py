import os

os.system("make")

params_likwid = ["FLOPS_DP", "L2CACHE", "L3"]
tam = [64, 100, 128, 1024, 2000, 2048]
for k in tam:
    for i in params_likwid:
        os.system(f"likwid-perfctr -O -C 3 -g {i} -m ./matmult -n {k} > {k}_{i}.csv")

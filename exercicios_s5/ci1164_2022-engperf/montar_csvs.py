import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mpl

df = pd.read_csv("FLOPS_DP.csv")

plt.figure(figsize=(10, 3.7))
plt.plot(df["Tamanho"], df["t_matmat"], 'r', label="ColunaMatrizxMatriz")
plt.plot(df["Tamanho"], df["t_matvet"], 'g', label="ColunaMatrizxVetor")
plt.xlabel('x label')
plt.ylabel('y label')
plt.legend(loc='upper left', frameon=False)
plt.title("L2CACHE",loc='left')

plt.savefig('L2CACHE.png')

    


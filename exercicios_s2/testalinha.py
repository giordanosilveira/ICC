
linha = input()
lista = linha.replace("  ", ",").split(",")
print(lista)
lista = [float(num) for num in lista]
print(lista)

resposta = input()
resposta = resposta.replace("   ", " ").replace("  ", " ").replace(" ", ",").split(",")
print(resposta)
resposta.remove('')
resposta = [float(num) for num in resposta]

soma = 0.0
for i in range(0, len(resposta)):
    soma = soma + lista[i]*resposta[i]
    print(soma)
    
print(soma)
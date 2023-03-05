import math

# Usar vetor de notas, mudar quantia para usá-la em moedas (tem 1 real)

def calcular_quantidade_notas(quantia, nota_inicial):
    if int(float(nota_inicial)) == 1:
        return
    quantidade_notas = int(quantia) // int(float(nota_inicial))
    print(str(quantidade_notas) + " notas(s) de R$ " + str(nota_inicial))
    
    quantia = quantia - (quantidade_notas * float(nota_inicial))
    nota_inicial = int(float(nota_inicial)) // 2
    nota_inicial = "{:.2f}".format(nota_inicial)
    
    calcular_quantidade_notas(quantia, nota_inicial)
    
def calcular_quantidade_moedas(quantia, lista_moedas, index_moeda):
    if len(lista_moedas) == index_moeda:
        return
    
    quantidade_moedas = 0
    
    while((quantia - lista_moedas[index_moeda]) >= 0):
        quantidade_moedas += 1
        quantia = quantia - lista_moedas[index_moeda]
    
    print(str(quantidade_moedas) + " moeda(s) de R$ " + str(lista_moedas[index_moeda]))
    
    index_moeda += 1
    
    calcular_quantidade_moedas(quantia, lista_moedas, index_moeda)

def main():
    quantia = float("{:.2f}".format(float(input())))
    nota_inicial = "{:.2f}".format(float(100))
    lista_moedas = [1, 0.5, 0.25, 0.1, 0.05, 0.01]
    index_moeda = 0
    parte_decimal = quantia % 1
    
    print("NOTAS:")
    calcular_quantidade_notas(quantia, nota_inicial)
    print("MOEDAS:")
    calcular_quantidade_moedas(parte_decimal, lista_moedas, index_moeda)

if __name__ == "__main__":
    main()
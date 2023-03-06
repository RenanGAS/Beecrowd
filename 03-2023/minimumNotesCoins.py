def main():
    quantia = float(input())
    lista_notas = [100, 50, 20, 10, 5, 2]
    lista_moedas = [1, 0.5, 0.25, 0.1, 0.05, 0.01]

    print("NOTAS:")
    for nota in lista_notas:
        quantidade_notas = int(quantia) // nota
        print(str(quantidade_notas) + " nota(s) de R$ " + "{:.2f}".format(float(nota)))
        quantia = quantia - (quantidade_notas * nota)

    print("MOEDAS:")
    for moeda in lista_moedas:
        quantidade_moedas = 0
        while((round(quantia, 2) - moeda) >= 0):
            quantidade_moedas += 1
            quantia = quantia - moeda
        print(str(quantidade_moedas) + " moeda(s) de R$ " + "{:.2f}".format(float(moeda)))

if __name__ == "__main__":
    main()
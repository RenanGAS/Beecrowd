numero = int(input())
while numero >= 10:
    print(numero)
    numero = numero// 10 * 3+ numero % 10
print(numero)
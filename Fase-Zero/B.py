grafos, dinamica, geometria = [int(entrada) for entrada in input().split()]
# 3 questões de grafos (do tipo A) custam o mesmo que 2 questões de programação dinâmica (do tipo B);
# 2 questões de geometria (do tipo C) custam o mesmo que 5 questões de grafos.

preferencia = input()
questoes_desejadas = 0
peso_total = grafos * 15 + dinamica * 10 + geometria * 6
if preferencia == "A":
    questoes_desejadas = grafos + (dinamica * 3)/2.0 + (geometria * 5)/2.0
elif preferencia == "B":
    questoes_desejadas = (grafos*2)/3.0 + dinamica + (((geometria * 5)/2.0)*2)/3.0
else:
    questoes_desejadas = (grafos*2)/5.0 + (((dinamica * 3)/2.0)*2)/5.0 + geometria


# raciocino pra pegar o número certo numa troca de verdade
'''
peso_total = ((15 * grafos) + (6 * geometria)+ (10 * dinamica))
if preferencia == "A":
    questoes_desejadas += 3 * (dinamica // 2)
    questoes_desejadas += grafos
    questoes_desejadas += 5 * (geometria // 2)
elif preferencia == "B":
    questoes_desejadas += 2 * (grafos // 3)
    questoes_desejadas += dinamica
    questoes_desejadas += 5 * (geometria // 3)
else:
    questoes_desejadas += geometria
    questoes_desejadas += 2 * (grafos // 5)
    questoes_desejadas += 3 * (dinamica // 5)
'''
print(int(questoes_desejadas))
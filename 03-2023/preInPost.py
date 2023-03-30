def call_recursion(pre_order, in_order, i_in, f_in, i_pre):
  if i_in >= f_in:
    if i_in == f_in:
      print(in_order[i_in], end="")
    elif i_in == len(in_order):
      print(in_order[f_in], end="")
    elif f_in < 0:
      print(in_order[i_in], end="")
    return

  raiz = pre_order[i_pre]

  pos_raiz_in = 0

  for j in range(i_in, f_in + 1):
    if in_order[j] == raiz:
      pos_raiz_in = j

  numero_nos_esquerda = pos_raiz_in - 1

  i_esq_pre = i_pre + 1
  f_esq_pre = i_esq_pre + numero_nos_esquerda

  i_dir_pre = f_esq_pre + 1

  # Left Tree
  call_recursion(pre_order, in_order, i_in, pos_raiz_in - 1, i_esq_pre)

  # Right Tree
  call_recursion(pre_order, in_order, pos_raiz_in + 1, f_in, i_dir_pre)

  print(raiz, end="")


def wrapper(pre_order, in_order, n):
  call_recursion(pre_order, in_order, 0, n - 1, 0)


def main():

  numero_testes = int(input())

  for i in range(numero_testes):
    n, pre_order, in_order = input().split()
    numero_nos = int(n)

    wrapper(pre_order, in_order, numero_nos)
    print("")


if __name__ == "__main__":
  main()

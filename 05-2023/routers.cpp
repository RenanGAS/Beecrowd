#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <limits.h>
#include <fstream>

using namespace std;

void mostrarMap(unordered_map<int, unordered_map<int, int>> &map_roteadores)
{
    for (auto it = map_roteadores.begin(); it != map_roteadores.end(); ++it)
    {
        cout << "rot: " << it->first << " ";

        for (auto it1 = map_roteadores.at(it->first).begin(); it1 != map_roteadores.at(it->first).end(); ++it1)
        {
            cout << "-> (" << it1->first << ", " << it1->second << ") ";
        }

        cout << "\n";
    }
}

void mostrarVetorCustos(vector<int> &custos_minimos)
{
    cout << "\n";
    for (auto it = custos_minimos.begin(); it != custos_minimos.end(); it++)
    {
        int pos = it - custos_minimos.begin();
        cout << "no: " << pos + 1 << " custo: " << *it << "\n";
    }
}

void adicionarAdjacencia(unordered_map<int, unordered_map<int, int>> &map_roteadores, int rot_x, int rot_y, int custo)
{
    map_roteadores.at(rot_x).emplace(rot_y, custo);
    map_roteadores.at(rot_y).emplace(rot_x, custo);
}

void algoritmo(unordered_map<int, unordered_map<int, int>> &map_roteadores, int num_roteadores)
{
    vector<int> custos_minimos(num_roteadores, INT_MAX);
    custos_minimos.at(0) = 0;

    vector<char> vetor_cor(num_roteadores, 'B');

    for (int i = 0; i < num_roteadores; i++)
    {
        if (vetor_cor.at(i) == 'B')
        {
            stack<int> pilha;
            pilha.push(i);
            vetor_cor.at(i) = 'P';

            while (!pilha.empty())
            {
                int rot_pilha = pilha.top();
                pilha.pop();

                cout << "Estamos em: " << rot_pilha + 1 << "\n";

                for (auto it = map_roteadores.at(rot_pilha).begin(); it != map_roteadores.at(rot_pilha).end(); ++it)
                {
                    if (vetor_cor.at(it->first) == 'B')
                    {
                        cout << "Passando por: " << it->first + 1 << "\n";
                        if (custos_minimos.at(it->first) > it->second)
                        {
                            custos_minimos.at(it->first) = it->second;
                        }
                    }
                }

                int menor = INT_MAX;
                int proximo_rot = -1;

                for (auto it = custos_minimos.begin(); it != custos_minimos.end(); ++it)
                {
                    int pos = it - custos_minimos.begin();
                    if (vetor_cor.at(pos) == 'B')
                    {
                        if (*it < menor)
                        {
                            menor = *it;
                            proximo_rot = pos;
                        }
                    }
                }

                mostrarVetorCustos(custos_minimos);

                if (proximo_rot != -1)
                {
                    cout << "Vai para: " << proximo_rot + 1 << "\n";
                    pilha.push(proximo_rot);
                }

                vetor_cor.at(rot_pilha) = 'P';
            }
        }
    }

    int soma = 0;

    for (auto it = custos_minimos.begin(); it != custos_minimos.end(); ++it)
    {
        soma += *it;
    }

    cout << soma << "\n";
    // mostrarVetorCustos(custos_minimos);
}

int main()
{
    // Ver se o problema tá quando empata os valores dos caminhos, temos que olhar pra frente e ver o melhor como no djisktra

    ifstream infile;
    infile.open("05-2023/routers.txt");

    int num_roteadores, num_cabos;

    while (infile >> num_roteadores >> num_cabos)
    {
        unordered_map<int, unordered_map<int, int>> map_roteadores;

        for (int i = 0; i < num_roteadores; i++)
        {
            unordered_map<int, int> roteadores_conectados;
            map_roteadores.emplace(i, roteadores_conectados);
        }

        for (int i = 0; i < num_cabos; i++)
        {
            int rot_x, rot_y, custo;
            infile >> rot_x >> rot_y >> custo;

            adicionarAdjacencia(map_roteadores, rot_x - 1, rot_y - 1, custo);
        }

        mostrarMap(map_roteadores);

        algoritmo(map_roteadores, num_roteadores); // prim
    }

    return 0;
}
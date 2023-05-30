#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits.h>
#include <stack>

using namespace std;

void mostrarMap(unordered_map<int, unordered_map<int, int>> &umap_tribo)
{
    for (auto it = umap_tribo.begin(); it != umap_tribo.end(); ++it)
    {
        cout << "oca: " << it->first << " ";

        for (auto it1 = umap_tribo[it->first].begin(); it1 != umap_tribo[it->first].end(); ++it1)
        {
            cout << "-> (" << it1->first << ", " << it1->second << ") ";
        }

        cout << "\n";
    }
}

void mostrarVetorCustosMinimos(vector<int> &custos_minimos)
{
    for (auto it = custos_minimos.begin(); it != custos_minimos.end(); ++it)
    {
        int pos = it - custos_minimos.begin();

        cout << "pos: " << pos << " custo: " << *it << "\n";
    }
}

void algoritmo(unordered_map<int, unordered_map<int, int>> &umap_tribo, int numero_ocas)
{
    vector<int> custos_minimos(numero_ocas, INT_MAX);

    custos_minimos.at(0) = 0;

    vector<char> vector_cor(numero_ocas, 'B');

    for (int i = 0; i < numero_ocas; i++)
    {
        if (vector_cor[i] == 'B')
        {
            stack<int> stack_ocas;
            stack_ocas.push(i);
            vector_cor[i] = 'P';

            while (!stack_ocas.empty())
            {
                int visitar_oca = stack_ocas.top();
                stack_ocas.pop();

                for (auto it = umap_tribo.at(visitar_oca).begin(); it != umap_tribo.at(visitar_oca).end(); ++it)
                {
                    if (vector_cor[it->first] == 'B')
                    {
                        if (custos_minimos[it->first] > it->second)
                        {
                            custos_minimos[it->first] = it->second;
                        }
                    }
                }

                int menor_custo = INT_MAX;
                int oca_menor_custo = -1;

                for (auto it = custos_minimos.begin(); it != custos_minimos.end(); ++it)
                {
                    int pos = it - custos_minimos.begin();

                    if (vector_cor[pos] == 'B')
                    {
                        if (*it < menor_custo)
                        {
                            menor_custo = *it;
                            oca_menor_custo = pos;
                        }
                    }
                }

                if (oca_menor_custo != -1)
                {
                    stack_ocas.push(oca_menor_custo);
                }

                vector_cor[visitar_oca] = 'P';
            }
        }
    }

    mostrarVetorCustosMinimos(custos_minimos);

    for (int i = numero_ocas - 1; i >= 0; i--)
    {
        for (auto it = umap_tribo.at(i).begin(); it != umap_tribo.at(i).end(); ++it)
        {
            if (custos_minimos[it->first] == it->second && i < it->first)
            {
                printf("\n%d, %d\n", i + 1, it->first + 1);
            }
        }
    }
}

int main()
{
    ifstream infile;
    infile.open("05-2023/optimalNet.txt");

    int numero_ocas, numero_conexoes;

    while (infile >> numero_ocas >> numero_conexoes)
    {
        if (numero_ocas == 0)
        {
            break;
        }

        unordered_map<int, unordered_map<int, int>> umap_tribo;

        for (int i = 0; i < numero_ocas; i++)
        {
            unordered_map<int, int> adjacentes;
            umap_tribo.emplace(i, adjacentes);
        }

        for (int i = 0; i < numero_conexoes; i++)
        {
            int oca_x, oca_y, custo;
            infile >> oca_x >> oca_y >> custo;

            umap_tribo[oca_x - 1].emplace(oca_y - 1, custo);
            umap_tribo[oca_y - 1].emplace(oca_x - 1, custo);
        }

        algoritmo(umap_tribo, numero_ocas);

        mostrarMap(umap_tribo);
    }

    return 0;
}
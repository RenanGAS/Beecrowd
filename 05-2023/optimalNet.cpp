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

        for (auto it1 = umap_tribo.at(it->first).begin(); it1 != umap_tribo.at(it->first).end(); ++it1)
        {
            cout << "-> (" << it1->first << ", " << it1->second << ") ";
        }

        cout << "\n";
    }
}

void mostrarConexoes(unordered_map<int, pair<int, int>> &umap_conexoes)
{
    for (auto it = umap_conexoes.begin(); it != umap_conexoes.end(); ++it)
    {
        cout << "oca_x: " << it->first << " oca_y: " << it->second.first << " custo: " << it->second.second << "\n";
    }
}

void adicionarAdjacencia(unordered_map<int, unordered_map<int, int>> &umap_tribo, int oca_x, int oca_y, int custo)
{
    cout << "adj:" << oca_x << oca_y << "\n";
    umap_tribo.at(oca_x).emplace(oca_y, custo);
    umap_tribo.at(oca_y).emplace(oca_x, custo);
}

void algoritmo(unordered_map<int, unordered_map<int, int>> &umap_tribo, int numero_ocas)
{
    unordered_map<int, pair<int , int>> umap_conexoes;
    vector<char> vector_cor(numero_ocas, 'B');
    stack<int> stack_ocas;
    stack_ocas.push(0);
    vector_cor.at(0) = 'P';

    // Talvez não tá passando por ocas que acabam ficando isoladas

    while (!stack_ocas.empty())
    {
        int visitar_oca = stack_ocas.top();
        stack_ocas.pop();

        int menor_custo = INT_MAX;
        int oca_menor_custo = 0;

        for (auto it = umap_tribo.at(visitar_oca).begin(); it != umap_tribo.at(visitar_oca).end(); ++it)
        {
            if (vector_cor.at(it->first) == 'B')
            {
                if (it->second <= menor_custo)
                {   
                    menor_custo = it->second;
                    oca_menor_custo = it->first;
                }
            }
        }

        if (oca_menor_custo != 0)
        {
            umap_conexoes.emplace(visitar_oca, make_pair(oca_menor_custo, menor_custo));
            stack_ocas.push(oca_menor_custo);
            vector_cor.at(oca_menor_custo) = 'P';
        }
    }

    mostrarConexoes(umap_conexoes);
}

int main()
{
    ifstream infile;
    infile.open("05-2023/optimalNet.txt");

    int numero_ocas, numero_conexoes;

    while (infile >> numero_ocas >> numero_conexoes && numero_ocas != 0)
    {
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

            adicionarAdjacencia(umap_tribo, oca_x - 1, oca_y - 1, custo);
        }
        mostrarMap(umap_tribo);
        algoritmo(umap_tribo, numero_ocas);
    }

    return 0;
}
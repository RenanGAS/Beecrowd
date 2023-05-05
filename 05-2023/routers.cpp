#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <limits.h>

using namespace std;

void adicionarAdjacencia(unordered_map<int, unordered_map<int, int>> &map_roteadores, int rot_x, int rot_y, int cost)
{
    map_roteadores.at(rot_x).emplace(rot_y, cost);
}

int main()
{
    int num_roteadores, num_cabos;

    while (cin >> num_roteadores >> num_cabos)
    {
        unordered_map<int, unordered_map<int, int>> map_roteadores;

        for (int i = 0; i < num_roteadores; i++)
        {
            unordered_map<int, int> roteadores_conectados;
            map_roteadores.emplace(i, roteadores_conectados);
        }
    }

    return 0;
}
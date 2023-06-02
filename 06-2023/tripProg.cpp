#include <ostream>
#include <limits.h>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

void mostrarGrafo(map<int, list<pair<int, int>>> &map_)
{
    printf("\n");

    for (auto it = map_.cbegin(); it != map_.cend(); ++it)
    {
        printf("%d ", it->first);

        for (auto it1 = it->second.cbegin(); it1 != it->second.cend(); ++it1)
        {
            printf("-> (%d, %d) ", it1->first, it1->second);
        }

        printf("\n");
    }

    printf("\n");
}

void mostrarPesos(vector<int> &vetor_w)
{
    printf("\n");

    for (auto it = vetor_w.cbegin(); it != vetor_w.cend(); ++it)
    {
        int pos = it - vetor_w.cbegin();
        printf("pos: %d w: %d\n", pos, *it);
    }
    printf("\n");
}

void addAdj(map<int, list<pair<int, int>>> &map_, int e1, int e2, int w)
{
    map_.at(e1).push_back(make_pair(e2, w));
    map_.at(e2).push_back(make_pair(e1, w));
}

int extrai_min(list<int> &lista_v, vector<int> &vetor_w)
{
    int v_min = 0;
    int w_min = INT_MAX;

    for (auto it = lista_v.cbegin(); it != lista_v.cend(); ++it)
    {
        if (w_min > vetor_w[*it])
        {
            v_min = *it;
            w_min = vetor_w[*it];
        }
    }

    lista_v.remove(v_min);
    return v_min;
}

void dijkstra(map<int, list<pair<int, int>>> &map_, int num_v, int dest)
{
    list<int> lista_v;
    vector<int> vetor_w;
    vector<int> vetor_p;

    for (int k = 0; k < num_v; k++)
    {
        vetor_w.push_back(INT_MAX);
        lista_v.push_back(k);
        vetor_p.push_back(k);
    }

    vetor_w[0] = 0;

    while (!lista_v.empty())
    {
        int prox_v = extrai_min(lista_v, vetor_w);
        
        for (auto it = map_.at(prox_v).cbegin(); it != map_.at(prox_v).cend(); ++it)
        {   
            if (vetor_w[it->first] > vetor_w[prox_v] + it->second)
            {
                vetor_w[it->first] = vetor_w[prox_v] + it->second;
                vetor_p[it->first] = prox_v;
            }
        }
    }

    int w_dest = vetor_w[dest];

    if (w_dest <= 120)
    {
        printf("Will not be late. Travel time - %d - best way - %d", w_dest, dest + 1);
    }
    else
    {
        printf("It will be %d minutes late. Travel time - %d - best way - %d", w_dest - 120, w_dest, dest + 1);
    }

    int v = dest;

    while (vetor_w[v] != 0)
    {
        v = vetor_p[v];
        printf(" %d", v + 1);
    }
    printf("\n");
}

int main()
{
    ifstream infile;
    infile.open("06-2023/tripProg.txt");

    int num_v, num_e;

    while (infile >> num_v >> num_e)
    {
        if (num_v == 0)
        {
            break;
        }

        map<int, list<pair<int, int>>> map_;

        for (int i = 0; i < num_v; i++)
        {
            list<pair<int, int>> list_adj;
            map_.emplace(i, list_adj);
        }

        for (int j = 0; j < num_e; j++)
        {
            int e1, e2, w;

            infile >> e1 >> e2 >> w;

            addAdj(map_, e1 - 1, e2 - 1, w);
        }

        int dest;

        infile >> dest;

        dijkstra(map_, num_v, dest - 1);
    }

    return EXIT_SUCCESS;
}
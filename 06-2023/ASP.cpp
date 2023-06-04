#include <ostream>
#include <limits.h>
#include <fstream>
#include <map>
#include <list>
#include <vector>

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

void mostrarGrafoInv(map<int, list<pair<int, int>>> &mapInvertido)
{
    printf("\n");

    for (auto it = mapInvertido.cbegin(); it != mapInvertido.cend(); ++it)
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

    if (w_min == INT_MAX)
    {
        return -1;
    }

    lista_v.remove(v_min);
    return v_min;
}

void dijkstra(map<int, list<pair<int, int>>> &map_, int num_v, int src, int dest)
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

    vetor_w[src] = 0;

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

    map<int, list<pair<int, int>>> map_inv_;

    for (int i = 0; i < num_v; i++)
    {
        list<pair<int, int>> list_adj;
        map_inv_.emplace(i, list_adj);
    }

    for (auto it = map_.cbegin(); it != map_.cend(); ++it)
    {
        for (auto it1 = it->second.cbegin(); it1 != it->second.cend(); ++it1)
        {
            map_inv_.at(it1->first).push_back(make_pair(it->first, it1->second));
        }
    }

    //mostrarGrafoInv(map_inv_);

    for (auto it = map_inv_.at(dest).begin(); it != map_inv_.at(dest).end(); ++it)
    {
        //printf("\npassando por: %d", it->first);

        if (vetor_w[it->first] + it->second == vetor_w[dest])
        {
            //printf("\nno: %d", it->first);

            int v = it->first;

            //printf("\nremovendo: %d ---%d--- %d", dest, it->second, it->first);
            it = map_inv_.at(dest).erase(it);

            while (vetor_w[v] != 0)
            {
                int v_ant = vetor_p[v];

                for (auto it1 = map_inv_.at(v).begin(); it1 != map_inv_.at(v).end(); ++it1)
                {
                    if (it1->first == v_ant)
                    {
                        //printf("\nremovendo: %d ---%d--- %d", v, it1->second, it1->first);
                        it1 = map_inv_.at(v).erase(it1);
                    }
                }

                v = v_ant;
            }

            //printf("\n");
        }

        //mostrarGrafoInv(map_inv_);
        //mostrarPesos(vetor_w);
    }

    //mostrarGrafoInv(map_inv_);

    list<int> lista_v_inv;
    vector<int> vetor_w_inv;

    for (int k = 0; k < num_v; k++)
    {
        vetor_w_inv.push_back(INT_MAX);
        lista_v_inv.push_back(k);
    }

    vetor_w_inv[dest] = 0;

    while (!lista_v_inv.empty())
    {
        int prox_v = extrai_min(lista_v_inv, vetor_w_inv);

        if (prox_v == -1)
        {
            break;
        }

        //printf("\nprox_v: %d", prox_v);

        for (auto it = map_inv_.at(prox_v).cbegin(); it != map_inv_.at(prox_v).cend(); ++it)
        {
            //printf("\nelem: (%d, %d)", it->first, it->second);
            if (vetor_w_inv[it->first] > vetor_w_inv[prox_v] + it->second)
            {
                vetor_w_inv[it->first] = vetor_w_inv[prox_v] + it->second;
            }
        }
    }

    if (vetor_w_inv[src] == INT_MAX)
    {
        printf("%d\n", -1);
    }
    else
    {
        printf("%d\n", vetor_w_inv[src]);
    }
}

int main()
{
    ifstream infile;
    infile.open("06-2023/ASP.txt");

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

        int src, dest;

        infile >> src >> dest;

        for (int i = 0; i < num_e; i++)
        {
            int e1, e2, w;

            infile >> e1 >> e2 >> w;

            addAdj(map_, e1, e2, w);
        }

        // mostrarGrafo(map_);

        dijkstra(map_, num_v, src, dest);
    }

    return EXIT_SUCCESS;
}
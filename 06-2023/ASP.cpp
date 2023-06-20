#include <ostream>
#include <limits.h>
#include <fstream>
#include <map>
#include <list>
#include <vector>

#define MAX 3000

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
    int w_min = MAX;

    for (auto it = lista_v.begin(); it != lista_v.end(); ++it)
    {
        if (w_min > vetor_w[*it])
        {
            v_min = *it;
            w_min = vetor_w[*it];
        }
    }

    //printf("\nvetor_w[*it]: %d it: %d", w_min, v_min);

    if (w_min == MAX)
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

    for (int i = 0; i < num_v; i++)
    {
        vetor_w.push_back(MAX);
        lista_v.push_back(i);
        vetor_p.push_back(i);
    }

    vetor_w[src] = 0;

    while (!lista_v.empty())
    {
        int prox_v = extrai_min(lista_v, vetor_w);

        if (prox_v == -1)
        {
            // printf("%d\n", -1);
            // //mostrarPesos(vetor_w);
            // return;

            break;
        }

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

    for (int j = 0; j < num_v; j++)
    {
        list<pair<int, int>> list_adj;
        map_inv_.emplace(j, list_adj);
    }

    for (auto it1 = map_.cbegin(); it1 != map_.cend(); ++it1)
    {
        for (auto it2 = it1->second.cbegin(); it2 != it1->second.cend(); ++it2)
        {
            map_inv_.at(it2->first).push_back(make_pair(it1->first, it2->second));
        }
    }

    //mostrarGrafoInv(map_inv_);

    for (auto it3 = map_inv_.at(dest).begin(); it3 != map_inv_.at(dest).end(); ++it3)
    {
        //printf("\npassando por: %d", it3->first);

        if (vetor_w[it3->first] + it3->second == vetor_w[dest])
        {
            //printf("\nno: %d", it3->first);

            int v = it3->first;

            //printf("\nremovendo: %d ---%d--- %d", dest, it3->second, it3->first);
            it3 = map_inv_.at(dest).erase(it3);
            it3--;

            while (vetor_w[v] != 0)
            {
                int v_ant = vetor_p[v];

                for (auto it4 = map_inv_.at(v).begin(); it4 != map_inv_.at(v).end(); ++it4)
                {
                    if (it4->first == v_ant && (vetor_w[v] - it4->second == vetor_w[it4->first]))
                    {
                        //printf("\nremovendo: %d ---%d--- %d", v, it4->second, it4->first);
                        it4 = map_inv_.at(v).erase(it4);
                        it4--;
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
        vetor_w_inv.push_back(MAX);
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

        for (auto it = map_inv_.at(prox_v).cbegin(); it != map_inv_.at(prox_v).cend(); ++it)
        {
            //printf("\nelem: (%d, %d)", it->first, it->second);
            if (vetor_w_inv[it->first] > vetor_w_inv[prox_v] + it->second)
            {
                vetor_w_inv[it->first] = vetor_w_inv[prox_v] + it->second;
            }
        }
    }

    if (vetor_w_inv[src] == MAX)
    {
        printf("%d\n", -1);

        //mostrarPesos(vetor_w_inv);
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
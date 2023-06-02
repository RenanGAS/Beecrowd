#include <ostream>
#include <limits.h>
#include <fstream>
#include <map>
#include <list>
#include <vector>

using namespace std;

int num_elem;
// map<int, list<pair<int, int>> *> map_;
map<int, list<pair<int, int>>> map_;

void mostrarGrafo()
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

void addAdj(int e1, int e2, int w)
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

void dijkstra(int num_v)
{
    list<int> lista_v;
    vector<int> vetor_w;

    for (int i = 0; i < num_v; i++)
    {
        vetor_w.push_back(INT_MAX);
        lista_v.push_back(i);
    }

    vetor_w[0] = 0;

    while (!lista_v.empty())
    {
        int prox_v = extrai_min(lista_v, vetor_w);

        printf("prox_v = %d\n", prox_v);

        for (auto it = map_.at(prox_v).cbegin(); it != map_.at(prox_v).cend(); ++it)
        {
            if (vetor_w[it->first] > vetor_w[prox_v] + it->second)
            {
                printf("Relaxamento:\n");
                printf("%d > %d\n", vetor_w[it->first], vetor_w[prox_v] + it->second);
                
                vetor_w[it->first] = vetor_w[prox_v] + it->second;
            }
        }

        mostrarPesos(vetor_w);
    }

    int max_w = 0;

    for (int i = 1; i < num_v; i++)
    {
        if (max_w < vetor_w[i])
        {
            max_w = vetor_w[i];
        }
    }

    printf("\n%d\n", max_w);
}

int main()
{
    ifstream infile;
    infile.open("06-2023/meeting.txt");

    int num_v, num_e;

    num_elem = 0;

    while (infile >> num_v >> num_e)
    {
        // if (num_v > num_elem && !num_elem)
        // {
        //     for (int i = num_elem; i < num_v; i++)
        //     {
        //         list<pair<int, int>> *list_adj = (list<pair<int, int>> *)malloc(sizeof(list<pair<int, int>> *));
        //         map_.emplace(i, list_adj);
        //     }

        //     num_elem = num_v;
        // }

        for (int i = 0; i < num_v; i++)
        {
            list<pair<int, int>> list_adj;
            map_.emplace(i, list_adj);
        }

        for (int i = 0; i < num_e; i++)
        {
            int e1, e2, w;

            infile >> e1 >> e2 >> w;

            addAdj(e1, e2, w);
        }

        mostrarGrafo();

        dijkstra(num_v);

        // for (int i = 0; i < num_v; i++)
        // {
        //     free(&map_.at(i));
        // }
    }

    return EXIT_SUCCESS;
}
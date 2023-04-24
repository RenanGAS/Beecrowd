#include <iostream>
#include <vector>

using namespace std;

class Vertice
{
public:
    char *id;
    vector<int> *vetor_conexoes;

    Vertice(char id, int num_vertices)
    {
        this->id = new char(id);
        this->vetor_conexoes = new vector<int>(num_vertices, 0);
    }
};

class DFS
{
public:
    int *num_vertices;
    vector<Vertice *> *vetor_vertice;
    vector<char> *vetor_cor;
    int *num_componentes;

    DFS(int num_vertices)
    {
        this->num_vertices = new int(num_vertices);
        this->vetor_vertice = new vector<Vertice *>(num_vertices, NULL);
        this->vetor_cor = new vector<char>(num_vertices, 'B');
        this->num_componentes = new int(0);

        for (int i = 0; i < num_vertices; i++)
        {
            char letra = i + 97;
            this->vetor_vertice->at(i) = new Vertice(letra, num_vertices);
        }
    }

    // void mostrarVetorVertice()
    // {
    //     cout << "Vetor Vertice:\n\n";

    //     for (auto it1 = this->vetor_vertice->begin();
    //          it1 != this->vetor_vertice->end(); ++it1)
    //     {
    //         cout << "\n"
    //              << *(*it1)->id << " -> ";
    //         for (Vertice *it2 = (*it1)->proximo; it2 != NULL; it2 = it2->proximo)
    //         {
    //             cout << *it2->id << " -> ";
    //         }
    //     }
    // }

    void adicionarAdjacencia(char id_x, char id_y)
    {
        this->vetor_vertice->at(id_x - 97)->vetor_conexoes->at(id_y - 97) = 1;
        this->vetor_vertice->at(id_y - 97)->vetor_conexoes->at(id_x - 97) = 1;
    }

    void algoritmo()
    {
        for (auto it = this->vetor_vertice->begin();
             it != this->vetor_vertice->end(); ++it)
        {
            if (this->vetor_cor->at(*(*it)->id - 97) == 'B')
            {
                *this->num_componentes += 1;
                cout << "\n"
                     << *(*it)->id << ",";
                visitar(*(*it)->id);
            }
        }
    }

    void visitar(char id)
    {
        this->vetor_cor->at(id - 97) = 'C';

        for (int i = 0; i < *this->num_vertices; i++)
        {
            if (this->vetor_vertice->at(id - 97)->vetor_conexoes->at(i) == 1)
            {
                if (this->vetor_cor->at(i) == 'B')
                {
                    char letra = i + 97;
                    cout << letra << ",";
                    visitar(letra);
                }
            }
        }

        this->vetor_cor->at(id - 97) = 'P';
    }
};

int main()
{
    int num_testes;
    int num_vertices, num_arestas;

    cin >> num_testes;

    for (int i = 0; i < num_testes; i++)
    {
        cin >> num_vertices >> num_arestas;

        DFS dfs = DFS(num_vertices);

        for (int i = 0; i < num_arestas; i++)
        {
            char id_x, id_y;
            cin >> id_x >> id_y;

            dfs.adicionarAdjacencia(id_x, id_y);
        }

        cout << "Case #" << i + 1 << ":";
        dfs.algoritmo();
        cout << "\n"
             << *dfs.num_componentes << " connected components\n\n";
    }

    return 0;
}
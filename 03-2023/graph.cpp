#include <iostream>
using namespace std;

class No
{
    int numero;
    int peso;
    No *proximo;

public:
    No(int numero)
    {
        this->numero = numero;
        this->peso = 0;
        this->proximo = NULL;
    }

    friend class ListaNo;
};

class ListaNo
{
    No *lista;
    int numero_nos;

public:
    ListaNo()
    {
        this->lista = (No *)malloc(sizeof(No));
        this->lista = NULL;
        this->numero_nos = 0;
    }

    void addNode(int numero_no)
    {
        No novo_no = No(numero_no);

        if (this->numero_nos == 0)
        {
            this->lista = &novo_no;
        }
        else
        {
            No *auxiliar = this->lista;
            int contador = 0;

            while (auxiliar->proximo != NULL)
            {
                auxiliar = auxiliar->proximo;
                contador++;
            }

            (lista + contador)->proximo = &novo_no;
        }

        this->numero_nos++;
    }

    bool findNode(int numero)
    {
        No *auxiliar = this->lista;

        while (auxiliar->proximo != NULL)
        {
            if (auxiliar->numero == numero)
            {
                return true;
            }

            auxiliar = auxiliar->proximo;
        }

        return false;
    }

    friend class Graph;
};

class Graph
{
    ListaNo *lista_incidencia;
    int num_vertices;

public:
    Graph(int num_vertices)
    {
        this->lista_incidencia = (ListaNo *)malloc(num_vertices * sizeof(ListaNo));
        for (int i = 0; i < this->num_vertices; i++)
        {
            this->lista_incidencia[i] = ListaNo();
        }

        this->num_vertices = num_vertices;
    }

    void addEdge(int u, int v)
    {
        this->lista_incidencia[u].addNode(v);
    }

    int getInDegree(int numero_vertice)
    {
        int contador = 0;

        for (int i = 0; i < this->num_vertices; i++)
        {
            if (this->lista_incidencia[i].findNode(numero_vertice))
            {
                contador++;
            }
        }

        return contador;
    }

    int getOutDegree(int numero_vertice)
    {
        return this->lista_incidencia[numero_vertice].numero_nos;
    }

    int getDegree(int numero_vertice)
    {
        int in = getInDegree(numero_vertice);
        int out = getOutDegree(numero_vertice);
        
        return (in + out);
    }
};

int main()
{
    Graph myGraph = Graph(1);

    myGraph.addEdge(0, 0);

    printf("%d\n", myGraph.getInDegree(0));
    printf("%d\n", myGraph.getOutDegree(0));
    printf("%d\n", myGraph.getDegree(0));

    return 0;
}
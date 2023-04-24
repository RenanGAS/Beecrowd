#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;

class Documento
{
public:
    int *id;
    Documento *proximo;

    Documento(int id)
    {
        this->id = new int(id);
        this->proximo = NULL;
    }
};

class DFS
{
public:
    int *num_documentos;
    vector<int> *vetor_inicio;
    vector<int> *vetor_fim;
    vector<Documento *> *vetor_documento;
    vector<char> *vetor_cor;
    int *tempo;

    DFS(int num_documentos)
    {
        this->num_documentos = new int(num_documentos);
        this->vetor_inicio = new vector<int>(num_documentos, -1);
        this->vetor_fim = new vector<int>(num_documentos, -1);
        this->vetor_documento = new vector<Documento *>(num_documentos, NULL);
        this->vetor_cor = new vector<char>(num_documentos, 'B');
        this->tempo = new int(0);

        for (int i = 0; i < num_documentos; i++)
        {
            this->vetor_documento->at(i) = new Documento(i);
        }
    }

    void mostrarVetorDocumento()
    {
        cout << "Vetor Documento:\n\n";

        for (auto it1 = this->vetor_documento->begin();
             it1 != this->vetor_documento->end(); ++it1)
        {
            cout << "\n"
                 << *(*it1)->id << " -> ";
            for (Documento *it2 = (*it1)->proximo; it2 != NULL; it2 = it2->proximo)
            {
                cout << *it2->id << " -> ";
            }
        }
    }

    void mostrarVetorInicio()
    {
        cout << "Vetor Inicio:\n\n";

        for (auto it = this->vetor_inicio->begin(); it != this->vetor_inicio->end();
             ++it)
        {
            int pos = it - this->vetor_inicio->begin();
            cout << "id: " << pos << " tempo: " << *it << "\n";
        }
        cout << "\n";
    }

    void mostrarVetorFim()
    {
        cout << "Vetor Fim:\n\n";

        for (auto it = this->vetor_fim->begin(); it != this->vetor_fim->end();
             ++it)
        {
            int pos = it - this->vetor_fim->begin();
            cout << "id: " << pos << " tempo: " << *it << "\n";
        }
        cout << "\n";
    }

    void adicionarAdjacencia(int id_x, int id_y)
    {
        Documento *it = NULL;
        for (it = this->vetor_documento->at(id_x); it->proximo != NULL;
             it = it->proximo)
        {
        }

        it->proximo = new Documento(id_y);
    }

    void algoritmo()
    {
        for (auto it = this->vetor_documento->begin();
             it != this->vetor_documento->end(); ++it)
        {
            if (this->vetor_cor->at(*(*it)->id) == 'B')
            {
                visitar(*(*it)->id);
            }
        }
    }

    void visitar(int id)
    {
        *this->tempo = *this->tempo + 1;
        this->vetor_inicio->at(id) = *this->tempo;
        this->vetor_cor->at(id) = 'C';

        for (Documento *it = this->vetor_documento->at(id)->proximo; it != NULL;
             it = it->proximo)
        {
            if (this->vetor_cor->at(*it->id) == 'B')
            {
                visitar(*it->id);
            }
        }

        this->vetor_cor->at(id) = 'P';
        *this->tempo = *this->tempo + 1;
        this->vetor_fim->at(id) = *this->tempo;
    }

    void verificaCiclo()
    {
        for (auto it1 = this->vetor_documento->begin();
             it1 != this->vetor_documento->end(); ++it1)
        {
            for (Documento *it2 = (*it1)->proximo; it2 != NULL; it2 = it2->proximo)
            {
                if (this->vetor_fim->at(*it2->id) > this->vetor_fim->at(*(*it1)->id))
                {
                    cout << "SIM\n";
                    return;
                }
                
            }
        }
        cout << "NAO\n";
        return;
    }
};

int main()
{
    int num_testes;
    int num_documentos, num_dependencias;

    cin >> num_testes;

    for (int i = 0; i < num_testes; i++)
    {
        cin >> num_documentos >> num_dependencias;

        DFS dfs = DFS(num_documentos);

        for (int i = 0; i < num_dependencias; i++)
        {
            int id_x, id_y;
            cin >> id_x >> id_y;

            dfs.adicionarAdjacencia(id_x - 1, id_y - 1);
        }

        dfs.algoritmo();

        dfs.verificaCiclo();
    }

    return 0;
}
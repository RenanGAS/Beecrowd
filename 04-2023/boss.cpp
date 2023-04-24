#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class Empregado
{
public:
  int *id;
  Empregado *proximo;

  Empregado(int id)
  {
    this->id = new int(id);
    this->proximo = NULL;
  }
};

class DFS
{
public:
  int *num_empregados;
  vector<int> *vetor_idade;
  vector<Empregado *> *vetor_empregado;
  vector<char> *vetor_cor;

  DFS(int num_empregados, vector<int> idade_empregados)
  {
    this->num_empregados = new int(num_empregados);
    this->vetor_idade = new vector<int>(num_empregados, 0);
    this->vetor_empregado = new vector<Empregado *>(num_empregados, NULL);
    this->vetor_cor = new vector<char>(num_empregados, 'B');

    for (int i = 0; i < num_empregados; i++)
    {
      this->vetor_idade->at(i) = idade_empregados.at(i);
    }

    for (int i = 0; i < num_empregados; i++)
    {
      this->vetor_empregado->at(i) = new Empregado(i);
    }
  }

  void mostrarVetorIdade()
  {
    cout << "Vetor Idade:\n\n";

    for (auto it = this->vetor_idade->begin(); it != this->vetor_idade->end();
         ++it)
    {
      int pos = it - this->vetor_idade->begin();
      cout << "pos: " << pos << " idade: " << *it << "\n";
    }
  }

  void mostrarVetorEmpregado()
  {
    cout << "Vetor Empregado:\n\n";

    for (auto it1 = this->vetor_empregado->begin();
         it1 != this->vetor_empregado->end(); ++it1)
    {
      cout << "\n"
           << *(*it1)->id << " -> ";
      for (Empregado *it2 = (*it1)->proximo; it2 != NULL; it2 = it2->proximo)
      {
        cout << *it2->id << " -> ";
      }
    }
  }

  void adicionarAdjacencia(int id_x, int id_y)
  {
    Empregado *it = NULL;
    for (it = this->vetor_empregado->at(id_y); it->proximo != NULL;
         it = it->proximo)
    {
    }

    it->proximo = new Empregado(id_x);
  }

  void algoritmo()
  {
    for (auto it = this->vetor_empregado->begin();
         it != this->vetor_empregado->end(); ++it)
    {
      if (this->vetor_cor->at(*(*it)->id) == 'B')
      {
        visitar(*(*it)->id);
      }
    }
  }

  void visitar(int id)
  {
    this->vetor_cor->at(id) = 'C';

    for (Empregado *it = this->vetor_empregado->at(id)->proximo; it != NULL;
         it = it->proximo)
    {
      if (this->vetor_cor->at(*it->id) == 'B')
      {
        visitar(*it->id);
      }
    }

    this->vetor_cor->at(id) = 'P';
  }

  void buscaGerenteMaisNovo(int id_alvo)
  {
    int idade = INT_MAX;
    int menor_idade = 0;

    menor_idade = buscaProfundidade(*this->vetor_empregado->at(id_alvo)->id, idade);
    
    if(menor_idade == idade){
      cout << "*\n";
      return;
    }

    cout << menor_idade << "\n";
    return;
  }

  int buscaProfundidade(int id_alvo, int idade)
  {
    for (Empregado *it1 = this->vetor_empregado->at(id_alvo)->proximo; it1 != NULL; it1 = it1->proximo)
    {
      int idade_proximo = this->vetor_idade->at(*it1->id);

      if (idade_proximo < idade)
      {
        idade = idade_proximo;
      }

      idade = buscaProfundidade(*it1->id, idade);
    }

    return idade;
  }

  void mudarCadeiaComando(int id_x, int id_y)
  {
    for (auto it1 = this->vetor_empregado->begin();
         it1 != this->vetor_empregado->end(); ++it1)
    {
      if (*(*it1)->id == id_x)
      {
        *(*it1)->id = id_y;
      }
      else if (*(*it1)->id == id_y)
      {
        *(*it1)->id = id_x;
      }

      for (Empregado *it2 = (*it1)->proximo; it2 != NULL; it2 = it2->proximo)
      {
        if (*it2->id == id_x)
        {
          *it2->id = id_y;
        }
        else if (*it2->id == id_y)
        {
          *it2->id = id_x;
        }
      }
    }
  }
};

int main()
{
  int num_empregados, num_dlinks, num_instrucoes;

  while (!cin.eof())
  {
    cin >> num_empregados >> num_dlinks >> num_instrucoes;

    vector<int> idade_empregados(num_empregados, 0);

    for (int i = 0; i < num_empregados; i++)
    {
      cin >> idade_empregados.at(i);
    }

    DFS dfs = DFS(num_empregados, idade_empregados);

    for (int i = 0; i < num_dlinks; i++)
    {
      int id_x, id_y;
      cin >> id_x >> id_y;

      dfs.adicionarAdjacencia(id_x - 1, id_y - 1);
    }

    for (int i = 0; i < num_instrucoes; i++)
    {
      char funcao;

      cin >> funcao;

      if (funcao == 'P')
      {
        int id;
        cin >> id;

        dfs.buscaGerenteMaisNovo(id - 1);
      }
      else if (funcao == 'T')
      {
        int id_x, id_y;
        cin >> id_x >> id_y;

        dfs.mudarCadeiaComando(id_x - 1, id_y - 1);
        dfs.mostrarVetorEmpregado();
      }
    }
  }

  return 0;
}
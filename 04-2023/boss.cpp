#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class Empregado
{
public:
  int *id;
  int *idade_mais_novo;
  Empregado *proximo;

  Empregado(int id)
  {
    this->id = new int(id);
    this->idade_mais_novo = new int(INT_MAX);
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
  int *cadeiaMudou;
  vector<int> *correspondencias_id;

  DFS(int num_empregados, vector<int> idade_empregados)
  {
    this->num_empregados = new int(num_empregados);
    this->vetor_idade = new vector<int>(num_empregados, 0);
    this->vetor_empregado = new vector<Empregado *>(num_empregados, NULL);
    this->vetor_cor = new vector<char>(num_empregados, 'B');
    this->cadeiaMudou = new int(0);
    this->correspondencias_id = new vector<int>(num_empregados, 0);

    for (int i = 0; i < num_empregados; i++)
    {
      this->vetor_idade->at(i) = idade_empregados.at(i);
      this->vetor_empregado->at(i) = new Empregado(i);
      this->correspondencias_id->at(i) = i;
    }
  }

  ~DFS(){
    for (int i = 0; i < *this->num_empregados; i++)
    {
      delete this->vetor_empregado->at(i);
    }

    delete this->num_empregados;
    delete this->vetor_idade;
    delete this->vetor_empregado;
    delete this->vetor_cor;
    delete this->cadeiaMudou;
    delete this->correspondencias_id;
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

  void algoritmo(int id_alvo)
  {
    int id_correspondente = this->correspondencias_id->at(id_alvo);

    if (*this->cadeiaMudou || this->vetor_cor->at(id_correspondente) == 'B')
    {
      int menor_idade = INT_MAX;
      menor_idade = visitar(*this->vetor_empregado->at(id_correspondente)->id, menor_idade);
      *this->vetor_empregado->at(id_correspondente)->idade_mais_novo = menor_idade;
    }

    if (*this->vetor_empregado->at(id_correspondente)->idade_mais_novo == INT_MAX)
    {
      cout << "*\n";
      return;
    }

    cout << *this->vetor_empregado->at(id_correspondente)->idade_mais_novo << "\n";

    *this->cadeiaMudou = 0;
    return;
  }

  int visitar(int id, int menor_idade)
  {
    this->vetor_cor->at(id) = 'C';

    for (Empregado *it = this->vetor_empregado->at(id)->proximo; it != NULL;
         it = it->proximo)
    {
      int id_correspondente = this->correspondencias_id->at(*it->id);

      int idade_proximo = this->vetor_idade->at(id_correspondente);

      if (menor_idade > idade_proximo)
      {
        menor_idade = idade_proximo;
      }

      menor_idade = visitar(id_correspondente, menor_idade);
    }

    this->vetor_cor->at(id) = 'P';
    return menor_idade;
  }

  void mudarCadeiaComando(int id_x, int id_y)
  {
    this->correspondencias_id->at(id_x) = id_y;
    this->correspondencias_id->at(id_y) = id_x;

    this->vetor_cor->at(id_x) = 'B';
    this->vetor_cor->at(id_y) = 'B';

    *this->cadeiaMudou = 1;
    return;
  }
};

int main()
{
  int num_empregados, num_dlinks, num_instrucoes;

  while (1)
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

        dfs.algoritmo(id - 1);
      }
      else if (funcao == 'T')
      {
        int id_x, id_y;
        cin >> id_x >> id_y;

        dfs.mudarCadeiaComando(id_x - 1, id_y - 1);
      }
    }
  }

  return 0;
}
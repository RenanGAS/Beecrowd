#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <list>
#include <limits.h>

using namespace std;

class DFS
{
public:
  int *num_empregados;
  vector<int> *vetor_idade;
  unordered_map<int, int> *umap_id_pos;
  map<int, pair<int, list<int> *>> *map_empregados;

  DFS(int num_empregados, vector<int> &idade_empregados)
  {
    this->num_empregados = new int(num_empregados);
    this->vetor_idade = new vector<int>;
    this->vetor_idade->reserve(num_empregados);
    this->umap_id_pos = new unordered_map<int, int>;
    this->map_empregados = new map<int, pair<int, list<int> *>>;

    for (int i = 0; i < num_empregados; i++)
    {
      this->vetor_idade->push_back(idade_empregados.at(i));
      this->umap_id_pos->emplace(i, i);
      list<int> *lista_adj = new list<int>;
      this->map_empregados->emplace(i, make_pair(i, lista_adj));
    }
  }

  ~DFS()
  {
    delete this->num_empregados;
    delete this->vetor_idade;
    delete this->umap_id_pos;
    delete this->map_empregados;
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

  void mostrarUmap()
  {
    cout << "Umap:\n\n";

    for (auto it = this->umap_id_pos->begin(); it != this->umap_id_pos->end();
         ++it)
    {
      cout << "id_emp: " << it->first << " pos: " << it->second << "\n";
    }
  }

  void mostrarHash()
  {
    cout << "Hash:\n\n";

    for (auto it = this->map_empregados->begin(); it != this->map_empregados->end(); it++)
    {
      cout << "pos: " << it->first << " id_emp: " << it->second.first << " list: ";
      for (auto it1 = this->map_empregados->at(it->first).second->begin(); it1 != this->map_empregados->at(it->first).second->end(); it1++)
      {
        cout << *it1 << " ";
      }
      cout << "\n";
    }
  }

  void adicionarAdjacencia(int id_x, int id_y)
  {
    this->map_empregados->at(id_y).second->push_back(id_x);
  }

  // void algoritmo(int id_alvo)
  // {
  //   int pos = this->umap_id_pos->at(id_alvo);

  //   int menor_idade = INT_MAX;

  //   menor_idade = visitar(pos, menor_idade);

  //   if (menor_idade == INT_MAX)
  //   {
  //     cout << "*\n";
  //     return;
  //   }

  //   cout << menor_idade << "\n";
  //   return;
  // }

  // int visitar(int pos, int menor_idade)
  // {
  //   for (auto it = this->map_empregados->at(pos).second->begin(); it != this->map_empregados->at(pos).second->end(); ++it){
  //     int id_correspondente = this->map_empregados->at(*it).first;

  //     int idade_proximo = this->vetor_idade->at(id_correspondente);

  //     if (menor_idade > idade_proximo)
  //     {
  //       menor_idade = idade_proximo;
  //     }

  //     menor_idade = visitar(*it, menor_idade);
  //   }

  //   return menor_idade;
  // }

  void algoritmo(int id_alvo)
  {
    int pos = this->umap_id_pos->at(id_alvo);

    int menor_idade = INT_MAX;

    stack<int> s;
    s.push(pos);

    while (!s.empty())
    {
      int curr_pos = s.top();
      s.pop();

      for (auto it = this->map_empregados->at(curr_pos).second->begin(); it != this->map_empregados->at(curr_pos).second->end(); ++it)
      {
        int id_correspondente = this->map_empregados->at(*it).first;

        int idade_proximo = this->vetor_idade->at(id_correspondente);

        if (menor_idade > idade_proximo)
        {
          menor_idade = idade_proximo;
        }

        s.push(*it);
      }
    }

    if (menor_idade == INT_MAX)
    {
      cout << "*\n";
      return;
    }

    cout << menor_idade << "\n";
    return;
  }

  void mudarCadeiaComando(int id_x, int id_y)
  {
    int antiga_pos_x = this->umap_id_pos->at(id_x);
    int antiga_pos_y = this->umap_id_pos->at(id_y);

    this->umap_id_pos->at(id_y) = antiga_pos_x;
    this->umap_id_pos->at(id_x) = antiga_pos_y;

    this->map_empregados->at(antiga_pos_x).first = id_y;
    this->map_empregados->at(antiga_pos_y).first = id_x;

    return;
  }
};

int main()
{
  int num_empregados, num_dlinks, num_instrucoes;

  while (cin.peek() != '\n' && cin >> num_empregados >> num_dlinks >> num_instrucoes)
  {
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
        dfs.mostrarUmap();
        dfs.mostrarHash();
      }
    }
    cin.ignore();
  }

  return 0;
}
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <list>
#include <limits.h>

using namespace std;

void mostrarVetorIdade(vector<int> &vetor_idade)
{
  cout << "Vetor Idade:\n\n";

  for (auto it = vetor_idade.begin(); it != vetor_idade.end();
       ++it)
  {
    int pos = it - vetor_idade.begin();
    cout << "pos: " << pos << " idade: " << *it << "\n";
  }
}

void mostrarUmap(unordered_map<int, int> &umap_id_pos)
{
  cout << "Umap:\n\n";

  for (auto it = umap_id_pos.begin(); it != umap_id_pos.end();
       ++it)
  {
    cout << "id_emp: " << it->first << " pos: " << it->second << "\n";
  }
}

void mostrarHash(map<int, pair<int, list<int>>> &map_empregados)
{
  cout << "Hash:\n\n";

  for (auto it = map_empregados.begin(); it != map_empregados.end(); it++)
  {
    cout << "pos: " << it->first << " id_emp: " << it->second.first << " list: ";
    for (auto it1 = map_empregados.at(it->first).second.begin(); it1 != map_empregados.at(it->first).second.end(); it1++)
    {
      cout << *it1 << " ";
    }
    cout << "\n";
  }
}

void adicionarAdjacencia(map<int, pair<int, list<int>>> &map_empregados, int id_x, int id_y)
{
  map_empregados.at(id_y).second.push_back(id_x);
}

void algoritmo(map<int, pair<int, list<int>>> &map_empregados, unordered_map<int, int> &umap_id_pos, vector<int> &vetor_idade, int id_alvo, int num_empregados)
{
  int pos = umap_id_pos.at(id_alvo);

  int menor_idade = 101;

  stack<int> s;
  s.push(pos);

  vector<char> vector_cor(num_empregados, 'B');

  while (!s.empty())
  {
    int curr_pos = s.top();
    s.pop();

    for (auto it = map_empregados.at(curr_pos).second.begin(); it != map_empregados.at(curr_pos).second.end(); ++it)
    {
      if (vector_cor[*it] == 'P')
      {
        continue;
      }

      vector_cor[*it] = 'P';

      int id_correspondente = map_empregados.at(*it).first;

      int idade_proximo = vetor_idade.at(id_correspondente);

      if (menor_idade > idade_proximo)
      {
        menor_idade = idade_proximo;
      }

      s.push(*it);
    }
  }

  if (menor_idade == 101)
  {
    cout << "*\n";
    return;
  }

  cout << menor_idade << "\n";
  return;
}

void mudarCadeiaComando(map<int, pair<int, list<int>>> &map_empregados, unordered_map<int, int> &umap_id_pos, int id_x, int id_y)
{
  int antiga_pos_x = umap_id_pos.at(id_x);
  int antiga_pos_y = umap_id_pos.at(id_y);

  umap_id_pos.at(id_y) = antiga_pos_x;
  umap_id_pos.at(id_x) = antiga_pos_y;

  map_empregados.at(antiga_pos_x).first = id_y;
  map_empregados.at(antiga_pos_y).first = id_x;

  return;
}

int main()
{
  int num_empregados, num_dlinks, num_instrucoes;

  while (cin.peek() != '\n' && cin >> num_empregados >> num_dlinks >> num_instrucoes)
  {
    vector<int> idade_empregados(num_empregados, 0);
    unordered_map<int, int> umap_id_pos;
    map<int, pair<int, list<int>>> map_empregados;

    for (int i = 0; i < num_empregados; i++)
    {
      cin >> idade_empregados.at(i);

      umap_id_pos.emplace(i, i);
      list<int> lista_adj;
      map_empregados.emplace(i, make_pair(i, lista_adj));
    }

    for (int i = 0; i < num_dlinks; i++)
    {
      int id_x, id_y;
      cin >> id_x >> id_y;

      adicionarAdjacencia(map_empregados, id_x - 1, id_y - 1);
    }

    for (int i = 0; i < num_instrucoes; i++)
    {
      char funcao;

      cin >> funcao;

      if (funcao == 'P')
      {
        int id;
        cin >> id;

        algoritmo(map_empregados, umap_id_pos, idade_empregados, id - 1, num_empregados);
      }
      else if (funcao == 'T')
      {
        int id_x, id_y;
        cin >> id_x >> id_y;

        mudarCadeiaComando(map_empregados, umap_id_pos, id_x - 1, id_y - 1);
      }
    }
    cin.ignore();
  }

  return 0;
}
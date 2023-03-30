#include <bits/stdc++.h>

using namespace std;

class MiniChefe {
  class Rip {
  public:
    vector<int> *vetor_distancias;

    Rip(int numero_cidades) {
      this->vetor_distancias = new vector<int>(numero_cidades, 0);
    }

    vector<int> *getVetorDistancias() { return this->vetor_distancias; }
  };

private:
  int id_cidade_origem;
  int numero_cidades;
  vector<Rip> tabela_Rips;

public:
  MiniChefe(int numero_cidades, int id_cidade_origem) {
    this->numero_cidades = numero_cidades;
    this->id_cidade_origem = id_cidade_origem;
    this->tabela_Rips = vector<Rip>(numero_cidades, Rip(numero_cidades));
  }

  void comunicarConexao(int cidade_x, int cidade_y) {}
};

int main() { int numero_max_pedagios = 2; }
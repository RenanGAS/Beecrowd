#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

void mostrarGruposDisjuntos(map<int, unordered_map<int, int>> &grupos_disjuntos)
{
    cout << "\n";

    for (auto it = grupos_disjuntos.cbegin(); it != grupos_disjuntos.cend(); ++it)
    {
        cout << it->first << " -> ";
        for (auto it1 = it->second.cbegin(); it1 != it->second.cend(); ++it1)
        {
            cout << "(" << it1->first << ", " << it1->second << ") -> ";
        }

        cout << "\n";
    }
}

void adicionarElemento(map<int, unordered_map<int, int>> &grupos_disjuntos, vector<int> &tamanho_grupos, int aluno_x, int aluno_y)
{
    int grupo_x = grupos_disjuntos.at(aluno_x).at(aluno_x);
    int grupo_y = grupos_disjuntos.at(aluno_y).at(aluno_y);

    if (grupo_x != grupo_y)
    {
        if (tamanho_grupos.at(grupo_y) == 1)
        {
            grupos_disjuntos.at(grupo_y).at(grupo_y) = grupo_x;
            grupos_disjuntos.at(grupo_x).emplace(grupo_y, grupo_x);
            tamanho_grupos.at(grupo_x) += 1;
            return;
        }
        else if (tamanho_grupos.at(grupo_x) == 1)
        {
            grupos_disjuntos.at(grupo_x).at(grupo_x) = grupo_y;
            grupos_disjuntos.at(grupo_y).emplace(grupo_x, grupo_y);
            tamanho_grupos.at(grupo_y) += 1;
            return;
        }

        int novo_grupo, antigo_grupo = 0;

        if (tamanho_grupos.at(grupo_x) >= tamanho_grupos.at(grupo_y))
        {
            antigo_grupo = grupo_y;
            novo_grupo = grupo_x;
        }
        else
        {
            antigo_grupo = grupo_x;
            novo_grupo = grupo_y;
        }

        for (auto it = grupos_disjuntos.at(antigo_grupo).begin(); it != grupos_disjuntos.at(antigo_grupo).end(); ++it)
        {
            grupos_disjuntos.at(it->first).at(it->first) = novo_grupo;
            it->second = novo_grupo;
            tamanho_grupos.at(novo_grupo) += 1;
        }
    }
}

void verificarPai(map<int, unordered_map<int, int>> &grupos_disjuntos, int aluno_x, int aluno_y)
{
    if (grupos_disjuntos.at(aluno_x).at(aluno_x) == grupos_disjuntos.at(aluno_y).at(aluno_y))
    {
        cout << "S\n";
    }
    else
    {
        cout << "N\n";
    }
}

int main()
{
    ifstream infile;
    infile.open("05-2023/makePairs.txt");

    int numero_alunos, numero_amizades_diretas, numero_pares;

    while (infile >> numero_alunos >> numero_amizades_diretas >> numero_pares)
    {
        // cout << "\n";
        map<int, unordered_map<int, int>> grupos_disjuntos;
        vector<int> tamanho_grupos(numero_alunos, 1);

        for (int i = 0; i < numero_alunos; i++)
        {
            unordered_map<int, int> elementos;
            elementos.emplace(i, i);
            grupos_disjuntos.emplace(i, elementos);
        }

        for (int i = 0; i < numero_amizades_diretas; i++)
        {
            int aluno_x, aluno_y;

            infile >> aluno_x >> aluno_y;

            adicionarElemento(grupos_disjuntos, tamanho_grupos, aluno_x - 1, aluno_y - 1);
        }

        // mostrarGruposDisjuntos(grupos_disjuntos);

        for (int i = 0; i < numero_pares; i++)
        {
            int aluno_x, aluno_y;

            infile >> aluno_x >> aluno_y;

            verificarPai(grupos_disjuntos, aluno_x - 1, aluno_y - 1);
        }
    }

    return 0;
}
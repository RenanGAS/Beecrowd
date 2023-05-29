#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void mostrarGruposDisjuntos(vector<int> &grupos_disjuntos)
{
    cout << "\n";

    for (auto it = grupos_disjuntos.cbegin(); it != grupos_disjuntos.cend(); ++it)
    {
        int pos = it - grupos_disjuntos.begin();

        cout << "no: " << *it << " pai: " << pos << "\n";
    }
    cout << "\n";
}

void adicionarElemento(vector<int> &grupos_disjuntos, vector<int> &tamanho_grupos, int aluno_x, int aluno_y)
{
    int grupo_x = grupos_disjuntos.at(aluno_x);
    int grupo_y = grupos_disjuntos.at(aluno_y);

    if (grupo_x != grupo_y)
    {
        if (tamanho_grupos.at(grupo_y) == 1)
        {
            grupos_disjuntos.at(grupo_y) = grupo_x;
            tamanho_grupos.at(grupo_x) += 1;
            return;
        }
        else if (tamanho_grupos.at(grupo_x) == 1)
        {
            grupos_disjuntos.at(grupo_x) = grupo_y;
            tamanho_grupos.at(grupo_y) += 1;
            return;
        }

        int novo_grupo = -1, antigo_grupo = -1;

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

        for (auto it = grupos_disjuntos.begin(); it != grupos_disjuntos.end(); ++it)
        {
            int pos = it - grupos_disjuntos.begin();

            if (*it == antigo_grupo)
            {
                *it = novo_grupo;
                tamanho_grupos.at(novo_grupo) += 1;
            }
        }
    }
}

int main()
{
    ifstream infile;
    infile.open("05-2023/makePairs.txt");

    int numero_alunos, numero_amizades_diretas, numero_pares;

    while (infile >> numero_alunos >> numero_amizades_diretas >> numero_pares)
    {
        vector<int> grupos_disjuntos;
        vector<int> tamanho_grupos(numero_alunos, 1);

        for (int i = 0; i < numero_alunos; i++)
        {
            grupos_disjuntos.push_back(i);
        }

        for (int i = 0; i < numero_amizades_diretas; i++)
        {
            int aluno_x, aluno_y;

            infile >> aluno_x >> aluno_y;

            adicionarElemento(grupos_disjuntos, tamanho_grupos, aluno_x - 1, aluno_y - 1);
        }

        for (int i = 0; i < numero_pares; i++)
        {
            int aluno_x, aluno_y;

            infile >> aluno_x >> aluno_y;

            if (grupos_disjuntos.at(aluno_x - 1) == grupos_disjuntos.at(aluno_y - 1))
            {
                cout << "S\n";
            }
            else
            {
                cout << "N\n";
            }
        }

        cout << "\n";
    }

    return 0;
}
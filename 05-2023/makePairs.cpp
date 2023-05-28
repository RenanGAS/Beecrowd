#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

void adicionarElemento(unordered_map<int, int> &conjuntos_disjuntos, int aluno_x, int aluno_y)
{
    if (conjuntos_disjuntos.at(aluno_x) == -1 && conjuntos_disjuntos.at(aluno_y) == -1)
    {
        conjuntos_disjuntos.at(aluno_x) = aluno_x;
        conjuntos_disjuntos.at(aluno_y) = aluno_x;
    }
    else
    {
        if (conjuntos_disjuntos.at(aluno_x) == -1 && conjuntos_disjuntos.at(aluno_y) != -1)
        {
            conjuntos_disjuntos.at(aluno_x) = conjuntos_disjuntos.at(aluno_y);
        }
        else if (conjuntos_disjuntos.at(aluno_x) != -1 && conjuntos_disjuntos.at(aluno_y) == -1)
        {
            conjuntos_disjuntos.at(aluno_y) = conjuntos_disjuntos.at(aluno_x);
        }
        else
        {
            int prox_pai_y = conjuntos_disjuntos.at(aluno_y);

            while (prox_pai_y != conjuntos_disjuntos.at(prox_pai_y))
            {
                prox_pai_y = conjuntos_disjuntos.at(prox_pai_y);
                conjuntos_disjuntos.at(prox_pai_y) = conjuntos_disjuntos.at(aluno_x);
            }

            conjuntos_disjuntos.at(aluno_y) = conjuntos_disjuntos.at(aluno_x);
        }
    }
}

void verificarPai(unordered_map<int, int> &conjuntos_disjuntos, int aluno_x, int aluno_y)
{
    if (conjuntos_disjuntos.at(aluno_x) == -1 || conjuntos_disjuntos.at(aluno_y) == -1)
    {
        cout << "N\n";
        return;
    }

    // int pai_x = aluno_x;

    // while (conjuntos_disjuntos.at(pai_x) != pai_x)
    // {
    //     pai_x = conjuntos_disjuntos.at(pai_x);
    // }

    // int pai_y = aluno_y;

    // while (conjuntos_disjuntos.at(pai_y) != pai_y)
    // {
    //     pai_y = conjuntos_disjuntos.at(pai_y);
    // }

    if (conjuntos_disjuntos.at(aluno_x) == conjuntos_disjuntos.at(aluno_y))
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
        cout << "\n";
        unordered_map<int, int> conjuntos_disjuntos;

        for (int i = 0; i < numero_alunos; i++)
        {
            conjuntos_disjuntos.emplace(i, -1);
        }

        for (int i = 0; i < numero_amizades_diretas; i++)
        {
            int aluno_x, aluno_y;

            infile >> aluno_x >> aluno_y;

            adicionarElemento(conjuntos_disjuntos, aluno_x - 1, aluno_y - 1);
        }

        for (int i = 0; i < numero_pares; i++)
        {
            int aluno_x, aluno_y;

            infile >> aluno_x >> aluno_y;

            verificarPai(conjuntos_disjuntos, aluno_x - 1, aluno_y - 1);
        }
    }

    return 0;
}
#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
    int TAMANHO_DNA, TAMANHO_PROTEINA;
    scanf("%d %d", &TAMANHO_DNA, &TAMANHO_PROTEINA);

    string FITA_DNA, PROTEINA;
    cin >> FITA_DNA >> PROTEINA;

    int consultas;
    scanf("%d", &consultas);

    for (int consulta = 0; consulta < consultas; consulta++) {

        int comeco, final;
        scanf("%d %d", &comeco, &final);

        string substring = PROTEINA.substr(comeco - 1, final - comeco + 1);

        regex pattern("(?=" + substring + ")");
        smatch matches;

        int count = 0;

        auto start = FITA_DNA.cbegin();
        auto end = FITA_DNA.cend();

        while (regex_search(start, end, matches, pattern)) {
            count++;
            start = matches[0].first + 1;
        }

        printf("%d\n", count);
    }

    return 0;
}

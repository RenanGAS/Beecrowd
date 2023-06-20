#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> computePrefixFunction(const string& pattern) {
    int m = pattern.length();
    vector<int> pi(m);
    int k = 0;

    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            k++;
        }
        pi[i] = k;
    }

    return pi;
}

int countOccurrences(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> pi = computePrefixFunction(pattern);
    int count = 0;
    int q = 0;

    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = pi[q - 1];
        }
        if (pattern[q] == text[i]) {
            q++;
        }
        if (q == m) {
            count++;
            q = pi[q - 1];
        }
    }

    return count;
}

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
        int count = countOccurrences(FITA_DNA, substring);
        printf("%d\n", count);
    }

    return 0;
}

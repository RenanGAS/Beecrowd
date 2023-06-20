#include <ostream>
#include <iostream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

bool cmp(pair<int, int> &a,
         pair<int, int> &b)
{
    return a.second < b.second;
}

void sort(map<int, int> &M)
{

    // Declare vector of pairs
    vector<pair<int, int>> A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto &it : M)
    {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    for (auto &it : A)
    {

        cout << it.first << ' '
             << it.second << endl;
    }
}

int main()
{
    int num_amigos;

    scanf("%d", &num_amigos);

    vector<int> chutes;
    vector<int> diferencas;
    vector<int> results;
    map<int, int> results2;

    for (int i = 0; i < num_amigos; i++)
    {
        int chute;
        scanf("%d", &chute);

        chutes.push_back(chute);
    }

    for (int i = 0; i < num_amigos; i++)
    {
        int diff;
        scanf("%d", &diff);

        diferencas.push_back(diff);
    }

    for (int i = 0; i < num_amigos; i++)
    {
        int mais = chutes[i] + diferencas[i];
        int menos = chutes[i] - diferencas[i];

        results.push_back(mais);
        results.push_back(menos);
    }

    int maxcount = 0;
    int element_having_max_freq;
    for (int i = 0; i < num_amigos * 2; i++)
    {
        int count = 0;
        for (int j = 0; j < num_amigos * 2; j++)
        {
            if (results[i] == results[j])
                count++;
        }

        if (count >= maxcount)
        {
            maxcount = count;
        }
    }

    for (int i = 0; i < num_amigos * 2; i++)
    {
        int count = 0;
        for (int j = 0; j < num_amigos * 2; j++)
        {
            if (results[i] == results[j])
                count++;
        }
        if (count == maxcount)
        {
            results2.emplace(results[i], results[i]);
        }
    }

    sort(results2);

    for (auto it = results2.begin(); it != results2.end(); it++)
    {
        printf("%d\n", it->first);
    }

    return EXIT_SUCCESS;
}
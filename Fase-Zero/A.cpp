#include <ostream>
#include <limits.h>
#include <fstream>
#include <string>

using namespace std;

void verifica_resultado(char *entrada)
{
    int countX = 0;

    for (size_t i = 0; i < 3; i++)
    {
        if (entrada[i] == 'X')
        {
            countX++;
        }
    }

    if (countX != 2)
    {
        printf("%s", "?\n");
    }
    else
    {
        if (entrada[1] == entrada[2] || entrada[0] == entrada[1])
        {
            printf("%s", "Alice\n");
        }
        else
        {
            printf("%s", "*\n");
        }
    }
}

int main()
{
    char entrada[4];

    scanf("%s", entrada);

    verifica_resultado(entrada);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))

// https://www.beecrowd.com.br/judge/pt/problems/view/3083

void KR(char *x, int m, char *y, int n)
{
    int d, hx, hy, i, j, result = 0;

    /* Preprocessing */
    /* computes d = 2^(m-1) with
       the left-shift operator */
    for (d = i = 1; i < m; ++i)
        d = (d << 1);

    for (hy = hx = i = 0; i < m; ++i)
    {
        hx = ((hx << 1) + x[i]);
        hy = ((hy << 1) + y[i]);
    }

    /* Searching */
    j = 0;
    while (j <= n - m)
    {
        if (hx == hy && memcmp(x, y + j, m) == 0)
            result++;
        hy = REHASH(y[j], y[j + m], hy);
        ++j;
    }
    printf("%d\n", result);
}

int main()
{
    char *string = malloc(sizeof(char *)), *pattern = malloc(sizeof(char *));
    int amount, str_size, pattern_size;
    scanf("%s", string);
    fflush(stdin);
    scanf("%s", pattern);
    fflush(stdin);
    scanf("%d", &amount);

    str_size = strlen(string);
    pattern_size = strlen(pattern);

    for (int i = 0; i < amount; i++)
    {
        char character, *str_copy = malloc(sizeof(char *));
        int pos;
        strcpy(str_copy, string);
        scanf("%d %c", &pos, &character);
        str_copy[pos - 1] = character;

        KR(pattern, pattern_size, str_copy, str_size);
    }
}
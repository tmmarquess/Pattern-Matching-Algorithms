#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX(int a, int b) { return (a > b) ? a : b; }

void preBmBc(char *x, int m, int bmBc[])
{
    int i;

    for (i = 0; i < m; ++i)
        bmBc[i] = m;
    for (i = 0; i < m - 1; ++i)
        bmBc[x[i]] = m - i - 1;
}

void suffixes(char *x, int m, int *suff)
{
    int f, g, i;

    suff[m - 1] = m;
    g = m - 1;
    for (i = m - 2; i >= 0; --i)
    {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else
        {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

void preBmGs(char *x, int m, int bmGs[])
{
    int i, j, suff[m];

    suffixes(x, m, suff);

    for (i = 0; i < m; ++i)
        bmGs[i] = m;
    j = 0;
    for (i = m - 1; i >= 0; --i)
        if (suff[i] == i + 1)
            for (; j < m - 1 - i; ++j)
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
    for (i = 0; i <= m - 2; ++i)
        bmGs[m - 1 - suff[i]] = m - 1 - i;
}

void BM(char *x, int m, char *y, int n)
{
    int i, j, bmGs[m], bmBc[m];

    /* Preprocessing */
    preBmGs(x, m, bmGs);
    preBmBc(x, m, bmBc);

    /* Searching */
    j = 0;
    while (j <= n - m)
    {
        for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i)
            ;
        if (i < 0)
        {
            printf("Pattern match! [%d:%d]\n", j, j + m - 1);
            j += bmGs[0];
        }
        else
            j += MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
    }
}

int main()
{
    char *string = "GCATCGCAGAGAGTATACAGTACG", *pattern = "GCAGAGAG";

    BM(pattern, strlen(pattern), string, strlen(string));

    string = "GCATCGCAGAGAGTATACAGTAGCAGAGAGCG";

    printf("===========\n");
    BM(pattern, strlen(pattern), string, strlen(string));

    string = "ABCABCABCABC";
    pattern = "ABCABC";

    printf("===========\n");
    BM(pattern, strlen(pattern), string, strlen(string));
}
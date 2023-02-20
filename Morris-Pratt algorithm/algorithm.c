#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preMp(char *x, int m, int mpNext[])
{
    int i, j;

    i = 0;
    j = mpNext[0] = -1;
    while (i < m)
    {
        while (j > -1 && x[i] != x[j])
            j = mpNext[j];
        mpNext[++i] = ++j;
    }
}

void MP(char *x, int m, char *y, int n)
{
    int i, j, mpNext[m + 1];

    /* Preprocessing */
    preMp(x, m, mpNext);

    /* Searching */
    i = j = 0;
    while (j < n)
    {
        while (i > -1 && x[i] != y[j])
            i = mpNext[i];
        i++;
        j++;
        if (i >= m)
        {
            printf("Pattern match! [%d:%d]\n", j - i, (j - i) + m - 1);
            i = mpNext[i];
        }
    }
}

int main()
{
    char *string = "GCATCGCAGAGAGTATACAGTACG", *pattern = "GCAGAGAG";
    MP(pattern, strlen(pattern), string, strlen(string));

    string = "GCATCGCAGAGAGTATACAGTAGCAGAGAGCG";

    printf("===========\n");
    MP(pattern, strlen(pattern), string, strlen(string));
}
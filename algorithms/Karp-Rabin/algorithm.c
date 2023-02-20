#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))

void KR(char *x, int m, char *y, int n)
{
    int d, hx, hy, i, j;

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
            printf("Pattern match! [%d:%d]\n", j, j + m - 1);
        hy = REHASH(y[j], y[j + m], hy);
        ++j;
    }
}

int main()
{
    char *string = "GCATCGCAGAGAGTATACAGTACG", *pattern = "GCAGAGAG";

    KR(pattern, strlen(pattern), string, strlen(string));

    string = "GCATCGCAGAGAGTATACAGTAGCAGAGAGCG";

    printf("===========\n");
    KR(pattern, strlen(pattern), string, strlen(string));

    string = "ABCABCABCABC";
    pattern = "ABCABC";

    printf("===========\n");
    KR(pattern, strlen(pattern), string, strlen(string));
}
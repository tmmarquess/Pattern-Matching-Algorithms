#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))

#define bool int
#define true 1
#define false 0

// https://www.beecrowd.com.br/judge/pt/problems/view/2974

bool KR(char *x, int m, char *y, int n)
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
            return true;
        hy = REHASH(y[j], y[j + m], hy);
        ++j;
    }
    return false;
}

char *sliceString(char *str, int start, int end)
{

    int i;
    int size = (end - start) + 2;
    char *output = malloc(size * sizeof(char));

    for (i = 0; start <= end; start++, i++)
    {
        output[i] = str[start];
    }

    output[size] = '\0';

    return output;
}

int main()
{
    int word_count;
    scanf("%d", &word_count);
    char **strings;
    strings = malloc(sizeof(char *) * word_count);
    for (int i = 0; i < word_count; i++)
    {
        char temp[100];
        fflush(stdin);
        scanf("%s", temp);
        strings[i] = malloc(sizeof(char) * strlen(temp));
        strcpy(strings[i], temp);
        temp[0] = '\0';
    }

    char *biggest_pattern_found = malloc(sizeof(char));
    int biggest_pattern_size = 0, beggining = 0, end = 0;

    char *sliced_string;
    bool pattern_not_found;
    while (end < strlen(strings[0]))
    {
        pattern_not_found = false;
        sliced_string = sliceString(strings[0], beggining, end);
        for (int i = 1; i < word_count; i++)
        {
            if (!KR(sliced_string, strlen(sliced_string), strings[i], strlen(strings[i])))
            {
                pattern_not_found = true;
                break;
            }
        }
        if (pattern_not_found)
        {
            beggining++;
            end = beggining;
        }
        else
        {
            if (biggest_pattern_size < strlen(sliced_string))
            {
                biggest_pattern_found = realloc(biggest_pattern_found, sizeof(char) * strlen(sliced_string));
                strcpy(biggest_pattern_found, sliced_string);
                biggest_pattern_size = strlen(sliced_string);
            }
            end++;
        }
        free(sliced_string);
    }
    printf("%s\n", biggest_pattern_found);
}
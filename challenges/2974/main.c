#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))

#define bool int
#define true 1
#define false 0

// https://www.beecrowd.com.br/judge/pt/problems/view/2974

typedef struct itens
{
    char **itens;
    int amount;
} itens;

itens *create_itens_list(int size)
{
    itens *lista = malloc(sizeof(itens));
    lista->amount = 0;
    lista->itens = malloc(sizeof(char *) * size);
    return lista;
}

void delete_list(itens **list)
{
    itens *lista = (*list);
    for (int i = 0; i < lista->amount; i++)
    {
        free(lista->itens[i]);
    }
    free(lista->itens);
    free(lista);
}

bool is_item_on_list(itens **list, char *item)
{
    itens *lista = (*list);
    for (int i = 0; i < lista->amount; i++)
    {
        if (!strcmp(lista->itens[i], item))
        {
            return true;
        }
    }
    return false;
}

void delete_item(itens **list, char *item)
{
    itens *lista = (*list);
    for (int i = 0; i < lista->amount; i++)
    {
        if (!strcmp(lista->itens[i], item))
        {
            free(lista->itens[i]);
            for (int j = i; j < lista->amount - 1; j++)
            {
                lista->itens[j] = lista->itens[j + 1];
            }
            lista->amount -= 1;
            break;
        }
    }
}

void add_item(itens **list, char *item)
{
    if (!is_item_on_list(list, item))
    {
        itens *lista = (*list);
        lista->itens[lista->amount] = malloc(sizeof(char) * strlen(item));
        strcpy(lista->itens[lista->amount], item);
        lista->amount += 1;
    }
}

void order_alphabetically(itens **list)
{
    itens *lista = (*list);
    for (int i = 0; i < lista->amount - 1; i++)
    {
        if (strcmp(lista->itens[i], lista->itens[i + 1]) > 0)
        {
            char *aux = lista->itens[i];
            lista->itens[i] = lista->itens[i + 1];
            lista->itens[i + 1] = aux;
        }
    }
}

void print_list(itens *list)
{
    printf("TOTAL\n");
    for (int i = 0; i < list->amount; i++)
    {
        printf("%s\n", list->itens[i]);
    }
}

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
        {
            if (j == 0 && (j + m - 1) == (n - 1))
            {
                return true;
            }
            break;
        }
        hy = REHASH(y[j], y[j + m], hy);
        ++j;
    }
    return false;
}

int main()
{
    int test_cases;
    scanf("%d", &test_cases);
    itens *list;
    for (int i = 0; i < test_cases; i++)
    {
        int utilizations;
        scanf("%d", &utilizations);
        list = create_itens_list(utilizations);
        for (int j = 0; j < utilizations; j++)
        {
            char *item = malloc(sizeof(char *)), *spell = malloc(sizeof(char *));
            fflush(stdin);
            scanf("%s %s", item, spell);
            fflush(stdin);
            if (KR(spell, strlen(spell), "chirrin", strlen("chirrin")))
            {
                add_item(&list, item);
            }
            else
            {
                if (KR(spell, strlen(spell), "chirrion", strlen("chirrion")))
                {
                    delete_item(&list, item);
                }
            }
            free(item);
            free(spell);
        }
        order_alphabetically(&list);
        print_list(list);
        // delete_list(&list);
        free(list);
    }
}
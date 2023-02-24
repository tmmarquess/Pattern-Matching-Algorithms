#include "finite_automaton.c"

// https://www.beecrowd.com.br/judge/pt/problems/view/3088

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

void fix_string(char *string, match *matches_list)
{

    char *string2 = malloc(strlen(string) * sizeof(char)), *aux_string = malloc(strlen(string) * sizeof(char));
    strcpy(aux_string, string);
    for (int i = 0; i < matches_list->amount; i++)
    {
        strcpy(string2, aux_string);
        strcpy(aux_string, "");

        char *aux = sliceString(string2, 0, matches_list->index_list[i] - 1 - i);
        strcat(aux_string, aux);
        free(aux);
        aux = sliceString(string2, matches_list->index_list[i] + 1 - i, strlen(string2));
        strcat(aux_string, aux);
        free(aux);
    }
    strcpy(string, aux_string);
    // printf("%s\n", aux_string);
    free(string2);
    free(aux_string);
}

int main()
{
    match *matches_list = create_match_list();
    graph *automaton = generate_automaton(" .");
    graph *automaton2 = generate_automaton(" ,");

    char *string = malloc(sizeof(char *));
    while (scanf("%[^\n]%*c", string) != EOF)
    {
        fflush(stdin);

        search_pattern_with_automaton(string, automaton, &matches_list);
        search_pattern_with_automaton(string, automaton2, &matches_list);

        sort_match_list(matches_list);
        fix_string(string, matches_list);

        reset_list(&matches_list);
        printf("%s\n", string);
    }
}
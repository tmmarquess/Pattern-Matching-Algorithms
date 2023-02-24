#include "graph.c"
#include <string.h>

typedef struct match
{
    int *index_list;
    int amount;
} match;

match *create_match_list()
{
    match *new_match = malloc(sizeof(match));
    new_match->index_list = malloc(sizeof(int *));
    new_match->amount = 0;
    return new_match;
}

void add_match(match **matches_list, int value)
{
    match *list = (*matches_list);
    list->index_list[list->amount] = value;
    list->amount++;
}

void reset_list(match **matches_list)
{
    match *list = (*matches_list);
    free(list->index_list);
    list->index_list = malloc(sizeof(int *));
    list->amount = 0;
}

graph *generate_automaton(char *pattern)
{
    graph *automaton = NULL;
    init_graph(&automaton);

    int size = strlen(pattern);

    for (int i = 0; i < size + 1; i++)
    {
        insert_vertex(&automaton);
        if (i >= 1)
        {
            insert_edge(&automaton, i - 1, i, false, pattern[i - 1]);

            if (pattern[i - 1] == pattern[0] && pattern[i] != pattern[1])
            {
                insert_edge(&automaton, i, 2, false, pattern[1]);
            }
            if (pattern[i] != pattern[0])
            {
                insert_edge(&automaton, i, 1, false, pattern[0]);
            }
        }
    }
    set_terminal(&automaton, size, true);

    return automaton;
}

void search_pattern_with_automaton(char *string, graph *automaton, match **matches_list)
{
    int current_state = 0, size = strlen(string);
    bool changed_state;

    for (int i = 0; i < size; i++)
    {
        changed_state = false;
        edge *trasitions = automaton->vertex_list[current_state]->adj_list;
        while (trasitions != NULL)
        {
            if (trasitions->character == string[i])
            {
                current_state = trasitions->value;
                changed_state = true;
                break;
            }
            trasitions = trasitions->next;
        }
        if (!changed_state)
        {
            current_state = 0;
        }
        if (automaton->vertex_list[current_state]->terminal)
        {
            add_match(matches_list, i - (current_state - 1));
        }
    }
}

match *search_pattern(char *pattern, char *string)
{
    match *matches_list = create_match_list();
    graph *automaton = generate_automaton(pattern);
    search_pattern_with_automaton(string, automaton, &matches_list);
    return matches_list;
}

void sort_match_list(match *matches_list)
{
    for (int i = 0; i < matches_list->amount - 1; i++)
    {
        if (matches_list->index_list[i] > matches_list->index_list[i + 1])
        {
            int aux = matches_list->index_list[i];
            matches_list->index_list[i] = matches_list->index_list[i + 1];
            matches_list->index_list[i + 1] = aux;
        }
    }
}

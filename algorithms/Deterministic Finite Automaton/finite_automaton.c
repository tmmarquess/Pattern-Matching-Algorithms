#include "graph.c"
#include <string.h>

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
    // show_graph(automaton);

    return automaton;
}

void search_pattern(char *pattern, char *string)
{
    graph *automaton = generate_automaton(pattern);

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
            printf("Pattern match! [%d:%d]\n", i - (current_state - 1), i);
        }
    }
}

int main()
{

    // graph *automaton = generate_automaton("GCAGAGAG");
    // graph *automaton = generate_automaton("ABCABCABC");
    // printf("%ld\n\n", strlen("GCATCGCAGAGAGTATACAGTACG"));
    search_pattern("GCAGAGAG", "GCATCGCAGAGAGTATACAGTACG");
    printf("===============\n");
    search_pattern("GCAGAGAG", "GCATCGCAGAGAGTATACAGTAGCAGAGAGCG");
    printf("===============\n");
    search_pattern("ABCABC", "ABCABCABCABC");
}
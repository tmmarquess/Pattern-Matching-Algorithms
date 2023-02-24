#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define bool int

typedef struct edge
{
    int value;
    char character;
    struct edge *next;
} edge;

edge *create_edge(int value, char character)
{
    edge *new = (edge *)malloc(sizeof(edge));
    new->value = value;
    new->character = character;
    new->next = NULL;
    return new;
}

void insert_edge_on_list(edge **first_node, int value, char character)
{
    if ((*first_node) == NULL)
    {
        (*first_node) = create_edge(value, character);
        return;
    }
    edge *current_node = *(first_node);

    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }
    current_node->next = create_edge(value, character);
}

bool delete_edge(edge **first_node, int value)
{
    edge *current = *(first_node), *previous;
    previous = current;

    if (current == NULL)
    {
        return false;
    }

    while (current->value != value)
    {
        previous = current;
        current = current->next;
        if (current == NULL)
        {
            return false;
        }
    }
    if (previous == current)
    {
        *(first_node) = current->next;
        free(current);
        return true;
    }
    previous->next = current->next;
    free(current);
    return true;
}

int get_edge_list_size(edge *list)
{
    edge *current = list;
    int size = 0;

    while (current != NULL)
    {
        size++;
        current = current->next;
    }

    return size;
}

bool is_value_on_edge_list(edge *list, int value)
{
    edge *current = list;
    while (current != NULL)
    {
        if (current->value == value)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
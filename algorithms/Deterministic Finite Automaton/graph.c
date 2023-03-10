#include "edge.c"

typedef struct vertex
{
    int id;
    bool terminal;
    edge *adj_list;
} vertex;

typedef struct graph
{
    int vertex_list_size;
    int del_count;
    vertex **vertex_list;
} graph;

void insert_vertex(graph **list)
{
    int index = (*list)->vertex_list_size;

    (*list)->vertex_list[index] = malloc(sizeof(vertex));
    (*list)->vertex_list[index]->id = index + (*list)->del_count;
    (*list)->vertex_list[index]->terminal = false;
    (*list)->vertex_list[index]->adj_list = NULL;

    (*list)->vertex_list_size++;

    (*list)->vertex_list = realloc((*list)->vertex_list, sizeof(vertex) * ((*list)->vertex_list_size + 1));
    (*list)->vertex_list[index + 1] = NULL;
}

void init_graph(graph **list)
{
    (*list) = malloc(sizeof(graph));
    (*list)->vertex_list = malloc(sizeof(vertex *));
    (*list)->vertex_list_size = 0;
    (*list)->del_count = 0;
    (*list)->vertex_list[0] = NULL;
}

bool insert_edge(
    graph **list,
    int origin_vertex_id,
    int destiny_vertex_id,
    bool bidirectional,
    char character)
{
    vertex *vertex_origin = NULL, *vertex_destiny = NULL;

    for (int i = 0; i < (*list)->vertex_list_size; i++)
    {
        if ((*list)->vertex_list[i]->id == origin_vertex_id)
        {
            vertex_origin = (*list)->vertex_list[i];
        }

        if ((*list)->vertex_list[i]->id == destiny_vertex_id)
        {
            vertex_destiny = (*list)->vertex_list[i];
        }
    }

    if (vertex_origin == NULL || vertex_destiny == NULL)
    {
        return false;
    }

    insert_edge_on_list(&vertex_origin->adj_list, vertex_destiny->id, character);

    if (bidirectional)
    {
        insert_edge_on_list(&vertex_destiny->adj_list, vertex_origin->id, character);
    }

    return true;
}

bool remove_edge(graph **list, int vertex_a_id, int vertex_b_id)
{
    bool deleted_a = false, deleted_b = false;

    for (int i = 0; i < (*list)->vertex_list_size; i++)
    {
        if ((*list)->vertex_list[i]->id == vertex_a_id)
        {
            delete_edge(&((*list)->vertex_list[i]->adj_list), vertex_b_id);
            deleted_a = true;
        }

        if ((*list)->vertex_list[i]->id == vertex_b_id)
        {
            delete_edge(&((*list)->vertex_list[i]->adj_list), vertex_a_id);
            deleted_b = true;
        }

        if (deleted_a && deleted_b)
        {
            return true;
        }
    }

    return false;
}

void set_terminal(graph **list, int vertex_id, bool terminal)
{
    for (int i = 0; i < (*list)->vertex_list_size; i++)
    {
        if ((*list)->vertex_list[i]->id == vertex_id)
        {
            (*list)->vertex_list[i]->terminal = terminal;
            return;
        }
    }
}

bool remove_vertex(graph **list, int vertex_id)
{
    bool vertex_exists = false;
    int vertex_pos;
    for (int i = 0; i < (*list)->vertex_list_size; i++)
    {
        if ((*list)->vertex_list[i]->id == vertex_id)
        {
            vertex_exists = true;
            vertex_pos = i;
        }
        else
        {
            delete_edge(&((*list)->vertex_list[i]->adj_list), vertex_id);
        }
    }
    if (!vertex_exists)
    {
        return false;
    }

    free((*list)->vertex_list[vertex_pos]);

    for (int i = vertex_pos; i < (*list)->vertex_list_size - 1; i++)
    {
        (*list)->vertex_list[i] = (*list)->vertex_list[i + 1];
    }
    free((*list)->vertex_list[(*list)->vertex_list_size]);

    (*list)->del_count++;
    (*list)->vertex_list_size--;

    (*list)->vertex_list = realloc((*list)->vertex_list, sizeof(vertex) * ((*list)->vertex_list_size + 1));
    (*list)->vertex_list[(*list)->vertex_list_size] = NULL;

    return true;
}

void destroy_graph(graph **list)
{
    if ((*list)->vertex_list[0] == NULL)
    {
        (*list)->del_count = 0;
        return;
    }
    remove_vertex(list, (*list)->vertex_list[0]->id);
    destroy_graph(list);
}

int get_out_degree(graph *list, int vertex_id)
{
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        if (list->vertex_list[i]->id == vertex_id)
        {
            return get_edge_list_size(list->vertex_list[i]->adj_list);
        }
    }
    return 0;
}

int get_in_degree(graph *list, int vertex_id)
{
    int in_degree = 0;
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        if (list->vertex_list[i]->id != vertex_id)
        {
            if (is_value_on_edge_list(list->vertex_list[i]->adj_list, vertex_id))
            {
                in_degree++;
            }
        }
    }
    return in_degree;
}

void show_graph(graph *list)
{
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        if (list->vertex_list[i]->terminal)
        {
            printf("[%d]: ", list->vertex_list[i]->id);
        }
        else
        {
            printf(" %d : ", list->vertex_list[i]->id);
        }
        edge *current_node = list->vertex_list[i]->adj_list;
        while (current_node != NULL)
        {
            printf("(%c) %d | ", current_node->character, current_node->value);
            current_node = current_node->next;
        }
        printf("\n");
    }
}

// int main()
// {
//     graph *list1 = NULL;

//     // Inicializa um grafo vazio
//     init_graph(&list1);

//     // Adiciona 5 v??rtices
//     insert_vertex(&list1);
//     insert_vertex(&list1);
//     insert_vertex(&list1);
//     insert_vertex(&list1);
//     insert_vertex(&list1);

//     /*
//      * Adiciona uma aresta bidirecional entre os v??rtices de ??ndices 0 e 1
//      * de peso 10
//      */
//     insert_edge(&list1, 0, 1, false, 'C');

//     /*
//      * Adiciona uma aresta unidirecional entre os v??rtices de ??ndices 0 e 2, ou
//      * seja, ?? poss??vel ir do v??rtice de ??ndice 0 para o de ??ndice 2, mas
//      * n??o o contr??rio (at?? o momento). Essa aresta tem peso 0
//      */
//     insert_edge(&list1, 0, 2, false, 'D');

//     /*
//      * Adiciona uma aresta bidirecional entre os v??rtices de ??ndices 0 e 3
//      * de peso 20
//      */
//     insert_edge(&list1, 0, 3, false, 'E');

//     /*
//      * Adiciona uma aresta bidirecional entre os v??rtices de ??ndices 1 e 3
//      * de peso 5
//      */
//     insert_edge(&list1, 1, 3, false, 'F');

//     /*
//      * Adiciona uma aresta bidirecional entre os v??rtices de ??ndices 1 e 4
//      * de peso 12
//      */
//     insert_edge(&list1, 1, 4, false, 'G');

//     /*
//      * Adiciona uma aresta unidirecional entre os v??rtices de ??ndices 2 e 3
//      * de peso 8
//      */
//     insert_edge(&list1, 2, 3, false, 'H');

//     /*
//      * Adiciona uma aresta unidirecional entre os v??rtices de ??ndices 3 e 4
//      * de peso 18
//      */
//     insert_edge(&list1, 3, 4, false, 'I');

//     // Mostra o grafo
//     show_graph(list1);
//     printf("=================\n");

//     // Remove o v??rtice de ??ndice 3
//     remove_vertex(&list1, 3);

//     // Insere mais dois v??rtices
//     insert_vertex(&list1);
//     insert_vertex(&list1);

//     // Mostra o grafo
//     show_graph(list1);
//     printf("=================\n");

//     remove_vertex(&list1, 4);

//     show_graph(list1);
//     printf("=================\n");

//     // Insere um v??rtice
//     insert_vertex(&list1);

//     // Mostra o grafo
//     show_graph(list1);
//     printf("=================\n");

//     /*
//      * Adiciona uma aresta bidirecional entre os v??rtices de ??ndices 2 e 7
//      * de peso 30
//      */
//     insert_edge(&list1, 2, 7, false, 'J');

//     /*
//      * Tenta adicionar uma aresta bidirecional entre os v??rtices de ??ndices 2 e 4
//      * de peso 16, mas como o v??rtice de ??ndice 4 n??o existe, essa aresta n??o ??
//      * adicionada
//      */
//     insert_edge(&list1, 2, 4, false, 'K');

//     // Mostra o grafo
//     show_graph(list1);
//     printf("=================\n");

//     // Destr??i o grafo (limpa todos as arestas e v??rtices da mem??ria)
//     destroy_graph(&list1);

//     // Mostra o grafo vazio
//     show_graph(list1);
//     printf("=================\n");

//     /*
//      * Obs: nessa implementa????o de grafos, quando todas as arestas s??o
//      * inseridas como bidirecionais, temos um grafo n??o-direcionado, ou seja,
//      * n??o existe um sentido entre as arestas. No entanto, quando inserimos no
//      * m??nimo uma aresta unidirecional, temos um grafo direcionado, mesmo que
//      * todas as outras arestas sejam bidirecionais
//      */
// }
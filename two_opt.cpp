#include "two_opt.h"

void two_opt_swap(Graph *g, Graph::Point *p_i, Graph::Point *p_k)
{
    // Temporary Variables
    int p_i_next = p_i->next;
    int p_i_prev = p_i->prev;
    int p_k_next = p_k->next;
    int p_k_prev = p_k->prev;
    int p_i_next_next = g->coords[p_i_next]->next;

    // Algorithm

    // Update i
    p_i->next = p_k->pos;

    // Update k
    p_k->prev = p_i->pos;
    p_k->next = g->coords[p_k_prev]->pos;

    // Update i + 1
    g->coords[p_i_next]->next = g->coords[p_k_next]->pos;
    g->coords[p_i_next]->prev = g->coords[p_i_next_next]->pos;

    // Update k + 1
    g->coords[p_k_next]->prev = g->coords[p_i_next]->pos;

    // Reverse k - 1 to i + 2
    Graph::Point *c = g->coords[p_k_prev];
    while (c->pos != g->coords[p_i_next]->pos)
    {
        int temp = c->prev;
        c->prev = c->next;
        c->next = temp;
        c = g->coords[temp];
    }
}

int calculate_length_delta(Graph *g, Graph::Point *p_i, Graph::Point *p_k)
{
    Graph::Point *p_i_next = g->coords[p_i->next];
    Graph::Point *p_k_next = g->coords[p_k->next];

    return (- g->dist(p_i, p_i_next) - g->dist(p_k, p_k_next) 
            + g->dist(p_i, p_k)      + g->dist(p_i_next, p_k_next));
}

void apply_two_opt(Graph *g)
{
    int N = g->N;
    bool foundImprovement = true;

    while (foundImprovement)
    {
        foundImprovement = false;
        for (Graph::Point *p_i = g->coords[0]; p_i->next != 0; p_i = g->coords[p_i->next])
        {
            for (Graph::Point *p_k = g->coords[p_i->next]; p_k->next != p_i->next; p_k = g->coords[p_k->next])
            {
                int lengthDelta = calculate_length_delta(g, p_i, p_k);

                if (lengthDelta < 0)
                {
                    two_opt_swap(g, p_i, p_k);
                    foundImprovement = true;
                }
            }
        }
    }
}

void two_opt_swap_vector(std::vector<int>& tour, int i, int j, int k)
{
    int a = tour[j - k];
    tour[j - k] = tour[i + k + 1];
    tour[i + k + 1] = a;
}

int calculate_length_delta(Graph *g, std::vector<int>& tour, int i, int k)
{
    return (- std::get<0>(g->matrix[tour[i]][tour[i + 1]]) - std::get<0>(g->matrix[tour[k]][tour[k + 1]]) 
            + std::get<0>(g->matrix[tour[i]][tour[k]])     + std::get<0>(g->matrix[tour[i + 1]][tour[k + 1]]));
}

std::vector<int> apply_two_opt_vector(Graph *g, std::vector<int>& v)
{
    if (g->N > 3)
    {
        int distance = -1;
        int bestDistance = g->fitness_vector(v);
        std::vector<int> tour = std::vector<int>(v);
        std::vector<int> bestTour = std::vector<int>(v);

        while (distance < bestDistance)
        {
            tour.push_back(tour[0]);

            for (int i = 0; i < g->N - 3; i++)
            {
                for (int j = i + 2; j < g->N; j++)
                {
                    int lengthDelta = calculate_length_delta(g, tour, i, j);
                    
                    if (lengthDelta < 0)
                    {
                        for (int k = 0; k < (j - i) / 2; k++)
                        {
                            two_opt_swap_vector(tour, i, j, k);
                        }
                    }
                }
            }

            tour.pop_back();
            distance = g->fitness_vector(tour);
            bestTour = std::vector<int>(tour);
            bestDistance = distance;
        }
        return bestTour;
    }
    else
        return v;
}

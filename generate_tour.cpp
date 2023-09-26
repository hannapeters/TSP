#include "generate_tour.h"

void create_greedy_tour(Graph *g) {
    int N = g->N;
    int pos = 0;
    int prev = -1;
    bool visited[N] = { 0 };
    auto matrix(g->matrix);

    visited[0] = true;
    for (int i = 0; i < N; i++) {
        std::sort(matrix[pos].begin(), matrix[pos].end());
        for (int cur_node = 0; cur_node < N; cur_node++) {
            int next = std::get<1>(matrix[pos][cur_node]);
            if (!visited[next] && pos != next) {
                g->coords[pos]->prev = prev;
                g->coords[pos]->next = next;
                visited[pos] = true;
                prev = pos;
                pos = next;
                break;
            }
        }
    }

    g->coords[pos]->next = 0;
    g->coords[pos]->prev = prev;
    g->coords[0]->prev = pos;
}

void create_random_tour(Graph *g)
{
    std::vector<int> v(g->N);
    std::srand(std::time(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());

    for (int i = 0; i < g->N; i++)
    {
        if (i == 0)
        {
            g->coords[v[i]]->prev = v[g->N - 1];
            g->coords[v[i]]->next = v[i + 1];
        }
        else if (i != (g->N - 1))
        {
            g->coords[v[i]]->prev = v[i - 1];
            g->coords[v[i]]->next = v[i + 1];
        }
        else
        {
            g->coords[v[i]]->prev = v[i - 1];
            g->coords[v[i]]->next = v[0];
        }
    }
}
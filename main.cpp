#include "graph.h"
#include "two_opt.h"
#include "generate_tour.h"
#include "genetic_algorithm.h"

void solve(Graph *g, clock_t begin)
{
    if (g->N > 1) 
    {
        create_greedy_tour(g);
        apply_two_opt(g);
        apply_genetic_algorithm(g, begin);
    } else 
        std::cout << 0 << std::endl;
}

int main() {
    clock_t begin = clock();
    int N;
    std::cin >> N;
    Graph g(N);
    solve(&g, begin);
}
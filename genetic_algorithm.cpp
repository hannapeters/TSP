#include "two_opt.h"
#include "genetic_algorithm.h"

std::random_device rand_dev;
std::mt19937 generator(rand_dev());

int random_int(int from, int to)
{
    std::uniform_int_distribution<int> distr(from, to);
    return distr(generator);
}

bool termination_criteria_met(clock_t begin, double criteria)
{
    return ((double(clock() - begin) / CLOCKS_PER_SEC) >= criteria);
}

void order_generated_population(Population &p)
{
    std::sort(p.begin(), p.end(),
              [&](Chromosome c1, Chromosome c2) -> bool
              {
                  return std::get<1>(c1) < std::get<1>(c2);
              });
}

Chromosome generate_chromosome(Graph *g, std::vector<int> tour)
{
    int i = random_int(0, g->N - 1);
    int j = random_int(0, g->N - 1);

    while (i == j) j = random_int(0, g->N - 1);

    int temp = tour[i];
    tour[i] = tour[j];
    tour[j] = temp;

    tour = apply_two_opt_vector(g, tour);
    return std::make_tuple(tour, g->fitness_vector(tour));
}

Population create_mutation(Graph *g, Population p)
{
    Population population;
    population.push_back(p[0]);
    for (int i = 0; i < 10; i++)
        population.push_back(generate_chromosome(g, std::get<0>(p[i])));
    order_generated_population(population);
    return population;
}

void apply_genetic_algorithm(Graph *g, clock_t begin)
{
    Population population;
    std::vector<int> tour_init = g->getTour(0);

    for (int i = 0; i < 10; i++)
        population.push_back(generate_chromosome(g, tour_init));
    order_generated_population(population);

    while (!termination_criteria_met(begin, 1.95))
        population = create_mutation(g, population);

    for (int i : std::get<0>(population[0]))
        std::cout << i << std::endl;
}
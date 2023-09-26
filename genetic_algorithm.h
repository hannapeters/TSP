#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <ctime>
#include <tuple>
#include <vector>
#include <random>
#include "graph.h"

typedef std::vector<int> Mutation;
typedef std::tuple<Mutation, int> Chromosome;
typedef std::vector<Chromosome> Population;

bool termination_criteria_met(clock_t begin, double criteria);

void order_generated_population(Population &p);

Chromosome generate_chromosome(Graph *g, std::vector<int> tour);

Population create_mutation(Graph * g, Population p);

void apply_genetic_algorithm(Graph *g, clock_t begin);

#endif // GENETIC_ALGORITHM_H
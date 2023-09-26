#ifndef GENERATE_TOUR_H
#define GENERATE_TOUR_H

#include <tuple>
#include <ctime>
#include "graph.h"

void create_greedy_tour(Graph *g);
void create_random_tour(Graph *g);

#endif // GENERATE_TOUR_H
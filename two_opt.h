#ifndef TWO_OPT_H
#define TWO_OPT_H

#include "graph.h"
#include <numeric>
#include <cstring>
#include <algorithm>

void two_opt_swap(Graph *g, Graph::Point * p_i, Graph::Point * p_k);

int calculate_length_delta(Graph *g, std::vector<int> solution, Graph::Point * p_i, Graph::Point * p_k);

void apply_two_opt(Graph *g);

void two_opt_swap_vector(std::vector<int>& tour, int i, int j, int k);

int calculate_length_delta(Graph *g, std::vector<int>& v, int i, int k);

std::vector<int> apply_two_opt_vector(Graph *g, std::vector<int>& v);

#endif // TWO_OPT_H
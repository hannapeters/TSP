#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>
#include <memory>
#include <string>
#include <random>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

class Graph
{
public:
    class Point
    {
    public:
        double x, y, dist;
        int pos, next, prev;
        Point &operator=(const Point &other);
        Point(int pos, double x, double y) : pos(pos), x(x), y(y), dist(0), next(-1), prev(-1){};
        Point(int pos, double x, double y, int next, int prev) : pos(pos), x(x), y(y), next(next), prev(prev){};
    };

    // Constructors
    Graph(int N);
    Graph(const Graph *other);
    Graph &operator=(const Graph &other);
    ~Graph();

    // Variables
    int N;
    std::vector<Point *> coords;
    std::vector<std::vector<std::tuple<int, int>>> matrix;

    // Methods
    void print_points();
    void setTour(std::vector<int>, int N);
    std::vector<int> getTour(int pos);
    void setTour(std::string &tour, int N);
    std::string getTour(int pos, bool reverse);
    void print_tour(int pos, bool reverse);
    int dist(Point *p1, Point *p2);
    int fitness(int pos);
    int fitness_vector(std::vector<int>& v);
};

#endif // GRAPH_H
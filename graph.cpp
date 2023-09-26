#include "graph.h"

Graph::Point &Graph::Point::operator=(const Graph::Point &other)
{
    this->x = other.x;
    this->y = other.y;
    this->pos = other.pos;
    this->next = other.next;
    this->prev = other.prev;
    return *this;
}

Graph::Graph(int N)
{
    this->N = N;
    this->coords.reserve(N);
    this->matrix.resize(N, std::vector<std::tuple<int, int>>(N));

    for (int i = 0; i < N; i++)
    {
        double x, y;
        std::cin >> x >> y;
        Point *p = new Point(i, x, y);
        this->coords.push_back(p);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            this->matrix[i][j] = std::make_tuple(dist(coords[i], coords[j]), j);
        }
    }
}

Graph::Graph(const Graph *other)
{
    this->coords = std::vector<Graph::Point *>(other->N, nullptr);
    this->matrix = other->matrix;
    this->N = other->N;

    for (int i = 0; i < other->N; i++)
    {
        Point *p = new Point(other->coords[i]->pos, other->coords[i]->x, other->coords[i]->y, other->coords[i]->next, other->coords[i]->prev);
        this->coords[i] = p;
    }
}

Graph &Graph::operator=(const Graph &other)
{
    for (int i = 0; i < other.N; i++)
    {
        *this->coords[i] = *other.coords[i];
    }
    return *this;
}

Graph::~Graph()
{
    for (Point *p : coords)
    {
        delete (p);
    }
}

void Graph::print_points()
{
    std::cout << "Number of points: " << N << std::endl;
    for (auto &p : coords)
    {
        std::cout << "Point " << p->pos << ": (" << p->x << ", " << p->y << ")" << std::endl;
    }
}

void Graph::setTour(std::vector<int> arr, int N)
{
    for (int i = 1; i < N - 1; i++)
    {
        this->coords[arr[i]]->prev = arr[i - 1];
        this->coords[arr[i]]->next = arr[i + 1];
    }

    this->coords[arr[0]]->prev = arr[N - 1];
    this->coords[arr[0]]->next = arr[1];
    this->coords[arr[N - 1]]->prev = arr[N - 2];
    this->coords[arr[N - 1]]->next = arr[0];
}

std::vector<int> Graph::getTour(int pos)
{
    std::vector<int> v;
    for (Point * p = this->coords[pos]; v.size() < this->N; p = this->coords[p->next])
        v.push_back(p->pos);
    return v;
}

void Graph::setTour(std::string &tour, int N)
{
    int pos = 0;
    std::vector<int> arr(N);
    std::string num = "";
    int length = tour.length();

    for (int i = 0; i < length; i++)
    {
        if (tour[i] != ' ')
        {
            num += tour[i];
        }
        else if (tour[i] == ' ')
        {
            arr.push_back(std::atoi(num.c_str()));
            num = "";
            pos++;
        }
    }

    this->setTour(arr, N);
}

std::string Graph::getTour(int pos, bool reverse)
{
    std::string output = "";

    bool visited[N] = {0};
    Point *start = coords.at(pos);
    visited[start->pos] = true;

    output += std::to_string(start->pos);
    if (start->next != -1)
    {
        Point *nextOrPrev = (reverse) ? coords.at(start->prev) : coords.at(start->next);
        while (!visited[nextOrPrev->pos])
        {
            output += " " + std::to_string(nextOrPrev->pos);
            visited[nextOrPrev->pos] = true;
            nextOrPrev = (reverse) ? coords.at(nextOrPrev->prev) : coords.at(nextOrPrev->next);
        }
        output += " " + std::to_string(nextOrPrev->pos);
    }

    return output;
}

void Graph::print_tour(int pos, bool reverse)
{
    std::string num = "";
    std::string tour = this->getTour(pos, reverse);
    int length = tour.length();
    for (int i = 0; i < length; i++)
    {
        if (tour[i] != ' ')
        {
            num += tour[i];
        }
        else
        {
            std::cout << num;
            if (i != length - 2)
                std::cout << " -> ";
            num = "";
        }
    }
    std::cout << std::endl;
}

int Graph::dist(Point *p1, Point *p2)
{
    return std::round(std::sqrt(std::pow(p2->x - p1->x, 2) + std::pow(p2->y - p1->y, 2)));
}

int Graph::fitness(int pos)
{

    Point *p = this->coords[pos];
    int sum = this->dist(p, this->coords[p->next]);
    for (p = this->coords[p->next]; p->pos != pos; p = this->coords[p->next])
        sum += this->dist(this->coords[p->pos], this->coords[p->next]);
    return sum;
}

int Graph::fitness_vector(std::vector<int>& v)
{
    int sum = std::get<0>(matrix[v[0]][v[N - 1]]);
    for (int i = 1; i < v.size(); i++)
        sum += std::get<0>(matrix[v[i]][v[i - 1]]);
    return sum;
}
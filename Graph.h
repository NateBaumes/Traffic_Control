#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
    int to;
    double weight;
};

struct Graph {
    int nodes;
    std::vector<std::vector<Edge>> adjacencyList;
};

#endif // GRAPH_H

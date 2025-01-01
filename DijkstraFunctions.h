#ifndef DIJKSTRAFUNCTIONS_H
#define DIJKSTRAFUNCTIONS_H

#include <vector>
#include "Graph.h"

// Function declarations
void sequentialDijkstra(const Graph& graph, int source, std::vector<double>& distances);
void parallelDijkstra(const Graph& graph, int source, std::vector<double>& distances);

#endif // DIJKSTRAFUNCTIONS_H

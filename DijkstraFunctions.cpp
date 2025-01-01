#include "DijkstraFunctions.h"
#include <queue>
#include <climits>
#include <omp.h>

// Sequential Dijkstra Algorithm
void sequentialDijkstra(const Graph& graph, int source, std::vector<double>& distances) {
    distances.assign(graph.nodes, INT_MAX);
    distances[source] = 0.0;

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    pq.push({0.0, source});

    while (!pq.empty()) {
        auto currentPair = pq.top();
        double currentDistance = currentPair.first;
        int currentNode = currentPair.second;
        pq.pop();

        if (currentDistance > distances[currentNode]) continue;

        for (const auto& edge : graph.adjacencyList[currentNode]) {
            if (distances[currentNode] + edge.weight < distances[edge.to]) {
                distances[edge.to] = distances[currentNode] + edge.weight;
                pq.push({distances[edge.to], edge.to});
            }
        }
    }
}

// Parallel Dijkstra Algorithm
void parallelDijkstra(const Graph& graph, int source, std::vector<double>& distances) {
    distances.assign(graph.nodes, INT_MAX);
    distances[source] = 0.0;

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    pq.push({0.0, source});

    #pragma omp parallel
    {
        while (!pq.empty()) {
            #pragma omp single
            {
                auto currentPair = pq.top();
                double currentDistance = currentPair.first;
                int currentNode = currentPair.second;
                pq.pop();

                if (currentDistance > distances[currentNode]) continue;

                for (const auto& edge : graph.adjacencyList[currentNode]) {
                    if (distances[currentNode] + edge.weight < distances[edge.to]) {
                        distances[edge.to] = distances[currentNode] + edge.weight;
                        pq.push({distances[edge.to], edge.to});
                    }
                }
            }
        }
    }
}

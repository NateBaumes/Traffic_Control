#include <iostream>
#include <vector>
#include <chrono>
#include <random>  // For random number generation
#include <iomanip> // For controlling output format
#include "DijkstraFunctions.h"
#include "Graph.h"

// Function to generate a random graph
void generateRandomGraph(Graph& graph, int numNodes, int numEdges) {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> nodeDist(0, numNodes - 1);
    std::uniform_int_distribution<> weightDist(1, 10); // Random weight between 1 and 10

    graph.nodes = numNodes;
    graph.adjacencyList.resize(numNodes);

    // Add random edges
    for (int i = 0; i < numEdges; ++i) {
        int from = nodeDist(gen);
        int to = nodeDist(gen);
        while (to == from) { // Prevent self-loops
            to = nodeDist(gen);
        }
        int weight = weightDist(gen);

        graph.adjacencyList[from].push_back({to, weight});
    }
}

// Function to display the graph
void displayGraph(const Graph& graph) {
    std::cout << "\nGenerated Random Graph:\n";
    for (int i = 0; i < graph.nodes; ++i) {
        std::cout << "Node " << i << " connects to: ";
        for (const auto& edge : graph.adjacencyList[i]) {
            std::cout << "(" << edge.to << ", " << edge.weight << ") ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

// Function to display the distances without scientific notation
void displayDistances(const std::vector<double>& distances) {
    std::cout << "\nShortest Path Distances from Source Node:\n";
    for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << "  Node " << i << ": " << std::fixed << std::setprecision(3) << distances[i] << "\n";
    }
}

// Function to print execution time in scientific notation
void printExecutionTime(const std::chrono::duration<double>& duration, const std::string& algorithmName) {
    std::cout << "\n" << algorithmName << " Execution Time: "
              << std::fixed << std::setprecision(3) << duration.count() << " seconds ("
              << std::scientific << duration.count() << " in scientific notation)\n";
}

int main() {
    // Define the number of nodes and edges for the random graph
    int numNodes = 5;  // You can adjust this to a larger number for more complex graphs
    int numEdges = 10; // You can adjust this based on your desired edge density
    
    // Create and generate random graph
    Graph graph;
    generateRandomGraph(graph, numNodes, numEdges);
    
    // Display the generated graph
    displayGraph(graph);
    
    // For storing the distances
    std::vector<double> distances;

    // Sequential Dijkstra
    std::cout << "\nRunning Sequential Dijkstra Algorithm...\n";
    
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();
    sequentialDijkstra(graph, 0, distances);
    // End measuring time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    // Display the distances and execution time
    displayDistances(distances);
    printExecutionTime(duration, "Sequential Dijkstra");
    
    // Parallel Dijkstra
    std::cout << "\nRunning Parallel Dijkstra Algorithm...\n";
    
    // Reset distances
    distances.assign(graph.nodes, 0.0);
    
    // Start measuring time
    start = std::chrono::high_resolution_clock::now();
    parallelDijkstra(graph, 0, distances);
    // End measuring time
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    
    // Display the distances and execution time
    displayDistances(distances);
    printExecutionTime(duration, "Parallel Dijkstra");

    return 0;
}

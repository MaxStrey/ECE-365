#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <chrono>  // Include the chrono header for timing

int main() {
    Graph myGraph;  

    std::string inputFile, outputFile, startVertex;
    std::cout << "Enter the name of the input file: ";
    std::cin >> inputFile;

    if (!myGraph.importGraph(inputFile)) {
        std::cerr << "Failed to import graph from the file." << std::endl;
        return 1;
    }

    std::cout << "Enter the start vertex: ";
    std::cin >> startVertex;

    // Start timing before applying Dijkstra's algorithm
    auto start = std::chrono::high_resolution_clock::now();

    if (!myGraph.applydijkstra(startVertex)) {
        std::cerr << "Failed to apply Dijkstra's algorithm." << std::endl;
        return 1;
    }

    // Stop timing after Dijkstra's algorithm
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken for Dijkstra's algorithm: " << duration.count() << " milliseconds." << std::endl;

    std::cout << "Enter the name of the output file: ";
    std::cin >> outputFile;
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Could not open file " << outputFile << std::endl;
        return 1;
    }

    myGraph.printPaths(outFile);
    outFile.close();

    return 0;
}

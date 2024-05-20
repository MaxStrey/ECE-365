#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <string>
#include <climits>
#include "hash.h"
#include "heap.h"

class Graph {
public:
    Graph();
    ~Graph();
    bool importGraph(const std::string &filename);
    bool applydijkstra(const std::string &startId);
    void printPaths(std::ofstream &outFile);

private:
    class Edge;
    class Vertex {
    public:
        std::string id;
        std::list<Edge> adj;
        bool known;
        int dist;
        Vertex *path;

        Vertex(const std::string &id) : id(id), known(false), dist(INT_MAX), path(nullptr) {}
    };
    class Edge {
    public:
        int cost;
        Vertex *dest;

        Edge(Vertex *d, int c) : dest(d), cost(c) {}
    };

    std::list<Vertex *> vertexList;
    hashTable *vertexMap;
    void addVertex(const std::string &id);
    void addEdge(const std::string &sourceId, const std::string &destId, int cost);
};

#endif // GRAPH_H

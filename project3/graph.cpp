#include "graph.h"
#include <fstream>
#include <iostream>
#include <sstream>

Graph::Graph() {
    vertexMap = new hashTable(1000);  // Assuming a starting size
}

Graph::~Graph() {
    for (auto v : vertexList) {
        delete v;
    }
    delete vertexMap;
}

bool Graph::importGraph(const std::string &filename) {
    std::ifstream file(filename);
    std::string line, vertex1, vertex2;
    int cost;

    if (!file.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
        return false;
    }

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss >> vertex1 >> vertex2 >> cost)) {
            break;  // Error in reading the line
        }
        addVertex(vertex1);
        addVertex(vertex2);
        addEdge(vertex1, vertex2, cost);
    }

    file.close();
    return true;
}

void Graph::addVertex(const std::string &id) {
    if (!vertexMap->contains(id)) {
        Vertex *newVertex = new Vertex(id);
        vertexList.push_back(newVertex);
        vertexMap->insert(id, newVertex);
    }
}

void Graph::addEdge(const std::string &sourceId, const std::string &destId, int cost) {
    Vertex *source = static_cast<Vertex*>(vertexMap->getPointer(sourceId));
    Vertex *dest = static_cast<Vertex*>(vertexMap->getPointer(destId));
    if (source && dest) {
        source->adj.push_back(Edge(dest, cost));
    }
}

bool Graph::applydijkstra(const std::string &startId) {
    std::cout << "Applying Dijkstra's algorithm on vertex: " << startId << std::endl;

    if (!vertexMap->contains(startId)) {
        std::cerr << "Start vertex " << startId << " not found in the graph." << std::endl;
        return false;
    }

    Vertex *startVertex = static_cast<Vertex*>(vertexMap->getPointer(startId));
    if (!startVertex) {
        std::cerr << "Start vertex " << startId << " is null in vertexMap." << std::endl;
        return false;
    }
    std::cout << "Start vertex " << startId << " found with initial distance: " << startVertex->dist << std::endl;

    startVertex->dist = 0;
    heap minHeap(vertexList.size());
    minHeap.insert(startId, 0, startVertex);
    std::cout << "Inserted start vertex in min heap with distance: 0" << std::endl;

    for (auto v : vertexList) {
        if (v->id != startId) {
            minHeap.insert(v->id, v->dist, v);
        }
        v->path = nullptr;
    }

    std::string minId;
    int minDist;
    while (minHeap.deleteMin(&minId, &minDist, nullptr) == 0) {
        Vertex *u = static_cast<Vertex*>(vertexMap->getPointer(minId));
        if (!u) {
            std::cerr << "Vertex " << minId << " is null after deleteMin." << std::endl;
            continue;
        }
        u->known = true;
        std::cout << "Processing vertex: " << u->id << " with current shortest distance: " << u->dist << std::endl;

        for (auto &e : u->adj) {
            Vertex *v = e.dest;
            std::cout << "Checking edge from " << u->id << " to " << v->id << std::endl;
            if (!v->known && u->dist + e.cost < v->dist) {
                v->dist = u->dist + e.cost;
                v->path = u;
                minHeap.setKey(v->id, v->dist);
                std::cout << "Updated distance of vertex " << v->id << " to: " << v->dist << std::endl;
            }
        }
    }
    std::cout << "Dijkstra's algorithm completed." << std::endl;
    return true;
}



void Graph::printPaths(std::ofstream &outFile) {
    for (auto v : vertexList) {
        outFile << v->id << ": ";
        if (v->dist == INT_MAX) {
            outFile << "NO PATH" << std::endl;
        } else {
            outFile << v->dist << " [";
            std::list<std::string> path;
            for (Vertex *p = v; p != nullptr; p = p->path) {
                path.push_front(p->id);
            }
            auto it = path.begin();
            while (it != path.end()) {
                outFile << *it;
                if (++it != path.end()) {
                    outFile << ", ";
                }
            }
            outFile << "]" << std::endl;
        }
    }
}



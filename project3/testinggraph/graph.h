#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <fstream>
#include <list>
#include <string>

#include "hash.h"
#include "heap.h"
using namespace std;

class graph
{
  public:
    // The constructor initializes the graph.
    // Uses hash table implementation to store pointers to the vertices
    graph();

    // Implementation of Dijikstra's algorithm using heap for
    // tracking shortest path lengths
    bool dijkstra(const string &startingV);

    // Checks the vertices hash table to see if a specific vertex
    // exists within it. Returs true if the vertex exists, false otherwise.
    bool containsVertex(const string &vertex);

    // Takes in 2 vertex name strings and a distance int to inset the vertices into
    // the vertices hastable and graph
    void insert(const string &vertex1, const string &vertex2, int dist);

    // Import vertices connected by a positive path cost from a ifstream
    //  If all vertices are imported, returns true.
    bool importGraph(ifstream &in);

    void printPaths(ofstream &out);

  private:
    //size of the graph
    int capacity;
    class edge;
    class vertex;

    class edge
    {
      public:
        int cost;     //edge cost
        vertex *dest; //destination node
    };

    class vertex
    {
      public:
        string name;    //name of the vertex
        list<edge> adj; //adjacency list

        //Dijikstra's algorithm parameters
        bool known;
        int dist;
        list<string> path;
    };

    //list of vertices
    list<vertex *> vertexList;
    //hashtable of vertices
    hashTable *vertices;
};

#endif
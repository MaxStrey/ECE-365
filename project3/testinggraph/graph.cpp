#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"
using namespace std;

// read in the graph as per the specified format in the problem set
bool graph::importGraph(ifstream &in)
{
    string vertex1, vertex2;
    int dist;

    while (in >> vertex1 >> vertex2 >> dist)
    {
        insert(vertex1, vertex2, dist);
    }

    return true;
}

// Initializes graph as a hashtable containing pointers to vertices
graph::graph()
{
    vertices = new hashTable(500000);
    capacity = 0;
}

//  If the vertex exists, it is ignored. If it doesnt exist, it is inserted to the back
//  of the vertices list and added to the vertices hash table. The distance parameter of the vertex is set to INT_MAX
// (to be treated as inf) for the implementation of Dijikstra's.
//  The edge is then set to point to the second vertex and is inserted into the adjacency list of the first vertex
void graph::insert(const string &vertex1, const string &vertex2, int dist)
{
    vertex *temp1, *temp2;
    edge newEdge;

    if (!vertices->contains(vertex1))
    {
        temp1 = new vertex;
        temp1->name = vertex1;
        temp1->known = false;
        temp1->dist = INT_MAX;
        vertexList.push_back(temp1);
        vertices->insert(vertex1, temp1);
        capacity++;
    }
    else
    {
        temp1 = (vertex *)vertices->getPointer(vertex1);
    }

    if (!vertices->contains(vertex2))
    {
        temp2 = new vertex;
        temp2->name = vertex2;
        temp2->known = false;
        temp2->dist = INT_MAX;
        vertexList.push_back(temp2);
        vertices->insert(vertex2, temp2);
        capacity++;
    }
    else
    {
        temp2 = (vertex *)vertices->getPointer(vertex2);
    }
    newEdge.dest = temp2;
    newEdge.cost = dist;

    temp1->adj.push_back(newEdge);
}

// Checks to see if a specific vertex name exists within the vertices hash table
bool graph::containsVertex(const string &vertex)
{
    return (vertices->contains(vertex));
}

// Implementation of Dijikstra's algorithm
bool graph::dijkstra(const string &startingV)
{
    // Takes in a vertex name from useGraph to act as the starting vertex.
    vertex *start = (vertex *)vertices->getPointer(startingV);

    // Initializes  the distance of the starting to be 0 and adds itself to its path
    start->dist = 0;
    start->path.push_back(startingV);

    // Intializes the min distance heap to be used for the algorithm and
    // inserts the starting vertex into the heap
    heap distHeap(capacity);
    distHeap.insert(startingV, start->dist, start);

    // Insert the other vertices into the heap
    for (list<vertex *>::const_iterator it = vertexList.begin(), end = vertexList.end(); it != end; ++it)
    {
        if ((*it)->name != startingV)
        {
            distHeap.insert((*it)->name, (*it)->dist, *it);
        }
    }

    //  Create a temporary vertex for storing the minimum distance vertex while its being operated on
    vertex *temp;
    for (int i = 0; i < capacity; ++i)
    {
        // Delete the min distance vertex to operate on it
        distHeap.deleteMin(nullptr, nullptr, &temp);
        // Look at all of the vertices in its adjacency list and operate on them
        for (list<edge>::const_iterator it = temp->adj.begin(), end = temp->adj.end(); it != end && temp->dist != INT_MAX; ++it)
        {
            // Look at the vertex if it is unknown && its dist is less than the current min distance
            if (!it->dest->known && it->dest->dist > (it->cost + temp->dist))
            {
                it->dest->path.clear();
                it->dest->path.insert(it->dest->path.begin(), temp->path.begin(), temp->path.end());
                it->dest->path.push_back(it->dest->name);

                it->dest->dist = (it->cost + temp->dist);
                distHeap.setKey(it->dest->name, (it->cost + temp->dist));
            }
        }
        // declare the vertex being held by temp
        temp->known = true;
    }

    // return true when the algorithm completes
    return true;
}

// Iterates through the vertecis list to print the min paths in order of vertex entry
void graph::printPaths(std::ofstream &out)
{
    for (list<vertex *>::const_iterator it = vertexList.begin(), end = vertexList.end(); it != end; ++it)
    {
        out << (*it)->name << ": ";

        if ((*it)->dist == INT_MAX)
        {
            out << "NO PATH" << std::endl;
        }
        else
        {
            out << (*it)->dist << " [";
            for (list<string>::const_iterator it2 = (*it)->path.begin(), end2 = (*it)->path.end(); it2 != end2; ++it2)
            {
                out << *it2;
                if (next(it2, 1) != end2)
                    out << ", ";
            }
            out << "]" << endl;
        }
    }
}
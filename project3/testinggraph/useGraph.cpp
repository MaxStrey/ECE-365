#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "graph.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
    string infile, startingV, outfile;
    ifstream inFile;
    ofstream outFile;
    graph g;

    while (!inFile.is_open())
    {
        cout << "Enter a valid graph input file: ";
        cin >> infile;
        inFile.open(infile, ifstream::in);
    }

    g.importGraph(inFile);
    inFile.close();

    while (!g.containsVertex(startingV))
    {
        cout << "Enter a valid starting vertex: ";
        cin >> startingV;
    }

    clock_t begin = clock();
    g.dijkstra(startingV);
    clock_t end = clock();
    double runtime = ((double)(end - begin)) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << runtime << endl;

    while (!outFile.is_open())
    {
        cout << "Enter an output file: ";
        cin >> outfile;
        outFile.open(outfile, ofstream::out | ofstream::trunc);
    }

    g.printPaths(outFile);
    outFile.close();

    return 0;
}
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

using namespace std;

class Graph {
public:
    vector<Node> nodes;
    vector<vector<double>> distanceMatrix;

    void addNode(const Node& node);
    void computeDistanceMatrix();
    void printMatrix();
};

// Utility function
double getRouteDistance(const vector<int>& route,
                        const vector<vector<double>>& dist);

#endif
#include "Graph.h"
#include <cmath>
#include <iostream>

using namespace std;

void Graph::addNode(const Node& node) {
    nodes.push_back(node);
}

double calculateDistance(const Node& a, const Node& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Graph::computeDistanceMatrix() {
    int n = nodes.size();
    distanceMatrix.resize(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distanceMatrix[i][j] = calculateDistance(nodes[i], nodes[j]);
        }
    }
}

void Graph::printMatrix() {
    for (auto &row : distanceMatrix) {
        for (auto &val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// ✅ Utility: Calculate route distance
double getRouteDistance(const vector<int>& route, const vector<vector<double>>& dist) {
    double total = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        total += dist[route[i]][route[i + 1]];
    }
    return total;
}
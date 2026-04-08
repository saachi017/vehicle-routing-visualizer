#include "NearestNeighbor.h"
#include <limits>
#include <iostream>

using namespace std;

vector<int> NearestNeighbor::solve(Graph& graph) {
    int n = graph.nodes.size();
    
    vector<int> unvisited;
    unvisited.reserve(n - 1);
    for (int i = 1; i < n; i++) {
        unvisited.push_back(i);
    }
    
    vector<int> route;
    route.reserve(n + 1);

    int current = 0; // start from depot
    route.push_back(current);

    while (!unvisited.empty()) {
        double minDist = numeric_limits<double>::max();
        int bestIdx = -1;
        int nextNode = -1;

        for (int i = 0; i < unvisited.size(); i++) {
            int candidate = unvisited[i];
            if (graph.distanceMatrix[current][candidate] < minDist) {
                minDist = graph.distanceMatrix[current][candidate];
                nextNode = candidate;
                bestIdx = i;
            }
        }

        route.push_back(nextNode);
        
        // Swap with the last element and pop to avoid O(N) shifting overhead
        unvisited[bestIdx] = unvisited.back();
        unvisited.pop_back();
        
        current = nextNode;
    }

    // return to depot
    route.push_back(0);

    return route;
}
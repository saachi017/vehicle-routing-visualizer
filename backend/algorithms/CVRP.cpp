#include "CVRP.h"
#include <limits>

using namespace std;

vector<vector<int>> CVRP::solve(Graph& graph, int capacity) {
    int n = graph.nodes.size();

    vector<bool> visited(n, false);
    vector<vector<int>> routes;

    visited[0] = true; // depot

    while (true) {
        int current = 0;
        int load = 0;
        vector<int> route;
        route.push_back(0);

        bool found = false;

        while (true) {
            double minDist = numeric_limits<double>::max();
            int nextNode = -1;

            for (int i = 1; i < n; i++) {
                if (!visited[i] &&
                    load + graph.nodes[i].demand <= capacity &&
                    graph.distanceMatrix[current][i] < minDist) {

                    minDist = graph.distanceMatrix[current][i];
                    nextNode = i;
                }
            }

            if (nextNode == -1) break;

            route.push_back(nextNode);
            visited[nextNode] = true;
            load += graph.nodes[nextNode].demand;
            current = nextNode;
            found = true;
        }

        route.push_back(0); // return to depot

        if (!found) break;

        routes.push_back(route);
    }

    return routes;
}
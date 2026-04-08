#include "GreedyInsertion.h"
#include <limits>
#include <list>
#include <iterator>

using namespace std;

vector<int> GreedyInsertion::solve(Graph& graph) {
    int n = graph.nodes.size();

    vector<bool> visited(n, false);
    list<int> routeList;

    // start with depot loop
    routeList.push_back(0);
    routeList.push_back(0);

    visited[0] = true;

    // insert all nodes
    for (int k = 1; k < n; k++) {
        int bestNode = -1;
        auto bestPosIt = routeList.end();
        double bestCost = numeric_limits<double>::max();

        for (int i = 1; i < n; i++) {
            if (visited[i]) continue;

            auto it1 = routeList.begin();
            auto it2 = routeList.begin();
            ++it2;

            while (it2 != routeList.end()) {
                int u = *it1;
                int v = *it2;

                double cost =
                    graph.distanceMatrix[u][i] +
                    graph.distanceMatrix[i][v] -
                    graph.distanceMatrix[u][v];

                if (cost < bestCost) {
                    bestCost = cost;
                    bestNode = i;
                    bestPosIt = it2;
                }

                ++it1;
                ++it2;
            }
        }

        routeList.insert(bestPosIt, bestNode);
        visited[bestNode] = true;
    }

    return vector<int>(routeList.begin(), routeList.end());
}
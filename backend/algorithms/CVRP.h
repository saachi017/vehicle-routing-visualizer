#ifndef CVRP_H
#define CVRP_H

#include "../Graph.h"
#include <vector>

using namespace std;

class CVRP {
public:
    static vector<vector<int>> solve(Graph& graph, int vehicleCapacity);
};

#endif
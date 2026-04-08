#ifndef NEAREST_NEIGHBOR_H
#define NEAREST_NEIGHBOR_H

#include "../Graph.h"
#include <vector>

using namespace std;

class NearestNeighbor {
public:
    static vector<int> solve(Graph& graph);
};

#endif
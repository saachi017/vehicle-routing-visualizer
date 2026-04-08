#ifndef NODE_H
#define NODE_H

using namespace std;

struct Node {
    int id;
    double x, y;
    int demand;

    Node(int id, double x, double y, int demand)
        : id(id), x(x), y(y), demand(demand) {}
};

#endif
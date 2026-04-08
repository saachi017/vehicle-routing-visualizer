#include <iostream>
#include <map>
#include <chrono>

#include "Graph.h"
#include "FileHandler.h"
#include "JSONWriter.h"

#include "algorithms/NearestNeighbor.h"
#include "algorithms/GreedyInsertion.h"
#include "algorithms/CVRP.h"
#include "algorithms/Genetic.h"

using namespace std;
using namespace chrono;

int main() {
    Graph g;

    // INPUT
    int choice;
    cout << "1. CSV\n2. Manual\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        string filename;
        cout << "Enter CSV path: ";
        cin >> filename;
        if (!FileHandler::loadCSV(filename, g)) {
            return 1;
        }
    } else {
        int n;
        cout << "Nodes: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            int id, demand;
            double x, y;
            cin >> id >> x >> y >> demand;
            g.addNode(Node(id, x, y, demand));
        }
    }

    g.computeDistanceMatrix();

    // NN
    auto t1 = high_resolution_clock::now();
    auto nnRoute = NearestNeighbor::solve(g);
    auto t2 = high_resolution_clock::now();
    double nnTime = duration<double, milli>(t2 - t1).count();
    double nnDist = getRouteDistance(nnRoute, g.distanceMatrix);

    // Greedy
    t1 = high_resolution_clock::now();
    auto giRoute = GreedyInsertion::solve(g);
    t2 = high_resolution_clock::now();
    double giTime = duration<double, milli>(t2 - t1).count();
    double giDist = getRouteDistance(giRoute, g.distanceMatrix);

    // Genetic
    t1 = high_resolution_clock::now();
    auto gaRoute = Genetic::solve(g);
    t2 = high_resolution_clock::now();
    double gaTime = duration<double, milli>(t2 - t1).count();
    double gaDist = getRouteDistance(gaRoute, g.distanceMatrix);

   // -----------------------------
   // STORE RESULTS
// -----------------------------
   map<string, pair<double, double>> results;

   results["Nearest Neighbor"] = {nnDist, nnTime};
   results["Greedy Insertion"] = {giDist, giTime};
   results["Genetic"] = {gaDist, gaTime};

// -----------------------------
// FIND BEST
// -----------------------------
   string bestAlgo = "Nearest Neighbor";
   double bestDist = nnDist;

   if (giDist < bestDist) {
      bestDist = giDist;
      bestAlgo = "Greedy Insertion";
   }

   if (gaDist < bestDist) {
      bestDist = gaDist;
      bestAlgo = "Genetic";
   }

   cout << "\nBest Algorithm: " << bestAlgo << endl;

// -----------------------------
// WRITE JSON
// -----------------------------
   if (!JSONWriter::write("output.json",
                  results,
                  bestAlgo,
                  nnRoute,
                  giRoute,
                  gaRoute,
                  g)) {
       return 1;
   }

  return 0;
}
#include "JSONWriter.h"
#include <fstream>
#include <iostream>

using namespace std;

bool JSONWriter::write(const string& filename,
                       const map<string, pair<double, double>>& results,
                       const string& bestAlgo,
                       const vector<int>& nnRoute,
                       const vector<int>& giRoute,
                       const vector<int>& gaRoute,
                       const Graph& graph) {

    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening JSON file!" << endl;
        return false;
    }

    file << "{\n";

    // 🔹 Results (distance + time)
    file << "\"results\": {\n";
    int count = 0;
    for (auto& pair : results) {
        file << "\"" << pair.first << "\": { ";
        file << "\"distance\": " << pair.second.first << ", ";
        file << "\"time\": " << pair.second.second << " }";

        count++;
        if (count != results.size()) file << ",";
        file << "\n";
    }
    file << "},\n";

    // 🔹 Best algorithm
    file << "\"best\": \"" << bestAlgo << "\",\n";

    // 🔹 Nodes
    file << "\"nodes\": [\n";
    for (int i = 0; i < graph.nodes.size(); i++) {
        file << "{ \"id\": " << graph.nodes[i].id
             << ", \"x\": " << graph.nodes[i].x
             << ", \"y\": " << graph.nodes[i].y << " }";

        if (i != graph.nodes.size() - 1) file << ",";
        file << "\n";
    }
    file << "],\n";

    // 🔹 ALL ROUTES
    file << "\"routes\": {\n";

    file << "\"Nearest Neighbor\": [";
    for (int i = 0; i < nnRoute.size(); i++) {
        file << nnRoute[i];
        if (i != nnRoute.size() - 1) file << ", ";
    }
    file << "],\n";

    file << "\"Greedy Insertion\": [";
    for (int i = 0; i < giRoute.size(); i++) {
        file << giRoute[i];
        if (i != giRoute.size() - 1) file << ", ";
    }
    file << "],\n";

    file << "\"Genetic\": [";
    for (int i = 0; i < gaRoute.size(); i++) {
        file << gaRoute[i];
        if (i != gaRoute.size() - 1) file << ", ";
    }
    file << "]\n";

    file << "}\n";

    file << "}\n";

    file.close();

    cout << "JSON written successfully!\n";
    return true;
}
#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool FileHandler::loadCSV(const string& filename, Graph& graph) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return false;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string value;

        int id, demand;
        double x, y;

        getline(ss, value, ',');
        id = stoi(value);

        getline(ss, value, ',');
        x = stod(value);

        getline(ss, value, ',');
        y = stod(value);

        getline(ss, value, ',');
        demand = stoi(value);

        graph.addNode(Node(id, x, y, demand));
    }

    file.close();
    return true;
}
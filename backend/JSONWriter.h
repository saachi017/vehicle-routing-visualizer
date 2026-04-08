#ifndef JSON_WRITER_H
#define JSON_WRITER_H

#include <vector>
#include <string>
#include <map>
#include "Graph.h"

using namespace std;

class JSONWriter {
public:
    static bool write(const string& filename,
                      const map<string, pair<double, double>>& results,
                      const string& bestAlgo,
                      const vector<int>& nnRoute,
                      const vector<int>& giRoute,
                      const vector<int>& gaRoute,
                      const Graph& graph);
};

#endif
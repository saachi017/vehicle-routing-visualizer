#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include "Graph.h"

using namespace std;

class FileHandler {
public:
    static bool loadCSV(const string& filename, Graph& graph);
};

#endif
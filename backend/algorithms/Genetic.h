#ifndef GENETIC_H
#define GENETIC_H

#include "../Graph.h"
#include <vector>
#include <random>

using namespace std;

class Genetic {
public:
    static vector<int> solve(const Graph& graph);

private:
    static vector<vector<int>> initializePopulation(int size, int n, mt19937& rng);
    static double fitness(const vector<int>& route, const Graph& graph);
    static vector<int> selection(const vector<vector<int>>& population, const Graph& graph, mt19937& rng);
    static vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2, mt19937& rng);
    static void mutate(vector<int>& route, mt19937& rng);
};

#endif
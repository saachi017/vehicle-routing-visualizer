#include "Genetic.h"
#include <algorithm>
#include <random>
#include <limits>

using namespace std;

// 🔹 Initialize population
vector<vector<int>> Genetic::initializePopulation(int size, int n, mt19937& rng) {
    vector<vector<int>> population;

    vector<int> base;
    for (int i = 1; i < n; i++) base.push_back(i);

    for (int i = 0; i < size; i++) {
        vector<int> individual = base;
        shuffle(individual.begin(), individual.end(), rng);

        individual.insert(individual.begin(), 0);
        individual.push_back(0);

        population.push_back(individual);
    }

    return population;
}

// 🔹 Fitness (lower distance = better)
double Genetic::fitness(const vector<int>& route, const Graph& graph) {
    return getRouteDistance(route, graph.distanceMatrix);
}

// 🔹 Selection (tournament)
vector<int> Genetic::selection(const vector<vector<int>>& population, const Graph& graph, mt19937& rng) {
    uniform_int_distribution<int> dist(0, population.size() - 1);
    int i1 = dist(rng);
    int i2 = dist(rng);

    if (fitness(population[i1], graph) < fitness(population[i2], graph))
        return population[i1];
    return population[i2];
}

// 🔹 Crossover (simple ordered crossover)
vector<int> Genetic::crossover(const vector<int>& p1, const vector<int>& p2, mt19937& rng) {
    int n = p1.size();
    vector<int> child(n, -1);

    uniform_int_distribution<int> distStart(1, n - 3);
    int start = distStart(rng);
    uniform_int_distribution<int> distEnd(start, n - 2);
    int end = distEnd(rng);

    // Copy segment
    vector<bool> inChild(n, false);
    for (int i = start; i <= end; i++) {
        child[i] = p1[i];
        inChild[p1[i]] = true;
    }

    // Fill remaining from p2
    int idx = 1;
    for (int i = 1; i < n - 1; i++) {
        if (!inChild[p2[i]]) {
            while (child[idx] != -1) idx++;
            child[idx] = p2[i];
        }
    }

    child[0] = 0;
    child[n - 1] = 0;

    return child;
}

// 🔹 Mutation (swap)
void Genetic::mutate(vector<int>& route, mt19937& rng) {
    int n = route.size();

    uniform_int_distribution<int> dist(1, n - 2);
    int i = dist(rng);
    int j = dist(rng);

    swap(route[i], route[j]);
}

// 🔹 Main solver
vector<int> Genetic::solve(const Graph& graph) {
    int populationSize = 50;
    int generations = 200;

    int n = graph.nodes.size();

    random_device rd;
    mt19937 rng(rd());

    auto population = initializePopulation(populationSize, n, rng);

    for (int gen = 0; gen < generations; gen++) {
        vector<vector<int>> newPopulation;

        for (int i = 0; i < populationSize; i++) {
            vector<int> parent1 = selection(population, graph, rng);
            vector<int> parent2 = selection(population, graph, rng);

            vector<int> child = crossover(parent1, parent2, rng);

            uniform_int_distribution<int> dist(0, 99);
            if (dist(rng) < 20) {
                mutate(child, rng);
            }

            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    // Find best
    double bestDist = numeric_limits<double>::max();
    vector<int> bestRoute;

    for (auto& route : population) {
        double dist = fitness(route, graph);
        if (dist < bestDist) {
            bestDist = dist;
            bestRoute = route;
        }
    }

    return bestRoute;
}
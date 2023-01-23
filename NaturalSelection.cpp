#include <iostream>
#include <algorithm>
#include <random>

const int POPULATION_SIZE = 100;
const int NUM_GENERATIONS = 100;
const double MUTATION_RATE = 0.01;

class Organism {
public:
    double fitness;
    std::vector<double> genes;

    Organism() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        for (int i = 0; i < 10; i++) {
            genes.push_back(dis(gen));
        }

        fitness = 0;
    }

    Organism(const std::vector<double>& g) {
        genes = g;
        fitness = 0;
    }

    void mutate() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        for (int i = 0; i < genes.size(); i++) {
            if (dis(gen) < MUTATION_RATE) {
                genes[i] = dis(gen);
            }
        }
    }
};

std::vector<Organism> population;

void init() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population.push_back(Organism());
    }
}

void eval() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        double sum = 0;
        for (int j = 0; j < population[i].genes.size(); j++) {
            sum += population[i].genes[j];
        }
        population[i].fitness = sum;
    }
}

Organism select() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double total_fitness = 0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        total_fitness += population[i].fitness;
    }

    double rand = dis(gen) * total_fitness;
    double running_total = 0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        running_total += population[i].fitness;
        if (running_total > rand) {
            return population[i];
        }
    }
}

std::vector<Organism> reproduce(const Organism& a, const Organism& b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    int crossover = dis(gen);
    std::vector<double> offspring1, offspring2;

    for (int i = 0; i < crossover; i++) {
        offspring1.push_back(a

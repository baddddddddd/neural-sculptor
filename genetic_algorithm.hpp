#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include "math_functions.hpp"
#include "sampler.hpp"
#include "neural_network.hpp"
#include "loss_functions.hpp"
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationPerGen) {
        population.reserve(populationPerGen);

        for (int i = 0; i < populationPerGen; i++) {
            population.emplace_back(std::vector<int>{ 1, 32,1 });
        }
    }  

    void selectNextGen() {
        float a = -10;
        float b = 10;
        int n = 200;

        auto expectedPoints = samplePointsY(MathFunctions::mexican_hat_wavelet, a, b, n);

        std::unordered_map<int, float> scores;

        for (int i = 0; i < population.size(); i++) {
            auto observedPoints = samplePointsY([this, i](float x) {
                std::vector<float> input;
                input.push_back(x);

                auto output = population[i].feed(input);
                return output[0];
            }, a, b, n);

            float error = mean_squared_error(expectedPoints, observedPoints);

            scores[i] = error;
        }

        // sort

        std::vector<std::pair<int, float>> items(scores.begin(), scores.end());

        std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        leaderboard = items;

        population[0] = population[leaderboard[0].first];
        std::cout << leaderboard[0].second << std::endl;


        int firstThird = population.size() / 4;
        int secondThird = firstThird * 2;
        int thirdThird = firstThird * 3;

        for (int i = 1; i < firstThird; i++) {
            population[i] = population[0];
            population[i].mutate(0.1);
        }

        for (int i = firstThird; i < secondThird; i++) {
            population[i] = population[0];
            population[i].mutate(0.01);
        }

        for (int i = secondThird; i < thirdThird; i++) {
            population[i] = population[0];
            population[i].mutate(0.001);
        }

        for (int i = thirdThird; i < population.size(); i++) {
            population[i] = population[0];
            population[i].mutate(0.0001);
        }
    }

    const NeuralNetwork& getTop() {
        return population[leaderboard[0].first];
    }

private:
    std::vector<NeuralNetwork> population;
    std::vector<std::pair<int, float>> leaderboard;

};


#endif // GENETIC_ALGORITHM_HPP
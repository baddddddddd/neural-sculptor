#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include "activation_functions.hpp"
#include <random>
#include <vector>
#include <functional>

class Layer {
public:
    Layer(int inputSize, int outputSize) : inputSize(inputSize), outputSize(outputSize) {
        biases.resize(outputSize, 0.0f);
        weights.resize(outputSize, std::vector<float>(inputSize));
        output.resize(outputSize);

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> dis(-1, 1);

        for (int i = 0; i < outputSize; i++) {
            for (int j = 0; j < inputSize; j++) {
                // weights[i][j] = 0.0f;
                weights[i][j] = dis(gen);
            }
        }
    }

    std::vector<float> forward(const std::vector<float>& input, std::function<float(float)> activationFunction) {
        for (int i = 0; i < outputSize; i++) {
            float sum = biases[i];
            for (int j = 0; j < inputSize; j++) {
                sum += input[j] * weights[i][j];
            }
            output[i] = activationFunction(sum);
        }
        return output;
    }

    void mutate(float delta) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> dis(-delta, delta);

        for (int i = 0; i < outputSize; i++) {
            for (int j = 0; j < inputSize; j++) {
                // weights[i][j] = 0.0f;
                weights[i][j] += dis(gen);
            }

            biases[i] += dis(gen);
        }
    }

private:
    int inputSize;
    int outputSize;

    std::vector<float> output;
    std::vector<float> biases;
    std::vector<std::vector<float>> weights;

};

class NeuralNetwork {
public:
    NeuralNetwork(const std::vector<int>& neuronsPerLayer) {
        for (int i = 0; i < neuronsPerLayer.size() - 1; i++) {
            layers.emplace_back(neuronsPerLayer[i], neuronsPerLayer[i + 1]);
        }
    }

    std::vector<float> feed(const std::vector<float>& input) {
        std::vector<float> output = input;

        for (int i = 0; i < layers.size() - 1; i++) {
            output = layers[i].forward(output, tanh);
        }

        output = layers[layers.size() - 1].forward(output, identity);
        return output;
    }

    void mutate(float delta) {
        for (int i = 0; i < layers.size(); i++) {
            layers[i].mutate(delta);
        }
    }

private:
    std::vector<Layer> layers;

};

#endif // NEURAL_NETWORK_HPP
#ifndef ACTIVATION_FUNCTIONS_HPP
#define ACTIVATION_FUNCTIONS_HPP

#include <algorithm>
#include <cmath>

float identity(float x) {
    return x;
}

float heaviside_step(float x) {
    return (x >= 0) ? 1 : 0;
}

float relu(float x) {
    return std::max(0.0f, x);
}

float sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
}

#endif // ACTIVATION_FUNCTIONS_HPP
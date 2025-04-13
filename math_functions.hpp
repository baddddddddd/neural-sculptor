#ifndef MATH_FUNCTIONS_HPP
#define MATH_FUNCTIONS_HPP

#include <cmath>
#include <functional>

namespace MathFunctions {

    inline std::function<float(float)> piecewise_polynomial = [](float x) {
        return (x < 0) ? (x * x * x + 2 * x + 1) : (-2 * x * x * x + 3 * x * x + 4);
    };

    inline std::function<float(float)> sine_exponential_combined = [](float x) {
        return std::sin(x) + std::exp(-x * x / 20);
    };

    inline std::function<float(float)> rational_oscillation = [](float x) {
        return std::sin(x) / (1 + x * x);
    };

    inline std::function<float(float)> gaussian_sine_mixture = [](float x) {
        return std::exp(-0.2f * x * x) * std::sin(5 * x);
    };

    inline std::function<float(float)> piecewise_sine = [](float x) {
        if (x < -5) return 2 * std::sin(x);
        if (x < 5) return std::sin(x);
        return 3 * std::sin(x);
    };

    inline std::function<float(float)> polynomial_5th_degree = [](float x) {
        return 0.1f * std::pow(x, 5) - 2 * std::pow(x, 4) + 3 * std::pow(x, 3) - 4 * std::pow(x, 2) + 5 * x - 6;
    };

    inline std::function<float(float)> sinusoidal_polynomial = [](float x) {
        return std::sin(x) + 0.1f * std::pow(x, 4) - 2 * std::pow(x, 3) + std::pow(x, 2);
    };

    inline std::function<float(float)> absolute_exponential_decay = [](float x) {
        return std::abs(x) * std::exp(-0.1f * x * x);
    };

    inline std::function<float(float)> bump_function = [](float x) {
        return std::exp(-x * x) / (1 + std::exp(-x * x));
    };

    inline std::function<float(float)> mexican_hat_wavelet = [](float x) {
        return (1 - (x * x) / 2.0f) * std::exp(-x * x / 2.0f);
    };

        inline std::function<float(float)> discontinuous_step = [](float x) {
        return (x < 0) ? -1.0f : 1.0f;
    };

    inline std::function<float(float)> high_freq_sine = [](float x) {
        return std::sin(20.0f * x);
    };

    inline std::function<float(float)> exponential_spike = [](float x) {
        return std::exp(-100.0f * (x - 1.0f) * (x - 1.0f));
    };

    inline std::function<float(float)> sawtooth_wave = [](float x) {
        return 2.0f * (x / M_PI - std::floor(x / M_PI + 0.5f));
    };

    inline std::function<float(float)> logistic_function = [](float x) {
        return 1.0f / (1.0f + std::exp(-x));
    };

    inline std::function<float(float)> chaotic_logistic_map = [](float x) {
        float r = 3.7f;
        return r * x * (1 - x); // domain: x in [0,1]
    };

    inline std::function<float(float)> absolute_sine = [](float x) {
        return std::abs(std::sin(x));
    };

    inline std::function<float(float)> ripple_function = [](float x) {
        return std::sin(10.0f * x) / (1 + x * x);
    };

    inline std::function<float(float)> smooth_relu = [](float x) {
        return std::log(1.0f + std::exp(x)); // softplus
    };

    inline std::function<float(float)> spiky_sine = [](float x) {
        return std::sin(x) + 0.3f * std::sin(15 * x);
    };


}

#endif // MATH_FUNCTIONS_HPP

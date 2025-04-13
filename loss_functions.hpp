#ifndef LOSS_FUNCTIONS_HPP
#define LOSS_FUNCTIONS_HPP

#include <vector>

float mean_squared_error(const std::vector<float>& a, const std::vector<float>& b) {
    size_t n = a.size();
    float sum = 0;
    for (size_t i = 0; i < n; ++i) {
        float diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sum / n;
}

float sum_squared_error(const std::vector<float>& a, const std::vector<float>& b) {
    size_t n = a.size();
    float sum = 0;
    for (size_t i = 0; i < n; ++i) {
        float diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sum;
}

#endif // LOSS_FUNCTIONS_HPP
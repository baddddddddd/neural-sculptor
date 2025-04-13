#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <functional>


template <typename Func>
std::vector<sf::Vector2f> samplePoints(Func func, float a, float b, int n) {
    float range = b - a;
    float width = range / n;

    std::vector<sf::Vector2f> points;

    for (int i = 0; i < n; i++) {
        float x = a + i * width;
        float y = func(x);
        points.emplace_back(x, y);
    }

    return points;
}

template <typename Func>
std::vector<float> samplePointsY(Func func, float a, float b, int n) {
    float range = b - a;
    float width = range / n;

    std::vector<float> points;

    for (int i = 0; i < n; i++) {
        float x = a + i * width;
        float y = func(x);
        points.push_back(y);
    }

    return points;
}

#endif // SAMPLER_HPP
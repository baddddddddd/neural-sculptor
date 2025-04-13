#ifndef GRAPHING_HPP
#define GRAPHING_HPP

#include "sampler.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <functional>
#include <iostream>

class Graphing {
public:
    Graphing(sf::RenderWindow& window) : window(window), center(0.0f, 0.0f) {
        xZoom = 8;
        yZoom = 6;
    }

    sf::Vertex toVertex(const sf::Vector2f& point) {
        int windowWidth = window.getSize().x;
        int windowHeight = window.getSize().y;

        float pixelsPerX = windowWidth / xZoom;
        float pixelsPerY = windowHeight / yZoom;

        float offsetX = center.x * pixelsPerX;
        float offsetY = center.y * pixelsPerY;

        float centerX = windowWidth / 2.0f - offsetX;
        float centerY = windowHeight / 2.0f + offsetY;

        float renderedX = centerX + point.x * pixelsPerX;
        float renderedY = centerY - point.y * pixelsPerY;

        return sf::Vertex{sf::Vector2f(renderedX, renderedY)};
    }

    std::vector<sf::Vertex> toVertices(const std::vector<sf::Vector2f>& points) {
        std::vector<sf::Vertex> vertices(points.size());

        for (int i = 0; i < points.size(); i++) {
            vertices.push_back(toVertex(points[i]));
        }

        return vertices;
    }

    void drawVertices(const std::vector<sf::Vertex>& vertices) {
        window.draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);
    }


    template <typename Func>
    void draw(Func func) {
        int a = center.x - xZoom;
        int b = center.x + xZoom;
        int n = window.getSize().x / 2;

        auto points = samplePoints(func, a, b, n);
        auto vertices = toVertices(points);
        drawVertices(vertices);
    }

    void move(const sf::Vector2i& delta) {
        int windowWidth = window.getSize().x;
        int windowHeight = window.getSize().y;

        float centerX = windowWidth / 2.0f;
        float centerY = windowHeight / 2.0f;

        float pixelsPerX = windowWidth / xZoom;
        float pixelsPerY = windowHeight / yZoom;

        float deltaX = delta.x / pixelsPerX;
        float deltaY = delta.y / pixelsPerY;

        center += {-deltaX, deltaY};
    }

    void zoom(float delta) {
        xZoom += xZoom * 0.1 * delta;
        yZoom += yZoom * 0.1 * delta;
    }

private:
    sf::RenderWindow& window;

    sf::Vector2f center;
    float xZoom;
    float yZoom;

};

#endif // GRAPHING_HPP
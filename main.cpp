#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <functional>
#include <iostream>
#include "activation_functions.hpp"
#include "genetic_algorithm.hpp"
#include "graphing.hpp"
#include "loss_functions.hpp"
#include "math_functions.hpp"
#include "neural_network.hpp"
#include "sampler.hpp"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Approx");
    window.setFramerateLimit(60);

    Graphing graph(window);

    sf::Vector2i referencePoint;
    bool isMouseButtonHeld = false;

    GeneticAlgorithm evo(40);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                referencePoint = mouseEvent->position;
                isMouseButtonHeld = true;
            }
            else if (auto mouseEvent = event->getIf<sf::Event::MouseMoved>()) {
                if (isMouseButtonHeld) {
                    auto curPosition = mouseEvent->position;
                    auto deltaPosition = curPosition - referencePoint;
                    referencePoint = curPosition;
                    graph.move(deltaPosition);
                }
            }
            else if (auto mouseEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
                isMouseButtonHeld = false;
            }

            else if (auto mouseEvent = event->getIf<sf::Event::MouseWheelScrolled>()) {
                graph.zoom(mouseEvent->delta);
            }
        }

        window.clear(sf::Color::Black);

        graph.draw(MathFunctions::mexican_hat_wavelet);

        
        evo.selectNextGen();
        auto top = evo.getTop();
        graph.draw([&](float x) {
            std::vector<float> input;
            input.push_back(x);

            auto output = top.feed(input);
            return output[0];
        });


        window.display();
    }
}
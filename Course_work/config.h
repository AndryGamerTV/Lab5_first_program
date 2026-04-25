#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Config 
{
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 800;
    const std::string WINDOW_TITLE = "Cursova";
    constexpr int FPS_LIMIT = 60;

    namespace Colors 
    {
        const sf::Color WHITE = sf::Color::White;
        const sf::Color RED = sf::Color::Red;
        const sf::Color GREEN = sf::Color::Green;
        const sf::Color BLUE = sf::Color::Blue;
        const sf::Color YELLOW = sf::Color::Yellow;
        const sf::Color MAGENTA = sf::Color::Magenta;
        const sf::Color CYAN = sf::Color::Cyan;
        const sf::Color BACKGROUND = sf::Color::White;
    }

    namespace Trail 
    {
        constexpr size_t MAX_LENGTH = 50;
    }

    namespace Movement 
    {
        constexpr float SINE_FREQUENCY_X = 1.5f;
        constexpr float SINE_AMPLITUDE = 1.0f;
    }
}
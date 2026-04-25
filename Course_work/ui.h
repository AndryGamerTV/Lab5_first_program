#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ui {
    sf::Font font;
    bool     fontLoaded;

public:
    ui();
    bool loadFont();
    void drawHUD(sf::RenderWindow& window, int objectCount, int selectedIndex,
        const std::string& selectedType);
    void drawInfo(sf::RenderWindow& window, const std::string& message);
    const sf::Font& getFont() const { return font; }
};
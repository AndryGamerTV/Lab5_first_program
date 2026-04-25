#include "ui.h"
#include <iostream>

ui::ui() : fontLoaded(false) {}

bool ui::loadFont() 
{
    const char* fontPaths[] = 
    {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/segoeui.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "arial.ttf",
        nullptr
    };
    for (int i = 0; fontPaths[i]; ++i) 
    {
        if (font.loadFromFile(fontPaths[i])) 
        {
            fontLoaded = true;
            return true;
        }
    }
    std::cerr << "Warning: could not load font\n";
    return false;
}

void ui::drawHUD(sf::RenderWindow& window, int objectCount, int selectedIndex,
    const std::string& selectedType) 
{
    if (!fontLoaded) return;
    float W = (float)window.getSize().x;
    float H = (float)window.getSize().y;

    auto txt = [&](const std::string& s, float x, float y,
        sf::Color col = sf::Color::Black, unsigned sz = 16u) 
        {
            sf::Text t;
            t.setFont(font);
            t.setString(s);
            t.setCharacterSize(sz);
            t.setFillColor(col);
            t.setPosition(x, y);
            window.draw(t);
        };

    txt("Objects: " + std::to_string(objectCount), 10, 10);
    if (selectedIndex >= 0)
        txt("Selected [" + std::to_string(selectedIndex) + "]: " + selectedType, 10, 32);

    std::string help =
        "    Controls    \n"
        "LMB          - select figure\n"
        "LMB + Ctrl   - add to selection\n"
        "Arrows       - move\n"
        "+/-          - scale\n"
        "1, 2, 3      - add rectangle / circle / triangle\n"
        "A            - create aggregate\n"
        "V            - visible / invisible\n"
        "M            - auto move\n"
        "T            - trace\n"
        "R            - reset to initial state\n"
        "C            - change color\n"
        "Delete       - delete\n"
        "S            - save prototype\n"
        "L            - load prototype\n"
        "Ctrl+S       - save scene to file\n"
        "Ctrl+L       - load scene from file";
    
    txt(help, 10, H - 320.0f, sf::Color::Black, 13u);
}

void ui::drawInfo(sf::RenderWindow& window, const std::string& message) 
{
    if (!fontLoaded || message.empty()) return;
    sf::Text t;
    t.setFont(font);
    t.setString(message);
    t.setCharacterSize(20);
    t.setFillColor(sf::Color::Black);
    t.setPosition(10.0f, (float)window.getSize().y / 2.0f - 10.0f);
    window.draw(t);
}

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Config.h"
#include "Controller.h"
#include "Aggregate.h"
#include "Prototype.h"
#include "ui.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT),
        Config::WINDOW_TITLE);
    window.setFramerateLimit(Config::FPS_LIMIT);

    Controller& scene = Controller::getInstance();
    Controller& scene2 = Controller::getInstance();

    ui ui;
    ui.loadFont();

    sf::Clock clock;
    int colorIndex = 0;
    const std::vector<sf::Color> colors = 
    {
        Config::Colors::RED,     
        Config::Colors::GREEN,
        Config::Colors::BLUE,    
        Config::Colors::YELLOW,
        Config::Colors::MAGENTA, 
        Config::Colors::CYAN
    };
    auto nextColor = [&]() { return colors[colorIndex++ % (int)colors.size()]; };

    const float CX = Config::WINDOW_WIDTH / 2.0f;
    const float CY = Config::WINDOW_HEIGHT / 2.0f;

    std::string lastMessage;
    float messageTimer = 0.0f;

    const std::vector<std::string> shapeNames = 
    {
        "Square", "Circle", "Triangle", "Aggregate"
    };

    while (window.isOpen()) 
    {
        float dt = clock.restart().asSeconds();
        if (messageTimer > 0.0f) messageTimer -= dt;
        else lastMessage.clear();

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) 
            {
                sf::Keyboard::Key key = event.key.code;

                for (int i = 0; i < 4; ++i) 
                {
                    if (key == sf::Keyboard::Num1 + i ||
                        key == sf::Keyboard::Numpad1 + i) 
                    {
                        sf::Color col = nextColor();
                        FigureDetails* obj =
                            scene.createFromPrototype(shapeNames[i], CX, CY, col);
                        if (obj) 
                        {
                            scene.addObject(obj);
                            lastMessage = shapeNames[i] + " created";
                            messageTimer = 2.0f;
                        }
                    }
                }

                if (key == sf::Keyboard::Tab) 
                {
                    if (event.key.shift) scene.selectPrevious();
                    else scene.selectNext();
                }
                if (key == sf::Keyboard::Delete) scene.removeSelected();

                FigureDetails* sel = scene.getSelected();

                if (key == sf::Keyboard::M && sel) 
                {
                    if (sel->isMoving()) sel->stopAutoMove();
                    else sel->startAutoMove();
                }
                if (key == sf::Keyboard::R && sel) sel->reset();
                if (key == sf::Keyboard::T && sel) sel->toggleTrail();
                if (key == sf::Keyboard::V && sel) sel->toggleVisibility();
                if (key == sf::Keyboard::C && sel) sel->changeColor(nextColor());
                if (key == sf::Keyboard::Add || key == sf::Keyboard::Equal) 
                {
                    if (sel) sel->deform(0.1f);
                }
                if (key == sf::Keyboard::Subtract || key == sf::Keyboard::Hyphen) 
                {
                    if (sel) sel->deform(-0.1f);
                }

                if (key == sf::Keyboard::A) 
                {
                    if (scene.multiSelection.size() > 0) 
                    {
                        scene.extractAndGroupSelected(CX, CY);
                        lastMessage = "Grouped into Aggregate";
                        messageTimer = 2.0f;
                    } else 
                    {
                        lastMessage = "Select at least 2 figures using Ctrl+LMB";
                        messageTimer = 2.0f;
                    }
                }

                const float STEP = 5.0f;
                if (sel) 
                {
                    if (key == sf::Keyboard::Left)  
                        sel->move(-STEP, 0);
                    if (key == sf::Keyboard::Right) 
                        sel->move(STEP, 0);
                    if (key == sf::Keyboard::Up)    
                        sel->move(0, -STEP);
                    if (key == sf::Keyboard::Down)  
                        sel->move(0, STEP);
                }

                if (key == sf::Keyboard::S) 
                {
                    if (event.key.control) 
                    {
                        std::cout << "Enter filename to save scene: ";
                        std::string filename;
                        std::cin >> filename;
                        scene.saveToFile(filename);
                        lastMessage = "Saved scene to " + filename;
                    } else 
                    {
                        if (sel) 
                        {
                            std::cout << "Enter name for new prototype: ";
                            std::string protoName;
                            std::cin >> protoName;
                            Prototype::getInstance().registerPrototype(protoName, sel->createClone());
                            lastMessage = "Saved prototype as " + protoName;
                        } else 
                        {
                            lastMessage = "No figure selected to save";
                        }
                    }
                    messageTimer = 2.0f;
                }
                if (key == sf::Keyboard::L) 
                {
                    if (event.key.control) 
                    {
                        std::cout << "Enter filename to load scene: ";
                        std::string filename;
                        std::cin >> filename;
                        scene.loadFromFile(filename);
                        lastMessage = "Loaded scene from " + filename;
                    } else 
                    {
                        std::cout << "Enter prototype name to create: ";
                        std::string protoName;
                        std::cin >> protoName;
                        sf::Color col = nextColor();
                        FigureDetails* obj = scene.createFromPrototype(protoName, CX, CY, col);
                        if (obj) 
                        {
                            scene.addObject(obj);
                            lastMessage = "Created " + protoName;
                        } else 
                        {
                            lastMessage = "Prototype " + protoName + " not found!";
                        }
                    }
                    messageTimer = 2.0f;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2f mp((float)event.mouseButton.x, (float)event.mouseButton.y);

                float minDist = 1e9f;
                int bestIdx = -1;

                const auto& objs = scene.getObjects();
                for (size_t i = 0; i < objs.size(); ++i) 
                {
                    sf::Vector2f d = objs[i]->getPosition() - mp;
                    float dist = d.x * d.x + d.y * d.y;
                    if (dist < minDist) { minDist = dist; bestIdx = (int)i; 
                    }}
                if (bestIdx >= 0 && minDist < 60.0f * 60.0f) 
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
                        scene.toggleMultiSelection(bestIdx);
                    } else 
                    {
                        scene.clearMultiSelection();

                        if ((int)objs.size() > 0) 
                        {
                            int cur = scene.getSelectedIndex();
                            if (cur < 0) cur = 0;
                            int steps = 0;
                            while (scene.getSelectedIndex() != bestIdx &&
                                steps < (int)objs.size()) 
                            {
                                scene.selectNext();
                                ++steps;
                            }
                        }
                    }
                } else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) 
                {
                    scene.clearMultiSelection();
                }
            }
        }

        scene.updateAll(dt);

        window.clear(Config::Colors::BACKGROUND);
        scene.drawAll(window);

        FigureDetails* selObj = scene.getSelected();
        std::string    selType = selObj ? selObj->createMemento().getType() : "none";
        ui.drawHUD(window, (int)scene.getObjectCount(),
            scene.getSelectedIndex(), selType);
        if (messageTimer > 0.0f)
            ui.drawInfo(window, lastMessage);

        window.display();
    }
    return 0;
}
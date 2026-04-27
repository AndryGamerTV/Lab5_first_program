#include <SFML/Graphics.hpp>
#include <iostream>
#include "Controller.h"
#include "FigureProxy.h"
#include "Square.h"
#include "Circle.h"
#include "Triangle.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Proxy Pattern");
    window.setFramerateLimit(60);

    Controller controller;

    float W = 800.0f;
    float H = 600.0f;

    sf::Font font;
    bool font_loaded = font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                sf::Keyboard::Key key = event.key.code;

                if (key == sf::Keyboard::Num1) {
                    Figure* sq = new Square(200, 300, 50, sf::Color::Red);
                    controller.add_current(new FigureProxy(sq));
                }
                if (key == sf::Keyboard::Num2) {
                    Figure* ci = new Circle(400, 300, 40, sf::Color::Green);
                    controller.add_current(new FigureProxy(ci));
                }
                if (key == sf::Keyboard::Num3) {
                    Figure* tr = new Triangle(600, 300, 50, sf::Color::Blue);
                    controller.add_current(new FigureProxy(tr));
                }

                if (key == sf::Keyboard::Tab) controller.next_figure();
                if (key == sf::Keyboard::R)   controller.restore_current();

                const float STEP = 5.0f;
                if (key == sf::Keyboard::Left)  controller.move_current(-STEP, 0, W, H);
                if (key == sf::Keyboard::Right) controller.move_current(STEP, 0, W, H);
                if (key == sf::Keyboard::Up)    controller.move_current(0, -STEP, W, H);
                if (key == sf::Keyboard::Down)  controller.move_current(0, STEP, W, H);
            }
        }

        window.clear(sf::Color(30, 30, 30));
        controller.draw_all(&window);

        if (font_loaded) {
            sf::Text info;
            info.setFont(font);
            info.setCharacterSize(14);
            info.setFillColor(sf::Color::White);
            info.setPosition(10, 10);
            info.setString(
                "1/2/3 - add Square/Circle/Triangle\n"
                "Arrows - move\n"
                "Tab - next figure\n"
                "R - restore\n"
                "Selected: " + controller.get_current_type()
            );
            window.draw(info);
        }

        window.display();
    }

    return 0;
}
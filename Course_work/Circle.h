#pragma once
#include "Figure.h"

class Circle : public Figure 
{
private:
    sf::CircleShape circle;
    float radius;
    float start_radius;

public:
    Circle(float x0, float y0, float r, sf::Color c);

    void draw(sf::RenderWindow* window) override;
    void move(float dx, float dy, float w_width, float w_height) override;
    void restore() override;
    Figure* clone() override;

    string get_type() const override;
    bool hit_figure(float click_x, float click_y) override;
};
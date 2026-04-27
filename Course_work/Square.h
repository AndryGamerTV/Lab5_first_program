#pragma once
#include "Figure.h"

class Square : public Figure 
{
private:
    sf::RectangleShape square;
    float side;
    float start_side;

public:
    Square(float x0, float y0, float s, sf::Color c);

    void draw(sf::RenderWindow* window) override;
    void move(float dx, float dy, float w_width, float w_height) override;
    void restore() override;
    Figure* clone() override;

    string get_type() const override;
    bool hit_figure(float click_x, float click_y) override;
};
#pragma once
#include "Figure.h"

class Triangle : public Figure {
private:
    sf::ConvexShape triangle;
    float radius;
    float start_radius;

    void updateShape();

public:
    Triangle(float x0, float y0, float r, sf::Color c);

    void draw(sf::RenderWindow* window) override;
    void move(float dx, float dy, float w_width, float w_height) override;
    void restore() override;
    Figure* clone() override;

    string get_type() const override;
    bool hit_figure(float click_x, float click_y) override;
};
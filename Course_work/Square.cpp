#include "Square.h"

Square::Square(float x0, float y0, float s, sf::Color c)
    : Figure(x0, y0, c), side(s), start_side(s) 
{
    square.setSize(sf::Vector2f(side, side));
    square.setFillColor(color);
    square.setOrigin(side / 2.0f, side / 2.0f);
    square.setPosition(x, y);
}

void Square::draw(sf::RenderWindow* window) 
{
    if (!visible) return;
    square.setFillColor(active ? sf::Color::White : color);
    square.setPosition(x, y);
    window->draw(square);
}

void Square::move(float dx, float dy, float w_width, float w_height) 
{
    x += dx;
    y += dy;
    if (x < 0) x = w_width;
    if (x > w_width) x = 0;
    if (y < 0) y = w_height;
    if (y > w_height) y = 0;
    square.setPosition(x, y);
}

void Square::restore() 
{
    x = x0;
    y = y0;
    side = start_side;
    color = start_color;
    square.setSize(sf::Vector2f(side, side));
    square.setOrigin(side / 2.0f, side / 2.0f);
    square.setPosition(x, y);
    square.setFillColor(color);
}

Figure* Square::clone() 
{
    return new Square(x, y, side, color);
}

string Square::get_type() const 
{
    return "Square";
}

bool Square::hit_figure(float click_x, float click_y) 
{
    return (click_x >= x - side / 2.0f && click_x <= x + side / 2.0f &&
        click_y >= y - side / 2.0f && click_y <= y + side / 2.0f);
}
#include "Circle.h"
#include <cmath>

Circle::Circle(float x0, float y0, float r, sf::Color c)
    : Figure(x0, y0, c), radius(r), start_radius(r) {
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setOrigin(radius, radius);
    circle.setPosition(x, y);
}

void Circle::draw(sf::RenderWindow* window) {
    if (!visible) return;
    circle.setFillColor(active ? sf::Color::White : color);
    circle.setPosition(x, y);
    window->draw(circle);
}

void Circle::move(float dx, float dy, float w_width, float w_height) {
    x += dx;
    y += dy;
    if (x < 0) x = w_width;
    if (x > w_width) x = 0;
    if (y < 0) y = w_height;
    if (y > w_height) y = 0;
    circle.setPosition(x, y);
}

void Circle::restore() {
    x = x0;
    y = y0;
    radius = start_radius;
    color = start_color;
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(x, y);
    circle.setFillColor(color);
}

Figure* Circle::clone() {
    return new Circle(x, y, radius, color);
}

string Circle::get_type() const {
    return "Circle";
}

bool Circle::hit_figure(float click_x, float click_y) {
    float dx = click_x - x;
    float dy = click_y - y;
    return (dx * dx + dy * dy) <= (radius * radius);
}
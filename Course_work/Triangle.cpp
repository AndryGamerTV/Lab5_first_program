#include "Triangle.h"
#include <cmath>

void Triangle::updateShape() {
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0, -radius));
    triangle.setPoint(1, sf::Vector2f(-radius * 0.866f, radius * 0.5f));
    triangle.setPoint(2, sf::Vector2f(radius * 0.866f, radius * 0.5f));
    triangle.setPosition(x, y);
    triangle.setFillColor(color);
}

Triangle::Triangle(float x0, float y0, float r, sf::Color c)
    : Figure(x0, y0, c), radius(r), start_radius(r) {
    updateShape();
}

void Triangle::draw(sf::RenderWindow* window) {
    if (!visible) return;
    triangle.setFillColor(active ? sf::Color::White : color);
    triangle.setPosition(x, y);
    window->draw(triangle);
}

void Triangle::move(float dx, float dy, float w_width, float w_height) {
    x += dx;
    y += dy;
    if (x < 0) x = w_width;
    if (x > w_width) x = 0;
    if (y < 0) y = w_height;
    if (y > w_height) y = 0;
    triangle.setPosition(x, y);
}

void Triangle::restore() {
    x = x0;
    y = y0;
    radius = start_radius;
    color = start_color;
    updateShape();
}

Figure* Triangle::clone() {
    return new Triangle(x, y, radius, color);
}

string Triangle::get_type() const {
    return "Triangle";
}

bool Triangle::hit_figure(float click_x, float click_y) {
    float dx = click_x - x;
    float dy = click_y - y;
    return (dx * dx + dy * dy) <= (radius * radius);
}
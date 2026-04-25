#include "Figure.h"
#include <cmath>

static const float PI = 3.14159265358979f;

static void applyMemento(FigureDetails& obj, const FigureMemento& m);

Square::Square(float x, float y, float s, sf::Color col)
    : FigureDetails(x, y, col), size(s) {}

void Square::draw(sf::RenderWindow& window) 
{
    if (!visible) return;
    drawTrail(window);

    float s = size * deformationFactor;
    sf::RectangleShape rect(sf::Vector2f(s * 2, s * 2));
    rect.setPosition(position.x - s, position.y - s);
    rect.setFillColor(color);
    window.draw(rect);
}

FigureMemento Square::createMemento() const 
{
    return { position, color, visible, showTrail, deformationFactor, "Square" };
}

void Square::restoreFromMemento(const FigureMemento& m) 
{
    position = initialPosition = m.getPosition();
    color = m.getColor();
    visible = m.isVisible();
    showTrail = m.hasTrail();
    deformationFactor = m.getDeformation();
}

Circle::Circle(float x, float y, float r, sf::Color col)
    : FigureDetails(x, y, col), radius(r) {}

void Circle::draw(sf::RenderWindow& window) 
{
    if (!visible) return;
    drawTrail(window);

    float r = radius * deformationFactor;
    sf::CircleShape circle(r);
    circle.setPosition(position.x - r, position.y - r);
    circle.setFillColor(color);
    window.draw(circle);
}

FigureMemento Circle::createMemento() const 
{
    return { position, color, visible, showTrail, deformationFactor, "Circle" };
}

void Circle::restoreFromMemento(const FigureMemento& m) 
{
    position = initialPosition = m.getPosition();
    color = m.getColor();
    visible = m.isVisible();
    showTrail = m.hasTrail();
    deformationFactor = m.getDeformation();
}

Triangle::Triangle(float x, float y, float s, sf::Color col)
    : FigureDetails(x, y, col), size(s) {}

void Triangle::draw(sf::RenderWindow& window) 
{
    if (!visible) return;
    drawTrail(window);

    float s = size * deformationFactor;
    float h = s * std::sqrt(3.0f);
    
    sf::ConvexShape tri;
    tri.setPointCount(3);
    tri.setPoint(0, sf::Vector2f(position.x, position.y - h * 2.0f / 3.0f));
    tri.setPoint(1, sf::Vector2f(position.x - s, position.y + h / 3.0f));
    tri.setPoint(2, sf::Vector2f(position.x + s, position.y + h / 3.0f));
    tri.setFillColor(color);
    window.draw(tri);
}

FigureMemento Triangle::createMemento() const 
{
    return { position, color, visible, showTrail, deformationFactor, "Triangle" };
}

void Triangle::restoreFromMemento(const FigureMemento& m) 
{
    position = initialPosition = m.getPosition();
    color = m.getColor();
    visible = m.isVisible();
    showTrail = m.hasTrail();
    deformationFactor = m.getDeformation();
}

static void applyMemento(FigureDetails& obj, const FigureMemento& m) 
{
    obj.restoreFromMemento(m);
}
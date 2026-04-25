#pragma once
#include "FigureDetails.h"

class Square : public FigureDetails {
    float size;
public:
    Square() : FigureDetails(0, 0, sf::Color::White), size(40.0f) {}
    Square(float x, float y, float s, sf::Color col);

    void draw(sf::RenderWindow& window) override;
    FigureDetails* createClone() const override { return new Square(*this); }
    FigureMemento createMemento() const override;
    void restoreFromMemento(const FigureMemento& m) override;

    float getSize() const { return size; }
};

class Circle : public FigureDetails {
    float radius;
public:
    Circle() : FigureDetails(0, 0, sf::Color::White), radius(40.0f) {}
    Circle(float x, float y, float r, sf::Color col);

    void draw(sf::RenderWindow& window) override;
    FigureDetails* createClone() const override { return new Circle(*this); }
    FigureMemento createMemento() const override;
    void restoreFromMemento(const FigureMemento& m) override;

    float getRadius() const { return radius; }
};

class Triangle : public FigureDetails {
    float size;
public:
    Triangle() : FigureDetails(0, 0, sf::Color::White), size(40.0f) {}
    Triangle(float x, float y, float s, sf::Color col);

    void draw(sf::RenderWindow& window) override;
    FigureDetails* createClone() const override { return new Triangle(*this); }
    FigureMemento createMemento() const override;
    void restoreFromMemento(const FigureMemento& m) override;

    float getSize() const { return size; }
};
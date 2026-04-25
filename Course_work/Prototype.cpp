#include "Prototype.h"
#include "Figure.h"
#include <iostream>

Prototype::Prototype() 
{
    registerPrototype("Square", new Square(0, 0, 40.0f, sf::Color::White));
    registerPrototype("Circle", new Circle(0, 0, 40.0f, sf::Color::White));
    registerPrototype("Triangle", new Triangle(0, 0, 40.0f, sf::Color::White));
}

Prototype& Prototype::getInstance() 
{
    static Prototype instance;
    return instance;
}

Prototype::~Prototype() 
{
    for (auto& p : prototypes) delete p.second;
}

void Prototype::registerPrototype(const std::string& name, FigureDetails* p) 
{
    if (!p) return;
    auto it = prototypes.find(name);
    if (it != prototypes.end()) delete it->second;
    prototypes[name] = p;
}

FigureDetails* Prototype::createObject(const std::string& name,
    float x, float y, sf::Color color) 
{
    auto it = prototypes.find(name);
    if (it == prototypes.end()) return nullptr;

    std::cout << name << " created" << std::endl;

    FigureDetails* obj = it->second->createClone();
    if (!obj->isComposite()) 
    {
        obj->changeColor(color);
    }
    sf::Vector2f cur = obj->getPosition();
    obj->move(x - cur.x, y - cur.y);
    FigureMemento snap = obj->createMemento();
    obj->restoreFromMemento(
        FigureMemento(sf::Vector2f(x, y),
            snap.getColor(),
            snap.isVisible(),
            snap.hasTrail(),
            snap.getDeformation(),
            snap.getType()));
    return obj;
}

bool Prototype::hasPrototype(const std::string& name) const 
{
    return prototypes.count(name) > 0;
}

std::vector<std::string> Prototype::getAvailablePrototypes() const 
{
    std::vector<std::string> names;
    for (const auto& p : prototypes) names.push_back(p.first);
    return names;
}
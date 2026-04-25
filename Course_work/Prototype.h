#pragma once
#include "FigureDetails.h"
#include <map>
#include <vector>
#include <string>

class Prototype {
    std::map<std::string, FigureDetails*> prototypes;
    Prototype();

public:
    static Prototype& getInstance();
    Prototype(const Prototype&) = delete;
    Prototype& operator=(const Prototype&) = delete;
    ~Prototype();

    void registerPrototype(const std::string& name, FigureDetails* prototype);
    FigureDetails* createObject(const std::string& name, float x, float y, sf::Color color);

    bool hasPrototype(const std::string& name) const;
    std::vector<std::string> getAvailablePrototypes() const;
};

inline Prototype& GetPrototype() { return Prototype::getInstance(); }

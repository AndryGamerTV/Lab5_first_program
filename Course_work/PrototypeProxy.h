#pragma once
#include "Prototype.h"
#include <iostream>

class PrototypeProxy 
{
    Prototype* realPrototype;
    size_t requestCount;

    Prototype& getRealPrototype() 
    {
        if (!realPrototype) {
            realPrototype = &GetPrototype();
            std::cout << "[Proxy] Prototype service initialized" << std::endl;
        }
        return *realPrototype;
    }

public:
    PrototypeProxy() : realPrototype(nullptr), requestCount(0) {}

    FigureDetails* createObject(const std::string& name, float x, float y, sf::Color color) 
    {
        ++requestCount;
        std::cout << "[Proxy] Request #" << requestCount << ": create '" << name << "'" << std::endl;

        Prototype& prototype = getRealPrototype();
        if (!prototype.hasPrototype(name)) 
        {
            std::cout << "[Proxy] Access denied: prototype '" << name << "' not found" << std::endl;
            return nullptr;
        }

        return prototype.createObject(name, x, y, color);
    }

    size_t getRequestCount() const 
    { 
        return requestCount; 
    }
};

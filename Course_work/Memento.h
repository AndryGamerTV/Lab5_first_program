#pragma once
#include "FigureDetails.h"
#include <vector>
#include <string>

class Memento 
{
public:
    static bool saveScene(const std::vector<FigureDetails*>& objects,
        const std::string& filename);
    static std::vector<FigureDetails*> loadScene(const std::string& filename);
};
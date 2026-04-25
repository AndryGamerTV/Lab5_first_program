#pragma once
#include "FigureDetails.h"
#include <vector>
#include <string>

class Controller {
    std::vector<FigureDetails*> objects;
    int selectedIndex;
    Controller();

public:
    static Controller& getInstance();
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    ~Controller();

    void addObject(FigureDetails* obj);
    void removeSelected();
    void removeObject(FigureDetails* obj);
    void clear();

    void selectNext();
    void selectPrevious();

    std::vector<int> multiSelection;
    void toggleMultiSelection(int index) 
    {
        auto it = std::find(multiSelection.begin(), multiSelection.end(), index);
        if (it != multiSelection.end()) multiSelection.erase(it);
        else multiSelection.push_back(index);
    }

    void clearMultiSelection() { multiSelection.clear(); }

    FigureDetails* getSelected() const;
    int    getSelectedIndex() const { return selectedIndex; }
    size_t getObjectCount()   const { return objects.size(); }
    const std::vector<FigureDetails*>& getObjects() const { return objects; }

    void updateAll(float deltaTime);
    void drawAll(sf::RenderWindow& window);

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    FigureDetails* createFromPrototype(const std::string& type,
        float x, float y, sf::Color color);
    
    void extractAndGroupSelected(float x, float y);
private:
    void drawSelection(sf::RenderWindow& window, FigureDetails* obj);
};
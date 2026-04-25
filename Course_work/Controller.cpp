#include "Controller.h"
#include "Aggregate.h"
#include "Memento.h"
#include "Prototype.h"
#include "PrototypeProxy.h"
#include <algorithm>

Controller::Controller() : selectedIndex(-1) {}

Controller& Controller::getInstance() 
{
    static Controller instance;
    return instance;
}

Controller::~Controller() { clear(); }

void Controller::addObject(FigureDetails* obj) 
{
    if (!obj) return;
    objects.push_back(obj);
    if (selectedIndex == -1) selectedIndex = 0;
}

void Controller::removeSelected() 
{
    if (selectedIndex < 0 || selectedIndex >= (int)objects.size()) return;
    delete objects[selectedIndex];
    objects.erase(objects.begin() + selectedIndex);
    if (objects.empty()) selectedIndex = -1;
    else selectedIndex = std::min(selectedIndex, (int)objects.size() - 1);
}

void Controller::removeObject(FigureDetails* obj) 
{
    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it == objects.end()) return;
    int idx = (int)std::distance(objects.begin(), it);
    delete* it;
    objects.erase(it);
    if (objects.empty()) selectedIndex = -1;
    else {
        if (idx <= selectedIndex) --selectedIndex;
        selectedIndex = std::min(selectedIndex, (int)objects.size() - 1);
    }
}

void Controller::clear() 
{
    for (auto obj : objects) delete obj;
    objects.clear();
    selectedIndex = -1;
}

void Controller::selectNext() 
{
    if (objects.empty()) return;
    selectedIndex = (selectedIndex + 1) % (int)objects.size();
}

void Controller::selectPrevious() 
{
    if (objects.empty()) return;
    selectedIndex = (selectedIndex - 1 + (int)objects.size()) % (int)objects.size();
}

FigureDetails* Controller::getSelected() const 
{
    if (selectedIndex < 0 || selectedIndex >= (int)objects.size()) return nullptr;
    return objects[selectedIndex];
}

void Controller::updateAll(float deltaTime) {
    for (auto obj : objects) obj->updateAutoMove(deltaTime);

    for (size_t i = 0; i < objects.size(); ++i) 
    {
        if (!objects[i]->isVisible()) continue;
        for (size_t j = i + 1; j < objects.size(); ++j) 
        {
            if (!objects[j]->isVisible()) continue;
            sf::Vector2f diff = objects[i]->getPosition() - objects[j]->getPosition();
            float distSq = diff.x * diff.x + diff.y * diff.y;

            if (distSq < 60.0f * 60.0f) 
            {
                objects[i]->influenceColor(*objects[j]);
                objects[j]->influenceColor(*objects[i]);
            }
        }
    }
}

void Controller::drawAll(sf::RenderWindow& window) 
{
    for (size_t i = 0; i < objects.size(); ++i) 
    {
        objects[i]->draw(window);
        if ((int)i == selectedIndex || std::find(multiSelection.begin(), multiSelection.end(), (int)i) != multiSelection.end())
            drawSelection(window, objects[i]);
    }
}

bool Controller::saveToFile(const std::string& filename) const 
{
    return Memento::saveScene(objects, filename);
}

bool Controller::loadFromFile(const std::string& filename) 
{
    auto loaded = Memento::loadScene(filename);
    clear();
    for (auto obj : loaded) addObject(obj);
    return !loaded.empty();
}

FigureDetails* Controller::createFromPrototype(const std::string& type,
    float x, float y, sf::Color color) 
{
    static PrototypeProxy proxy;
    return proxy.createObject(type, x, y, color);
}

void Controller::extractAndGroupSelected(float x, float y) 
{
    if (multiSelection.empty() && selectedIndex == -1) return;

    std::vector<int> toGroup;
    if (selectedIndex != -1) 
    {
        toGroup.push_back(selectedIndex);
    }
    for (int idx : multiSelection) 
    {
        if (std::find(toGroup.begin(), toGroup.end(), idx) == toGroup.end()) 
        {
            toGroup.push_back(idx);
        }
    }

    if (toGroup.size() < 2) return;

    Aggregate* agg = new Aggregate(x, y);
    std::sort(toGroup.rbegin(), toGroup.rend()); 

    for (int idx : toGroup) {
        if (idx >= 0 && idx < (int)objects.size()) 
        {
            agg->addChild(objects[idx]);
        }
    }

    for (int idx : toGroup) {
        if (idx >= 0 && idx < (int)objects.size()) 
        {
            objects.erase(objects.begin() + idx);
        }
    }

    multiSelection.clear();
    selectedIndex = -1;
    addObject(agg);
}

void Controller::drawSelection(sf::RenderWindow& window, FigureDetails* obj) 
{
    sf::CircleShape marker(8.0f);
    sf::Vector2f pos = obj->getPosition();
    marker.setPosition(pos.x - 8.0f, pos.y - 8.0f);
    marker.setFillColor(sf::Color::Transparent);
    marker.setOutlineThickness(2.0f);
    marker.setOutlineColor(sf::Color::Yellow);
    window.draw(marker);
}
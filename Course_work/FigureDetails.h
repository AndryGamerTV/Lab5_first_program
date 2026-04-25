#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include "Config.h"

class FigureMemento {
private:
    sf::Vector2f position;
    sf::Color color;
    bool visible;
    bool showTrail;
    float deformationFactor;
    std::string objectType;
public:
    FigureMemento(sf::Vector2f pos, sf::Color col, bool vis,
        bool trail, float deform, std::string type)
        : position(pos), color(col), visible(vis), showTrail(trail),
        deformationFactor(deform), objectType(std::move(type)) {
    }

    sf::Vector2f getPosition()    const { return position; }
    sf::Color    getColor()       const { return color; }
    bool         isVisible()      const { return visible; }
    bool         hasTrail()       const { return showTrail; }
    float        getDeformation() const { return deformationFactor; }
    std::string  getType()        const { return objectType; }
};

class FigureDetails {
protected:
    sf::Vector2f position;
    sf::Vector2f initialPosition;
    sf::Color color;
    sf::Color initialColor;
    bool visible;
    bool showTrail;
    std::vector<sf::Vector2f> trail;
    bool isAutoMoving;
    float moveTime;
    float deformationFactor;
    bool isWithinBounds(float x, float y) const;

public:
    FigureDetails(float x, float y, sf::Color col);
    virtual ~FigureDetails() = default;
    FigureDetails(const FigureDetails&) = default;
    FigureDetails& operator=(const FigureDetails&) = delete;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual FigureDetails* createClone() const = 0;
    virtual FigureMemento createMemento() const = 0;
    virtual void restoreFromMemento(const FigureMemento& memento) = 0;

    virtual void addChild(FigureDetails*) {}
    virtual void removeChild(FigureDetails*) {}
    virtual std::vector<FigureDetails*> getChildren() const { return {}; }
    virtual bool isComposite() const { return false; }

    virtual void move(float dx, float dy);
    virtual void updateAutoMove(float deltaTime);

    void startAutoMove();
    void stopAutoMove();
    void reset();
    void changeColor(sf::Color newColor);
    void toggleVisibility();
    void toggleTrail();
    virtual void deform(float delta);
    void influenceColor(const FigureDetails& other);

    void save(std::ofstream& out) const {
        out << position.x << ' ' << position.y << ' '
            << (int)color.r << ' ' << (int)color.g << ' ' << (int)color.b << ' '
            << (int)visible << ' ' << (int)showTrail << ' '
            << deformationFactor;
    }
    void load(std::ifstream& in) {
        int r, g, b;
        in >> position.x >> position.y
            >> r >> g >> b
            >> visible >> showTrail
            >> deformationFactor;
        color = sf::Color(r, g, b);
        initialPosition = position;
        initialColor = color;
    }

    void drawTrail(sf::RenderWindow& window) const;
    bool         isVisible()            const { return visible; }
    sf::Vector2f getPosition()          const { return position; }
    sf::Color    getColor()             const { return color; }
    bool         isMoving()             const { return isAutoMoving; }
    float        getDeformationFactor() const { return deformationFactor; }
};
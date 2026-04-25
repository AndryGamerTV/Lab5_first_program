#include "FigureDetails.h"
#include <cmath>
#include <algorithm>

FigureDetails::FigureDetails(float x, float y, sf::Color col)
    : position(x, y), initialPosition(x, y),
    color(col), initialColor(col),
    visible(true), showTrail(false),
    isAutoMoving(false), moveTime(0.0f),
    deformationFactor(1.0f) {}

bool FigureDetails::isWithinBounds(float x, float y) const 
{
    return true;
}

void FigureDetails::move(float dx, float dy) 
{
    if (showTrail) 
    {
        trail.push_back(position);
        if (trail.size() > Config::Trail::MAX_LENGTH)
            trail.erase(trail.begin());
    }
    
    position.x += dx;
    position.y += dy;

    if (position.x < 0) 
    {
        position.x += Config::WINDOW_WIDTH;
        initialPosition.x += Config::WINDOW_WIDTH;
        trail.clear();
    }
    else if (position.x > Config::WINDOW_WIDTH) 
    {
        position.x -= Config::WINDOW_WIDTH;
        initialPosition.x -= Config::WINDOW_WIDTH;
        trail.clear();
    }

    if (position.y < 0) 
    {
        position.y += Config::WINDOW_HEIGHT;
        initialPosition.y += Config::WINDOW_HEIGHT;
        trail.clear();
    }
    else if (position.y > Config::WINDOW_HEIGHT) 
    {
        position.y -= Config::WINDOW_HEIGHT;
        initialPosition.y -= Config::WINDOW_HEIGHT;
        trail.clear();
    }
}

void FigureDetails::updateAutoMove(float deltaTime) 
{
    if (!isAutoMoving) return;
    moveTime += deltaTime;
    float angle = moveTime * Config::Movement::SINE_FREQUENCY_X;
    float radius = Config::Movement::SINE_AMPLITUDE * 50.0f;
    float newX = initialPosition.x + radius * std::cos(angle);
    float newY = initialPosition.y + radius * std::sin(angle);
    move(newX - position.x, newY - position.y);
}

void FigureDetails::startAutoMove() 
{
    isAutoMoving = true;
    initialPosition = position;
    moveTime = 0.0f;
}
void FigureDetails::stopAutoMove() { isAutoMoving = false; }

void FigureDetails::reset() 
{
    position = initialPosition;
    color = initialColor;
    visible = true;
    showTrail = false;
    trail.clear();
    isAutoMoving = false;
    moveTime = 0.0f;
    deformationFactor = 1.0f;
}

void FigureDetails::changeColor(sf::Color newColor) { color = newColor; }
void FigureDetails::toggleVisibility() { visible = !visible; }
void FigureDetails::toggleTrail() 
{ 
    showTrail = !showTrail; 
    if (!showTrail) trail.clear();
}

void FigureDetails::deform(float delta) 
{
    deformationFactor = std::max(0.1f, deformationFactor + delta);
}

void FigureDetails::influenceColor(const FigureDetails& other) 
{
    sf::Color oc = other.getColor();
    color.r = (sf::Uint8)((color.r + oc.r) / 2);
    color.g = (sf::Uint8)((color.g + oc.g) / 2);
    color.b = (sf::Uint8)((color.b + oc.b) / 2);
}

void FigureDetails::drawTrail(sf::RenderWindow& window) const 
{
    if (!showTrail) return;
    
    for (size_t i = 0; i < trail.size(); ++i) 
    {
        sf::CircleShape dot(3.0f);
        dot.setPosition(trail[i].x - 3.0f, trail[i].y - 3.0f);
        sf::Color tc = color;
        tc.a = (sf::Uint8)((float)i / (float)trail.size() * 150.0f);
        dot.setFillColor(tc);
        window.draw(dot);
    }
}
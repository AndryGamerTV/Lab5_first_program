#include "Aggregate.h"
#include "Figure.h"
#include <algorithm>
#include <cmath>

Aggregate::Aggregate(float x, float y)
    : FigureDetails(x, y, Config::Colors::WHITE),
    containerWidth(50.0f), containerHeight(50.0f) {}

Aggregate::~Aggregate() 
{
    for (auto c : children) delete c;
}

static float getRadius(FigureDetails* f) 
{
    if (auto* s = dynamic_cast<Square*>(f))    return s->getSize();
    if (auto* c = dynamic_cast<Circle*>(f))    return c->getRadius();
    if (auto* t = dynamic_cast<Triangle*>(f))  return t->getSize();
    if (auto* a = dynamic_cast<Aggregate*>(f))
        return std::max(a->getContainerWidth(), a->getContainerHeight()) / 2.0f;
    return 50.0f;
}

void Aggregate::updateContainerSize() {
    if (children.empty()) {
        containerWidth = containerHeight = 50.0f;
        return;
    }
    float minX = 0, maxX = 0, minY = 0, maxY = 0;
    for (size_t i = 0; i < children.size(); ++i) {
        float ox = offsets[i].x, oy = offsets[i].y;
        float sw, sh;
        if (auto* a = dynamic_cast<Aggregate*>(children[i])) {
            sw = a->getContainerWidth() / 2.0f;
            sh = a->getContainerHeight() / 2.0f;
        }
        else {
            float s = getRadius(children[i]) * children[i]->getDeformationFactor();
            sw = sh = s;
        }
        minX = std::min(minX, ox - sw); maxX = std::max(maxX, ox + sw);
        minY = std::min(minY, oy - sh); maxY = std::max(maxY, oy + sh);
    }
    containerWidth = (maxX - minX) + PADDING * 2;
    containerHeight = (maxY - minY) + PADDING * 2;
}

void Aggregate::addChild(FigureDetails* child) 
{
    if (!child) return;
    sf::Vector2f offset = child->getPosition() - position;
    children.push_back(child);
    offsets.push_back(offset);
    updateContainerSize();
}

void Aggregate::recalcOffsets() 
{
    for (size_t i = 0; i < children.size(); ++i)
        offsets[i] = children[i]->getPosition() - position;
    updateContainerSize();
}

void Aggregate::removeChild(FigureDetails* child) 
{
    auto it = std::find(children.begin(), children.end(), child);
    if (it == children.end()) return;
    size_t idx = std::distance(children.begin(), it);
    delete* it;
    children.erase(it);
    offsets.erase(offsets.begin() + idx);
    updateContainerSize();
}

void Aggregate::draw(sf::RenderWindow& window) 
{
    if (!visible) return;
    drawTrail(window);

    float aw = containerWidth * deformationFactor;
    float ah = containerHeight * deformationFactor;

    sf::RectangleShape rect({ aw, ah });
    rect.setPosition(position.x - aw / 2.0f, position.y - ah / 2.0f);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(2.0f);
    rect.setOutlineColor(color);
    window.draw(rect);

    for (auto c : children) c->draw(window);
}

bool Aggregate::isContainerWithinBounds(float dx, float dy) const
{
    const float cx = position.x + dx;
    const float cy = position.y + dy;
    const float hw = (containerWidth * deformationFactor) / 2.0f;
    const float hh = (containerHeight * deformationFactor) / 2.0f;

    return (cx - hw >= 0.0f) &&
           (cx + hw <= (float)Config::WINDOW_WIDTH) &&
           (cy - hh >= 0.0f) &&
           (cy + hh <= (float)Config::WINDOW_HEIGHT);
}

void Aggregate::move(float dx, float dy)
{
    if (showTrail)
    {
        trail.push_back(position);
        if (trail.size() > Config::Trail::MAX_LENGTH) trail.erase(trail.begin());
    }

    if (isContainerWithinBounds(dx, dy))
    {
        position.x += dx;
        position.y += dy;

        for (size_t i = 0; i < children.size(); ++i)
        {
            sf::Vector2f target = position + offsets[i];
            sf::Vector2f cur = children[i]->getPosition();
            children[i]->move(target.x - cur.x, target.y - cur.y);
        }
    }
    else
    {
        isAutoMoving = false;
    }
}

void Aggregate::updateAutoMove(float deltaTime) 
{
    if (!isAutoMoving) return;
    moveTime += deltaTime;
    float angle = moveTime * Config::Movement::SINE_FREQUENCY_X;
    float radius = Config::Movement::SINE_AMPLITUDE * 50.0f;
    float newX = initialPosition.x + radius * std::cos(angle);
    float newY = initialPosition.y + radius * std::sin(angle);
    move(newX - position.x, newY - position.y);
}

FigureDetails* Aggregate::createClone() const 
{
    Aggregate* agg = new Aggregate(position.x, position.y);
    for (auto c : children) agg->addChild(c->createClone());
    return agg;
}

FigureMemento Aggregate::createMemento() const 
{
    return { position, color, visible, showTrail, deformationFactor, "Aggregate" };
}

void Aggregate::restoreFromMemento(const FigureMemento& m) 
{
    position = initialPosition = m.getPosition();
    color = m.getColor();
    visible = m.isVisible();
    showTrail = m.hasTrail();
    deformationFactor = m.getDeformation();
}
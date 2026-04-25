#pragma once
#include "FigureDetails.h"
#include <vector>

class Aggregate : public FigureDetails {
    std::vector<FigureDetails*> children;
    std::vector<sf::Vector2f> offsets;
    float containerWidth;
    float containerHeight;
    static constexpr float PADDING = 10.0f;

    void updateContainerSize();
    bool isContainerWithinBounds(float dx, float dy) const;

public:
    Aggregate(float x = 0.0f, float y = 0.0f);
    ~Aggregate();

    void addChild(FigureDetails* child) override;
    void recalcOffsets();
    void removeChild(FigureDetails* child) override;
    std::vector<FigureDetails*> getChildren() const override { return children; }
    bool isComposite() const override { return true; }

    void draw(sf::RenderWindow& window) override;
    void move(float dx, float dy) override;
    void updateAutoMove(float deltaTime) override;

    FigureDetails* createClone() const override;
    FigureMemento createMemento() const override;
    void restoreFromMemento(const FigureMemento& m) override;

    float getContainerWidth()  const { return containerWidth; }
    float getContainerHeight() const { return containerHeight; }
};
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Figure 
{
protected:
    float x, y;
    float x0, y0;
    sf::Color color;
    sf::Color start_color;
    bool visible;
    bool active;

public:
    Figure(float start_x, float start_y, sf::Color c);
    virtual ~Figure();

    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void move(float dx, float dy, float w_width, float w_height) = 0;
    virtual void restore() = 0;
    virtual Figure* clone() = 0;
    virtual string get_type() const = 0;
    virtual bool hit_figure(float click_x, float click_y) = 0;

    bool get_active() const;
    void activate();
    void deactivate();
    void set_visible(bool v);
    bool get_visible() const;
    void set_position(float new_x, float new_y);
    float get_x() const 
    { 
        return x; 
    }
    float get_y() const 
    { 
        return y; 
    }
    sf::Color get_color() const 
    { 
        return color; 
    }
};
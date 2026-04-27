#include "Figure.h"

Figure::Figure(float start_x, float start_y, sf::Color c) 
{
    x = start_x;
    y = start_y;
    x0 = start_x;
    y0 = start_y;
    color = c;
    start_color = c;
    visible = true;
    active = false;
}

Figure::~Figure() {}

bool Figure::get_active() const 
{
    return active;
}

void Figure::activate() 
{
    active = true;
}

void Figure::deactivate() 
{
    active = false;
}

void Figure::set_visible(bool v) 
{
    visible = v;
}

bool Figure::get_visible() const 
{
    return visible;
}

void Figure::set_position(float new_x, float new_y) 
{
    x = new_x;
    y = new_y;
}
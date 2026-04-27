#pragma once
#include "Figure.h"
#include <iostream>

class FigureProxy : public Figure 
{
private:
    Figure* real_figure;
    int move_count;
    bool access_allowed;

public:
    FigureProxy(Figure* figure);
    ~FigureProxy();

    void allow_access(bool allowed);

    void draw(sf::RenderWindow* window) override;
    void move(float dx, float dy, float w_width, float w_height) override;
    void restore() override;
    Figure* clone() override;

    string get_type() const override;
    bool hit_figure(float click_x, float click_y) override;

    int get_move_count() const 
    { 
        return move_count; 
    }
    Figure* get_real_figure() const 
    { 
        return real_figure; 
    }

    void print_stats() const;
};
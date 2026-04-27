#pragma once
#include "Figure.h"
#include <vector>

class Controller 
{
private:
    vector<Figure*> scene_figures;
    Figure* current_figure;

public:
    Controller();
    ~Controller();

    void add_current(Figure* f);
    Figure* get_current_figure();
    void set_current_figure(Figure* f);
    void move_current(float dx, float dy, float w_width, float w_height);
    void next_figure();
    void remove_current();
    void restore_current();
    void toggle_access_current();

    void draw_all(sf::RenderWindow* window);
    int get_count() const 
    { 
        return (int)scene_figures.size(); 
    }
    string get_current_type() const;
};
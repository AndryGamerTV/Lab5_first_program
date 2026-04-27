#include "Controller.h"
#include "FigureProxy.h"
#include <algorithm>

Controller::Controller() 
{
    current_figure = nullptr;
}

Controller::~Controller() 
{
    for (int i = 0; i < scene_figures.size(); i++) 
    {
        delete scene_figures[i];
    }
    scene_figures.clear();
}

void Controller::add_current(Figure* f) 
{
    if (f == nullptr) return;

    if (current_figure != nullptr) 
    {
        current_figure->deactivate();
    }

    scene_figures.push_back(f);
    current_figure = f;
    current_figure->activate();
}

Figure* Controller::get_current_figure() 
{
    return current_figure;
}

void Controller::set_current_figure(Figure* f) 
{
    if (current_figure != nullptr) 
    {
        current_figure->deactivate();
    }

    current_figure = f;

    if (current_figure != nullptr) 
    {
        current_figure->activate();
    }
}

void Controller::move_current(float dx, float dy, float w_width, float w_height) 
{
    if (current_figure != nullptr && current_figure->get_active()) 
    {
        current_figure->move(dx, dy, w_width, w_height);
    }
}

void Controller::next_figure() 
{
    if (scene_figures.empty()) return;

    auto it = find(scene_figures.begin(), scene_figures.end(), current_figure);

    if (current_figure != nullptr) current_figure->deactivate();

    if (it == scene_figures.end() || it + 1 == scene_figures.end())
        current_figure = scene_figures[0];
    else
        current_figure = *(it + 1);

    current_figure->activate();
}

void Controller::remove_current() 
{
    if (current_figure == nullptr) return;

    auto it = find(scene_figures.begin(), scene_figures.end(), current_figure);
    if (it == scene_figures.end()) return;

    delete current_figure;
    scene_figures.erase(it);

    if (scene_figures.empty()) 
    {
        current_figure = nullptr;
    }
    else 
    {
        current_figure = scene_figures[0];
        current_figure->activate();
    }
}

void Controller::restore_current() 
{
    if (current_figure != nullptr)
        current_figure->restore();
}

void Controller::toggle_access_current() 
{
    if (current_figure == nullptr) return;
    FigureProxy* proxy = dynamic_cast<FigureProxy*>(current_figure);
    if (proxy) 
    {
        bool currently_visible = proxy->get_visible();
        proxy->allow_access(!currently_visible);
        proxy->set_visible(!currently_visible);
    }
}

void Controller::draw_all(sf::RenderWindow* window) 
{
    for (auto f : scene_figures)
        f->draw(window);
}

string Controller::get_current_type() const 
{
    if (current_figure == nullptr) return "none";
    return current_figure->get_type();
}
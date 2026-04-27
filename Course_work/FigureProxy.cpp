#include "FigureProxy.h"

FigureProxy::FigureProxy(Figure* figure)
    : Figure(figure->get_x(), figure->get_y(), figure->get_color()),
    real_figure(figure),
    move_count(0),
    access_allowed(true)
{
    cout << "[Proxy] Created proxy for: " << figure->get_type() << endl;
}

FigureProxy::~FigureProxy() {
    print_stats();
    delete real_figure;
}

void FigureProxy::allow_access(bool allowed) {
    access_allowed = allowed;
    cout << "[Proxy] Access for " << real_figure->get_type()
        << (allowed ? " ALLOWED" : " DENIED") << endl;
}

void FigureProxy::draw(sf::RenderWindow* window) {
    if (!access_allowed) return;
    real_figure->draw(window);
}

void FigureProxy::move(float dx, float dy, float w_width, float w_height) {
    if (!access_allowed) return;
    move_count++;
    real_figure->move(dx, dy, w_width, w_height);
    x = real_figure->get_x();
    y = real_figure->get_y();
}

void FigureProxy::restore() {
    cout << "[Proxy] Restore -> " << real_figure->get_type() << endl;
    real_figure->restore();
    x = real_figure->get_x();
    y = real_figure->get_y();
}

Figure* FigureProxy::clone() {
    return new FigureProxy(real_figure->clone());
}

string FigureProxy::get_type() const {
    return "Proxy[" + real_figure->get_type() + "]";
}

bool FigureProxy::hit_figure(float click_x, float click_y) {
    return real_figure->hit_figure(click_x, click_y);
}

void FigureProxy::print_stats() const {
    cout << "[Proxy] Stats for " << real_figure->get_type()
        << ": moves=" << move_count << endl;
}
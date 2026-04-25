#include "Memento.h"
#include "Figure.h"
#include "Aggregate.h"
#include <fstream>

static int getTypeCode(FigureDetails* obj) 
{
    if (dynamic_cast<Square*>(obj))      return 1;
    if (dynamic_cast<Circle*>(obj))      return 2;
    if (dynamic_cast<Triangle*>(obj))    return 3;
    if (dynamic_cast<Aggregate*>(obj))   return 4;
    return 0;
}

static FigureDetails* createByCode(int code) 
{
    switch (code) 
    {
    case 1: return new Square();
    case 2: return new Circle();
    case 3: return new Triangle();
    case 4: return new Aggregate();
    default: return nullptr;
    }
}

static void saveObject(std::ofstream& out, FigureDetails* obj) 
{
    out << getTypeCode(obj) << ' ';
    obj->save(out);
    out << '\n';
    if (auto* agg = dynamic_cast<Aggregate*>(obj)) 
    {
        const auto ch = agg->getChildren();
        out << ch.size() << '\n';
        for (auto c : ch) saveObject(out, c);
    }
    else 
    {
        out << 0 << '\n';
    }
}

static FigureDetails* loadObject(std::ifstream& in) 
{
    int code; in >> code;
    FigureDetails* obj = createByCode(code);
    if (!obj) return nullptr;
    obj->load(in);

    int childCount; in >> childCount;
    if (auto* agg = dynamic_cast<Aggregate*>(obj)) 
    {
        for (int j = 0; j < childCount; ++j) 
        {
            FigureDetails* ch = loadObject(in);
            if (ch) agg->addChild(ch);
        }
    }
    else {
        for (int j = 0; j < childCount; ++j) 
        {
            FigureDetails* ch = loadObject(in);
            delete ch;
        }
    }
    return obj;
}

bool Memento::saveScene(const std::vector<FigureDetails*>& objects,
    const std::string& filename) 
{
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    out << objects.size() << '\n';
    for (auto obj : objects)
        saveObject(out, obj);
    return true;
}

std::vector<FigureDetails*> Memento::loadScene(const std::string& filename) 
{
    std::vector<FigureDetails*> objects;
    std::ifstream in(filename);
    if (!in.is_open()) return objects;
    int count; in >> count;
    for (int i = 0; i < count; ++i) 
    {
        FigureDetails* obj = loadObject(in);
        if (obj) objects.push_back(obj);
    }
    return objects;
}

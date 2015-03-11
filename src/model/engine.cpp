
#include "model/engine.h"

#include "model/unit.h"

#include <algorithm>


namespace aoe
{

Engine::Engine() {}
Engine::~Engine() {}


void Engine::animate_iteration()
{
    for (auto it=active_units.begin(); it!=active_units.end(); ++it)
    {
        (*it)->take_turn();
    }
}

bool Engine::contains(Unit* unit)
{
    return std::find(active_units.begin(), active_units.end(), unit) != active_units.end();
}

void Engine::add_unit(Unit* unit)
{
    auto it = std::find(active_units.begin(), active_units.end(), unit);
    if (it != active_units.end())
    {
        active_units.push_back(unit);
    }
}

void Engine::remove_unit(Unit* unit)
{
    auto it = std::find(active_units.begin(), active_units.end(), unit);
    if (it != active_units.end())
    {
        active_units.erase(it);
    }
}

std::ostream& operator<<(std::ostream& out, const Engine& e)
{
    int size = e.active_units.size();
    out << "Size: " << size << '\n';
    for (int i=0;i<size;i++)
    {
        out << '\t' << i << ": " << *(e.active_units[i]);
    }
    return out;
}


void Engine::run()
{
    animate_iteration();
    std::cout << *this << std::endl;
}

}

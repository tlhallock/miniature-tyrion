
#include "model/engine.h"

#include "task/task.h"

#include <algorithm>


namespace aoe
{

Engine::Engine() {}
Engine::~Engine() {}


void Engine::animate_iteration()
{
    for (auto it=active_units.begin(); it!=active_units.end(); ++it)
    {
        it->second->apply();
    }
}

//bool Engine::contains(Task* unit)
//{
//    return std::find(active_units.begin(), active_units.end(), unit) != active_units.end();
//}

void Engine::set_task(Unit* unit, Task* task)
{
    auto it = active_units.find(unit);
    if (it == active_units.end())
    {
        if (task != nullptr)
        {
            active_units.insert(std::pair<Unit*,Task*>{unit, task});
        }
    }
    else
    {
        if (task == nullptr)
        {
            active_units.erase(it);
        }
        else
        {
            it->second = task;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Engine& e)
{
    int size = e.active_units.size();
    out << "Size: " << size << '\n';
    int i=0;
    for (auto it = e.active_units.begin(); it != e.active_units.end(); ++it, i++)
    {
        out << '\t' << i << ": " /*<< *(it->first) */ << " <-> "<< it->second->get_description() << '\n';
    }
    return out;
}


void Engine::run()
{
    animate_iteration();
}

}

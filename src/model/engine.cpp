
#include "model/engine.h"

#include "task/task.h"

#include <algorithm>


namespace aoe
{

Engine::Engine() {}


void Engine::animateIteration(std::set<Unit*>& movedUnits)
{
    for (auto it=active_units.begin(); it!=active_units.end(); ++it)
    {
        Task* task = it->second;

        task->apply();
        if (task->unitHasMoved())
        {
            movedUnits.insert(task->getUnit());
        }
    }
}

void Engine::addTask(Task* task)
{
    if (task == nullptr)
    {
        return;
    }

    Unit* unit = task->getUnit();
    if (unit == nullptr)
    {
        std::cerr << "This should have a unit..." << std::endl;
        exit(-1);
    }

    auto it = active_units.find(unit);

    if (it == active_units.end())
    {
         active_units.insert(std::pair<Unit*,Task*>{unit, task});
    }
    else
    {
         it->second = task;
    }
}

std::ostream& operator<<(std::ostream& out, const Engine& e)
{
    int size = e.active_units.size();
    out << "Size: " << size << '\n';
    int i=0;
    for (auto it = e.active_units.begin(); it != e.active_units.end(); ++it, i++)
    {
        out << '\t' << i << ": " /*<< *(it->first) */ << " <-> "<< it->second->getDescription() << '\n';
    }
    return out;
}

void Engine::idle(Unit *unit)
{
    auto it = active_units.find(unit);
    if (it == active_units.end())
    {
        return;
    }

    active_units.erase(it);
}

}

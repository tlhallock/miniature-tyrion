
#include "model/engine.h"

#include "task/task.h"

#include <algorithm>


namespace aoe
{


IterationInfo::IterationInfo(Game* game_) : game{game_} {}

void IterationInfo::reset()
{
    movingUnits.clear();
}

void IterationInfo::unitMoved(Unit* u)
{
    movingUnits.insert(u);
}

const std::set<Unit*>& IterationInfo::getMovedUnits() const
{
    return movingUnits;
}

Game* IterationInfo::getGame() const
{
    return game;
}




Engine::Engine() {}


void Engine::animateIteration(IterationInfo& info)
{
    for (auto it=active_units.begin(); it!=active_units.end(); ++it)
    {
        it->second->apply(info);
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

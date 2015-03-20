
#include "task/task.h"

namespace aoe
{

Task::Task(Unit* unit_) : unit{unit_} {}
Task::~Task() {}

std::string Task::getDescription() const { return "descriptionless task"; }

Unit* Task::getUnit()
{
    return unit;
}




}

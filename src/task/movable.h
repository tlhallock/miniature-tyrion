
#ifndef MOVE_TASK_H_
#define MOVE_TASK_H_

#include <vector>

#include "model/area.h"
#include "task/task.h"

namespace aoe
{

class UnitListener;
class Unit;


class Move : public Task
{
private:
    Unit* unit;
    Location dest;

public:
    Move(Unit* unit);
    ~Move();

    void set_destination(const Location& dest);

    void apply();

    std::string get_description() const { return "moving torwards " /* + dest.x + "," + dest.y*/; }
};


}

#endif

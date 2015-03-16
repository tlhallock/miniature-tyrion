
#ifndef MOVE_TASK_H_
#define MOVE_TASK_H_

#include <vector>

#include "model/spc/area.h"
#include "task/task.h"

namespace aoe
{

class UnitListener;
class Unit;


class Move : public Task
{
private:
    Location* dest;

public:
    Move(Unit* unit);
    ~Move();

    void setDestination(Location* dest);

    void apply();

    std::string getDescription() const;
};


}

#endif

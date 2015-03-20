

#ifndef ATTACK_H_
#define ATTACK_H_

#include "task/task.h"

namespace aoe
{

class Attack : public Task
{
    Unit* target;

public:
    Attack(Unit* unit);
    ~Attack();

    void set_target(Unit* target);

    void apply(IterationInfo& info);

    std::string getDescription() const;
};

}


#endif

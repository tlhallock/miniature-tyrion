


#ifndef MOVE_TASK_H_
#define MOVE_TASK_H_

namespace aoe
{

class Move : public Task
{
private:
    Area* a;
    Area dest;

public:
    Move(area* a);
    ~Move();

    void set_destination(const area& dest);

    void apply(std::vector<UnitListener*>& listeners);
};


}

#endif

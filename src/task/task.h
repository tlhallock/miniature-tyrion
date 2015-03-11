

#ifndef TASK_H_
#define TASK_H_

#include <vector>

namespace aoe
{

class Task
{
 public:
  Task() {}
  virtual ~Task() {}

  virtual void apply(std::vector<UnitListener*>& listeners) = 0;
};


}

#endif

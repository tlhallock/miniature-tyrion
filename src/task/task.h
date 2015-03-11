

#ifndef TASK_H_
#define TASK_H_

#include <vector>

class Task
{
 public:
  Task() {}
  virtual ~Task() {}

  virtual void apply(std::vector<UnitListener*>& listeners) = 0;
};


#endif

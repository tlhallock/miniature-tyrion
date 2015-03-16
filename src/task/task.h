

#ifndef TASK_H_
#define TASK_H_

#include <vector>
#include <string>

namespace aoe
{

class Unit;

class Task
{
protected:
    Unit* unit;
 public:
  Task(Unit* unit);
  virtual ~Task();

  virtual void apply() = 0;

  virtual std::string getDescription() const;

  Unit* getUnit();
};


}

#endif

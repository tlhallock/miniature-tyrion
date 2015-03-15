

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

  virtual void apply() = 0;

  virtual std::string get_description() const { return "descriptionless task"; }
};


}

#endif

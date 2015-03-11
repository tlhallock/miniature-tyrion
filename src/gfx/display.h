

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "util/timer.h"

class Engine;

class Display : public TimerTask
{
 protected:
  Engine* engine;
 public:
   Display(Engine* engine_) : engine{engine_} {}
  ~Display() {}
};



#endif

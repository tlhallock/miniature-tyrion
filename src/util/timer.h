
#ifndef TIMER_H_
#define TIMER_H_


#include <vector>
#include <functional>
#include <thread>

class TimerTask
{
 public:
  TimerTask() {}
  virtual ~TimerTask() {}

  virtual void run() = 0;
};

class Timer
{
 private:
  long repeat;
  std::vector<TimerTask*> functions;
  std::thread t;

  bool done;

 public:
 Timer(long period);
 ~Timer();

 void run_all();
 void add(TimerTask* task);
 void end();
};


#endif


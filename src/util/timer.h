
#ifndef TIMER_H_
#define TIMER_H_

#include <vector>
#include <functional>
#include <thread>

namespace aoe
{

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
    uint64_t repeat;
    std::vector<TimerTask*> functions;
    std::thread *t;

    bool done;

public:
    Timer(uint64_t period);
    ~Timer();

    void add(TimerTask* task);

    void start();
    void end();

private:
    void run_all();
};

}

#endif


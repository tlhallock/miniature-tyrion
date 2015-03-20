
#include "util/timer.h"




#include <iostream>




namespace aoe
{


//namespace {
//    unsigned long currentTimeMillis()
//    {
//        return
//            std::chrono::system_clock::now().time_since_epoch() /
//            std::chrono::milliseconds(1);
//    }
//}






Timer::Timer(uint64_t period) :
    repeat{period},
    t{nullptr},
    done{false} {}

Timer::~Timer()
{
    if (t != nullptr)
    {
        std::cerr << "Uh oh... Not shut down properly!";
        delete t;
    }
}

void Timer::run_all()
{
    std::cout << "Timer thread being ran...\n";

    for(;;)
    {
//        std::cout << "In timer loop with size = " << functions.size() << " for timer = " << this << std::endl;

        // std::chrono::time_point<std::chrono::system_clock>
        auto now = std::chrono::high_resolution_clock::now();

        if (done)
        {
            std::cout << "Timer thread done..." << std::endl;
            break;
        }

        for (auto it = functions.begin(); it != functions.end(); ++it)
        {
            (*it)->run();
        }

        std::this_thread::sleep_until(now + std::chrono::milliseconds(repeat));
    }

    for (auto it = functions.begin(); it != functions.end(); ++it)
    {
        delete *it;
    }
}

void Timer::start()
{
    t = new std::thread{[&](){ this->run_all(); }};
}

void Timer::end()
{
    done = true;
    t->join();
    t = nullptr;
}

void Timer::add(TimerTask* task)
{
    std::cout << "Should be adding something to timer " << this << std::endl;
    functions.push_back(task);
}

}

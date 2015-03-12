
#include "util/timer.h"

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

namespace aoe
{

Timer::Timer(long period) :
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
        std::cout << "In timer loop with size = " << functions.size() << " for timer = " << this << std::endl;
        cv::waitKey(repeat);
        //      std::this_thread::sleep_for(std::chrono::milliseconds(repeat));

        if (done)
        {
            std::cout << "Timer thread done..." << std::endl;
            break;
        }

        for (auto it = functions.begin(); it != functions.end(); ++it)

        {
            (*it)->run();
        }
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
    std::cout << "Should be adding something to " << this << std::endl;
    functions.push_back(task);
}

}

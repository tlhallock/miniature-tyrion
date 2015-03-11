
#include "util/timer.h"

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

Timer::Timer(long period) :
  repeat{period},
  t{[&](){ this->run_all(); }},
  done{false} {}

Timer::~Timer()
{
  done = true;
  t.join();
}

void Timer::run_all()
{
  std::cout << "Timer thread being ran...\n";
  
  for(;;)
    {
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

  for( auto it = functions.begin(); it != functions.end(); ++it)
    {
      delete *it;
    }
}

void Timer::end()
{
  done = true;
}

void Timer::add(TimerTask* task)
{
  functions.push_back(task);
}

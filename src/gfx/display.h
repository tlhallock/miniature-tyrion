

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "util/timer.h"

class Game;

class Display : public TimerTask
{
 protected:
    Game* game;
 public:
   Display(Game* game);
  ~Display();
};



#endif

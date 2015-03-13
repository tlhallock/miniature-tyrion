#ifndef VIEWPORT_LISTENER_H
#define VIEWPORT_LISTENER_H

namespace aoe
{

class Area;
class Unit;

class ViewportListener
{
    Area* monitoring;


public:
    ViewportListener(Area* monitoring);


    virtual void unit_entered(Unit* entered) = 0;
    virtual void unit_exited(Unit* exit) = 0;
};

}

#endif // VIEWPORT_LISTENER_H

#ifndef PLAYER_LISTENER_H
#define PLAYER_LISTENER_H

class Unit;
class Building;
class Technology;
class ResourceDescription;

class PlayerListener
{
public:
    PlayerListener();
    virtual ~PlayerListener();

    virtual void resource_changed(ResourceDescription* desc);

    virtual void unit_created(Unit* u);
    virtual void unit_killed(Unit* u);

    virtual void building_built(Building* b);
    virtual void building_destroyed(Building* b);

    virtual void technology_researched(Technology* t);

};

#endif // PLAYER_LISTENER_H

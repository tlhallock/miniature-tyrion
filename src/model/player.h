#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "model/area.h"

class Civilization;
class CivilizationDescription;
class Unit;
class Building;
class PlayerListener;


class Player
{
private:
    std::unique_ptr<Civilization> civilization;
    std::vector<Unit*> units;
    std::vector<Building*> buildings;
    int *resources;

    std::vector<PlayerListener*> listeners;

    Area center;

public:
    Player(CivilizationDescription* desc, int nres);
    ~Player();

    void add_listener(PlayerListener* listener);
    void remove_listener(PlayerListener* listener);



};

#endif // PLAYER_H
